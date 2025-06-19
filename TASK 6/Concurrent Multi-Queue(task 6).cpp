
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

using Task = std::function<void()>;

// Thread-safe queue with condition variable
class TaskQueue {
    std::queue<Task> tasks;
    std::mutex mtx;
    std::condition_variable cv;

public:
    // Producer pushes task into the queue and notifies a waiting consumer
    void push(Task task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(std::move(task));
        }
        cv.notify_one();
    }

    // Consumer tries to pop a task (non-blocking, for stealing)
    bool try_pop(Task& task) {
        std::lock_guard<std::mutex> lock(mtx);
        if (tasks.empty()) return false;
        task = std::move(tasks.front());
        tasks.pop();
        return true;
    }

    // Consumer waits for a task (blocking)
    bool wait_pop(Task& task, std::atomic<bool>& done) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return !tasks.empty() || done; });
        if (tasks.empty()) return false; // woke up due to `done`
        task = std::move(tasks.front());
        tasks.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return tasks.empty();
    }

    void notify() {
        cv.notify_one();
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

    void operator()() {
        Task task;
        while (!done) {
            // Try to pop task from own queue (blocking)
            if (ownQueue->wait_pop(task, done)) {
                std::cout << "Thread " << id << " executing task\n";
                task();
            } else {
                // Try to steal task from other queues (non-blocking)
                bool stolen = false;
                for (auto q : queues) {
                    if (q != ownQueue && q->try_pop(task)) {
                        std::cout << "Thread " << id << " stole a task\n";
                        task();
                        stolen = true;
                        break;
                    }
                }
                // If nothing stolen, optional brief sleep (not necessary here due to blocking wait)
                if (!stolen)
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
        }

        // Final draining in case tasks were pushed before shutdown
        while (ownQueue->try_pop(task)) {
            task();
        }
    }
};

int main() {
    const int num_threads = 2;
    std::vector<std::thread> threads;
    std::vector<TaskQueue*> queues;
    std::vector<TaskQueue> queue_objects(num_threads);
    std::atomic<bool> done{ false };

    // Initialize queues
    for (int i = 0; i < num_threads; ++i)
        queues.push_back(&queue_objects[i]);

    // Main thread acts as producer
    for (int i = 0; i < 5; ++i) {
        queues[i % num_threads]->push([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::cout << "  → Task " << i << " executed by thread " << std::this_thread::get_id() << "\n";
        });
    }

    // Start worker threads (consumers)
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

    // Wake up any waiting threads
    for (auto& q : queues)
        q->notify();

    // Join all threads
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}
