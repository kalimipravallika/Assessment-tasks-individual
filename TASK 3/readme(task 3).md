
## C++ Multithreaded Task Scheduler ##

This project implements a multi-threaded task scheduler in C++ using a priority queue, `std::thread`, `std::mutex`, and `std::condition_variable`. Tasks are processed concurrently in a thread pool, with support for priority scheduling and task dependencies.

## Features

- Multi-threading support using `std::thread`.
- Task scheduling based on priority (higher priority executes first).
- Task dependencies support (tasks wait for dependent tasks to finish before executing).
- Exception handling for tasks that may fail.
- Efficient synchronization using `std::mutex` and `std::condition_variable`.

## How It Works

1. **Task Representation**
- Each task has an ID, priority, function to execute, and dependencies.
- Tasks use promises and futures to allow dependent tasks to wait.

2. **Task Scheduling**
- Tasks are stored in a priority queue, ensuring higher priority tasks execute first.
- A thread pool is created to process tasks concurrently.

3. **Worker Threads Execution**
- Worker threads continuously fetch tasks from the priority queue.
- Each task waits for dependencies before executing.
- If a task throws an exception, it is caught and stored.

 4. **Testing Various Tasks**
- Demonstrates simple tasks, dependent tasks, and exception handling.
- Handles an invalid task that throws an exception.

## How to Run 

1. Go to (https://www.programiz.com/cpp-programming/online-compiler/)
2. Select `C++` as the language.
3. Write the code.
4. Click `Run` to execute.

## Sample output

Task 2 started
Task 1 started
Task 4 (throws error)
Caught exception: Error in Task 4
Task 2 completed
Task 1 completed
Task 3 (depends on 1 and 2) started
Task 3 completed

