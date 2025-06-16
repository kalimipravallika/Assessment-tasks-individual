
///---- Thread-Safe Lock-Free Smart Pointer ----///

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>
#include <random>   
#include <algorithm> 
#include <memory>  

// ==== Custom Lock-Free Smart Pointer Class ====
template <typename T>
class LockFreeSharedPtr {
private:
    // Control block holds a pointer and an atomic reference counter
    struct ControlBlock {
        std::atomic<size_t> ref_count;
        T* ptr;

        ControlBlock(T* p) : ref_count(1), ptr(p) {}
    };

    ControlBlock* control;  // Points to the shared control block

public:
    // Constructor: create control block if pointer is given
    explicit LockFreeSharedPtr(T* p = nullptr) {
        if (p)
            control = new ControlBlock(p);
        else
            control = nullptr;
    }

    // Copy constructor: increase ref count
    LockFreeSharedPtr(const LockFreeSharedPtr& other) {
        control = other.control;
        if (control) {
            control->ref_count.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // Move constructor: transfer ownership
    LockFreeSharedPtr(LockFreeSharedPtr&& other) noexcept {
        control = other.control;
        other.control = nullptr;
    }

    // Copy assignment
    LockFreeSharedPtr& operator=(const LockFreeSharedPtr& other) {
        if (this != &other) {
            this->~LockFreeSharedPtr();  // cleanup current
            control = other.control;
            if (control) {
                control->ref_count.fetch_add(1, std::memory_order_relaxed);
            }
        }
        return *this;
    }

    // Destructor: decrement ref count, delete if last reference
    ~LockFreeSharedPtr() {
        if (control) {
            if (control->ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete control->ptr;
                delete control;
            }
        }
    }

    // Accessor methods
    T* get() const { return control ? control->ptr : nullptr; }
    T& operator*() const { return *get(); }
    T* operator->() const { return get(); }

    // Returns how many references exist
    size_t use_count() const {
        return control ? control->ref_count.load(std::memory_order_relaxed) : 0;
    }
};

// ==== Simple Test Object ====
struct TestData {
    int value;
    TestData(int v) : value(v) {}
};

// ==== Function to Test Copies & Shuffling in Threads ====
void stress_test(int thread_id, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        LockFreeSharedPtr<TestData> ptr(new TestData(i));  // create shared pointer
        std::vector<LockFreeSharedPtr<TestData>> copies;

        // Create multiple copies of the same pointer
        for (int j = 0; j < 10; ++j) {
            copies.emplace_back(ptr);
        }

        // Randomly shuffle the copies
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(copies.begin(), copies.end(), g);
    }
}

// ==== Benchmark Shared Pointer Creation Across Threads ====
template <typename SmartPtrFactory>
void benchmark(const std::string& label, SmartPtrFactory smart_ptr_factory) {
    const int num_threads = 8;
    const int iterations = 5000;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    // Launch threads to test how quickly shared pointers can be created/copied
    for (int i = 0; i < num_threads; ++i)
        threads.emplace_back([&, i]() {
            for (int j = 0; j < iterations; ++j) {
                auto ptr = smart_ptr_factory(new TestData(j));
                std::vector<decltype(ptr)> copies;
                for (int k = 0; k < 10; ++k)
                    copies.emplace_back(ptr);
            }
        });

    // Wait for all threads to finish
    for (auto& t : threads)
        t.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur = end - start;

    // Show how long the test took
    std::cout << label << " Time: " << dur.count() << " seconds\n";
}

// ==== Main Function ====
int main() {
    std::cout << "=== Stress Testing Lock-Free Smart Pointer ===\n";
    {
        // Run multiple threads to test reliability under load
        std::vector<std::thread> threads;
        for (int i = 0; i < 8; ++i)
            threads.emplace_back(stress_test, i, 1000);
        for (auto& t : threads)
            t.join();
        std::cout << "Stress test completed successfully.\n";
    }

    // Compare performance of custom vs standard smart pointers
    std::cout << "\n=== Benchmarking ===\n";
    benchmark("LockFreeSharedPtr", [](TestData* p) { return LockFreeSharedPtr<TestData>(p); });
    benchmark("std::shared_ptr", [](TestData* p) { return std::shared_ptr<TestData>(p); });

    return 0;
}
