
### Work-Stealing Task Scheduler in C++ ###

This project implements a thread pool with work stealing in C++. It manages multiple worker threads that execute tasks from their own queues and steal tasks from other queues when idle. This ensures efficient task distribution and minimizes idle time.

## Features

- Multi-threaded execution using `std::thread`.
- Task queuing with thread safety using `std::mutex`.
- Work stealing mechanism, where idle threads take tasks from others.
- Atomic synchronization using `std::atomic<bool>` to manage termination.
- Efficient waiting with std::condition_variable
- Dynamic task assignment across multiple threads.

## How It Works

1. **Task Queue**
- Stores tasks in a thread-safe queue (`std::queue<Task>`).
- The queue is thread-safe using std::mutex.
- Uses std::condition_variable to allow threads to wait efficiently for new tasks.

2. **Worker Threads**
- Each worker thread:
  Waits for tasks in its own queue using cv.wait(...).
- If no task is found and done == false, it continues waiting.
- If the queue is empty and done == true, it exits.
When a worker has no task:
It attempts to steal a task from another worker’s queue using a non-blocking method.

3. **Task Execution & Work Stealing**
- Tasks are pushed by the producer (main thread) into queues .
- Workers consume their own tasks or steal from others.
- All threads keep working until every queue is empty and shutdown is signaled.

4. **Graceful Shutdown**
- Uses `std::atomic<bool>` to signal when execution should stop.
- `std::condition_variable::notify_one()` is called to wake any sleeping threads.
- Ensures threads finish their tasks before stopping.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output

Thread 1 executing task
Thread 0 executing task
  → Task 1 executed by thread 137478097446592
Thread 1 executing task
  → Task 0 executed by thread 137478105839296
Thread 0 executing task
  → Task 3 executed by thread 137478097446592
Thread 1 stole a task
  → Task 2 executed by thread 137478105839296
  → Task 4 executed by thread 137478097446592
All tasks completed.
