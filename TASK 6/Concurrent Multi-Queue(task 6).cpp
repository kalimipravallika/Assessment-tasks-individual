
///---- Concurrent Multi-Queue Producer-Consumer with Work-Stealing ----///

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <atomic>
#include <chrono>

// Define a task as a function that returns void and takes no parameters
using Task = std::function<void()>;

// Thread-safe task queue to store and manage tasks
class TaskQueue {
    std::queue<Task> tasks;
    std::mutex mtx;

public:
    // Add a task to the queue
    void push(Task task) {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push(std::move(task));
    }

    // Try to get a task from the queue
    bool try_pop(Task& task) {
        std::lock_guard<std::mutex> lock(mtx);
        if (tasks.empty()) return false;
        task = std::move(tasks.front());
        tasks.pop();
        return true;
    }

    // Check if the queue is empty
    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return tasks.empty();
    }

    // Get the number of tasks in the queue
    size_t size() {
        std::lock_guard<std::mutex> lock(mtx);
        return tasks.size();
    }
};

// Worker thread that executes tasks from its own queue or steals from others
class Worker {
    int id;
    std::vector<TaskQueue*>& queues;
    TaskQueue* ownQueue;
    std::atomic<bool>& done;

public:
    Worker(int id, std::vector<TaskQueue*>& qs, TaskQueue* own, std::atomic<bool>& done)
        : id(id), queues(qs), ownQueue(own), done(done) {}

    // Worker logic: execute own tasks or steal from other queues
    void operator()() {
        Task task;
        while (!done) {
            if (ownQueue->try_pop(task)) {
                std::cout << "Thread " << id << " executing task\n";
                task();
            } else {
                // Try to steal task from other queues
                bool stolen = false;
                for (auto q : queues) {
                    if (q != ownQueue && q->try_pop(task)) {
                        std::cout << "Thread " << id << " stole a task\n";
                        task();
                        stolen = true;
                        break;
                    }
                }
                // Sleep briefly to prevent busy waiting
                if (!stolen) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
        }
    }
};

int main() {
    const int num_threads = 2;
    std::vector<std::thread> threads;
    std::vector<TaskQueue*> queues;
    std::vector<TaskQueue> queue_objects(num_threads);
    std::atomic<bool> done{ false };

    // Link each queue object with a pointer
    for (int i = 0; i < num_threads; ++i)
        queues.push_back(&queue_objects[i]);

    // Add 5 sample tasks across threads
    for (int i = 0; i < 5; ++i) {
        queues[i % num_threads]->push([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::cout << "  → Task " << i << " executed by thread " << std::this_thread::get_id() << "\n";
        });
    }

    // Start all worker threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(Worker(i, queues, queues[i], done));
    }

    // Wait until all queues are empty
    while (true) {
        bool all_empty = true;
        for (auto q : queues) {
            if (!q->empty()) {
                all_empty = false;
                break;
            }
        }
        if (all_empty) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // Signal threads to stop
    done = true;

    // Join all threads
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}
