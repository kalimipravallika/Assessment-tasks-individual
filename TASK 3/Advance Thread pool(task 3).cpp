
///---- Advanced Thread Pool with Task Scheduling ---- ///

// Include necessary libraries
#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <map>
#include <stdexcept>

// Structure to represent a Task with ID, priority, function to run,
struct Task {
    int id;
    int priority;
    std::function<void()> func;
    std::vector<std::shared_future<void>> dependencies;
    std::promise<void> prom;

    // Get a shared future linked to this task’s promise
    std::shared_future<void> get_future() {
        return prom.get_future().share();
    }

    // Custom comparison for priority queue (higher number = higher priority)
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

// Class to manage and execute tasks using multiple threads
class TaskScheduler {
private:
    std::priority_queue<Task> taskQueue; // Queue of tasks sorted by priority
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
    std::vector<std::thread> workers; // Thread pool

public:
    // Constructor: create threads and start worker loop
    TaskScheduler(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this]() { this->worker_thread(); });
        }
    }

    // Destructor: stops all threads safely
    ~TaskScheduler() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
            cv.notify_all(); // Wake up all waiting threads
        }
        for (auto& t : workers) {
            if (t.joinable())
                t.join(); // Wait for thread to finish
        }
    }

    // Add a new task to the scheduler
    void add_task(Task&& task) {
        std::unique_lock<std::mutex> lock(mtx);
        taskQueue.push(std::move(task));
        cv.notify_one(); // Notify one waiting thread
    }

    // Function run by each worker thread
    void worker_thread() {
        while (true) {
            Task task;

            {
                std::unique_lock<std::mutex> lock(mtx);
                // Wait until there’s a task or stop is true
                cv.wait(lock, [&] { return stop || !taskQueue.empty(); });

                // If stopping and no tasks left, exit the loop
                if (stop && taskQueue.empty()) break;

                // Get the highest priority task
                task = std::move(const_cast<Task&>(taskQueue.top()));
                taskQueue.pop();
            }

            try {
                // Wait for dependencies to finish
                for (auto& dep : task.dependencies) {
                    dep.wait();
                }

                // Execute task
                task.func();
                task.prom.set_value(); // Mark task as done
            } catch (...) {
                // If task throws, store the exception
                try {
                    task.prom.set_exception(std::current_exception());
                } catch (...) {}
            }
        }
    }
};

int main() {
    TaskScheduler scheduler(4); // Create a scheduler with 4 threads

    // Task 1
    Task task1;
    task1.id = 1;
    task1.priority = 2;
    task1.func = [] {
        std::cout << "Task 1 started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Task 1 completed\n";
    };
    auto fut1 = task1.get_future();

    // Task 2
    Task task2;
    task2.id = 2;
    task2.priority = 3;
    task2.func = [] {
        std::cout << "Task 2 started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Task 2 completed\n";
    };
    auto fut2 = task2.get_future();

    // Task 3 depends on task 1 and 2
    Task task3;
    task3.id = 3;
    task3.priority = 1;
    task3.dependencies = {fut1, fut2};
    task3.func = [] {
        std::cout << "Task 3 (depends on 1 and 2) started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Task 3 completed\n";
    };

    // Task 4 will throw an error
    Task task4;
    task4.id = 4;
    task4.priority = 4;
    task4.func = [] {
        std::cout << "Task 4 (throws error)\n";
        throw std::runtime_error("Error in Task 4");
    };
    auto fut4 = task4.get_future();

    // Submit all tasks to scheduler
    scheduler.add_task(std::move(task1));
    scheduler.add_task(std::move(task2));
    scheduler.add_task(std::move(task3));
    scheduler.add_task(std::move(task4));

    // Catch error from task 4, if any
    try {
        fut4.get();
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Wait so all output is printed before program ends
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}