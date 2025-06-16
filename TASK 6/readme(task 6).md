
### Work-Stealing Task Scheduler in C++ ###

This project implements a thread pool with work stealing in C++. It manages multiple worker threads that execute tasks from their own queues and steal tasks from other queues when idle. This ensures efficient task distribution and minimizes idle time.

## Features

- Multi-threaded execution using `std::thread`.
- Task queuing with thread safety using `std::mutex`.
- Work stealing mechanism, where idle threads take tasks from others.
- Atomic synchronization using `std::atomic<bool>` to manage termination.
- Dynamic task assignment across multiple threads.

## How It Works

1. **Task Queue**
- Stores tasks in a thread-safe queue (`std::queue<Task>`).
- Provides `push/pop operations with locking` to prevent race conditions.

2. **Worker Threads**
- Each worker retrieves tasks from its own queue.
- If no task is available, it `steals` from another queue.
- Uses `std::this_thread::sleep_for` to avoid busy-waiting.

3. **Task Execution & Work Stealing**
- Tasks are added to individual thread queues.
- Threads execute their own tasks or steal from others.
- Execution continues until all tasks are completed.

4. **Graceful Shutdown**
- Uses `std::atomic<bool>` to signal when execution should stop.
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
