
///---- Advanced Thread Pool with Task Scheduling ---- ///

#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

// Task structure
struct Task {
    int id;  
    int priority;  
    std::function<void()> func;  
    std::vector<std::future<void>> dependencies;  // Futures for dependency tracking
    std::promise<void> prom;  // Promise to signal completion (or exception)

    // Get a future from the promise
    std::future<void> get_future() {
        return prom.get_future();
    }

    // Define comparison: lower priority tasks go behind in priority_queue
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

// Scheduler class that runs tasks concurrently
class TaskScheduler {
private:
    std::priority_queue<Task> taskQueue; 
    std::mutex mtx;                       
    std::condition_variable cv;           
    bool stop = false;                    
    std::vector<std::thread> workers;     

public:
    // Constructor: launch worker threads
    TaskScheduler(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this]() { this->worker_thread(); });
        }
    }

    // Destructor: stop threads and join them
    ~TaskScheduler() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
            cv.notify_all();  // Wake up all threads
        }
        for (auto& t : workers) {
            if (t.joinable()) t.join();
        }
    }

    // Add task to queue
    void add_task(Task&& task) {
        std::unique_lock<std::mutex> lock(mtx);
        taskQueue.push(std::move(task));
        cv.notify_one();  // Wake up one thread
    }

    // Worker thread function
    void worker_thread() {
        while (true) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                // Wait until stop or queue is not empty
                cv.wait(lock, [&] { return stop || !taskQueue.empty(); });

                // Exit thread if stopping and no tasks
                if (stop && taskQueue.empty()) break;

                // Get the highest-priority task
                task = std::move(const_cast<Task&>(taskQueue.top()));
                taskQueue.pop();
            }

            try {
                // Wait for dependencies
                for (auto& dep : task.dependencies) {
                    dep.get();  // Wait and throw if dependency failed
                }

                // Run task
                task.func();

                // Mark task as completed
                task.prom.set_value();
            } catch (...) {
                // Store exception in promise
                try {
                    task.prom.set_exception(std::current_exception());
                } catch (...) {}
            }
        }
    }
};

// Main function to demonstrate the scheduler
int main() {
    TaskScheduler scheduler(4);  // Start 4 worker threads

    // Task 1 (no dependencies)
    Task task1;
    task1.id = 1;
    task1.priority = 2;
    task1.func = [] {
        std::cout << "Task 1 started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Task 1 completed\n";
    };
    std::future<void> fut1 = task1.get_future();  // Store future for dependency

    // Task 2 (no dependencies)
    Task task2;
    task2.id = 2;
    task2.priority = 3;
    task2.func = [] {
        std::cout << "Task 2 started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Task 2 completed\n";
    };
    std::future<void> fut2 = task2.get_future();  // Store future for dependency

    // Task 3 (depends on Task 1 and Task 2)
    Task task3;
    task3.id = 3;
    task3.priority = 1;
    task3.dependencies.push_back(std::move(fut1));  // Add Task 1 as dependency
    task3.dependencies.push_back(std::move(fut2));  // Add Task 2 as dependency
    task3.func = [] {
        std::cout << "Task 3 (depends on 1 and 2) started\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Task 3 completed\n";
    };
    std::future<void> fut3 = task3.get_future();  // For optional waiting

    // Task 4 (throws exception)
    Task task4;
    task4.id = 4;
    task4.priority = 4;
    task4.func = [] {
        std::cout << "Task 4 (throws error)\n";
        throw std::runtime_error("Error in Task 4");
    };
    std::future<void> fut4 = task4.get_future();

    // Submit tasks to scheduler
    scheduler.add_task(std::move(task1));
    scheduler.add_task(std::move(task2));
    scheduler.add_task(std::move(task3));
    scheduler.add_task(std::move(task4));

    // Handle exception from Task 4
    try {
        fut4.get();  // This will throw if task4 throws
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    // Wait for dependent task to finish (optional)
    fut3.get();

    // Sleep to allow all tasks to complete before program exits
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
