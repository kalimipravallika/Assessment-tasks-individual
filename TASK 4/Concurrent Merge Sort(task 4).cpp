
///---- Efficient Generic Concurrent Merge Sort ----///


// Include necessary libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <chrono>
#include <random>

// Use threading only if the size of the array is large enough
const size_t THRESHOLD = 10000;

// Merge two sorted subarrays: arr[left..mid] and arr[mid+1..right]
template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    std::vector<T> temp;
    int i = left, j = mid + 1;

    // Merge elements in order
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    // Add remaining elements from both halves
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    // Copy merged result back into original array
    for (int k = 0; k < static_cast<int>(temp.size()); ++k)
        arr[left + k] = temp[k];
}

// Standard recursive merge sort (no threading)
template <typename T>
void sequentialMergeSort(std::vector<T>& arr, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    sequentialMergeSort(arr, left, mid);
    sequentialMergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Multithreaded merge sort using std::async
template <typename T>
void concurrentMergeSort(std::vector<T>& arr, int left, int right) {
    if (left >= right) return;

    // Use normal sort for small chunks
    if ((right - left) < static_cast<int>(THRESHOLD)) {
        sequentialMergeSort(arr, left, right);
        return;
    }

    int mid = (left + right) / 2;

    // Run left half sorting in a separate thread
    auto futureLeft = std::async(std::launch::async, [&arr, left, mid]() {
        concurrentMergeSort(arr, left, mid);
    });

    // Sort right half in current thread
    concurrentMergeSort(arr, mid + 1, right);

    // Wait for left half to finish
    futureLeft.wait();

    // Merge sorted halves
    merge(arr, left, mid, right);
}

// Measure the execution time of a sorting function
template <typename T>
void benchmark(const std::string& name, void(*sortFunc)(std::vector<T>&, int, int), std::vector<T> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, 0, static_cast<int>(arr.size()) - 1);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << name << " took " << elapsed.count() << " seconds\n";
}

// Generate a vector filled with random integers
std::vector<int> generateRandomData(size_t size) {
    std::vector<int> data(size);
    std::mt19937 rng(42); // Fixed seed for repeatability
    std::uniform_int_distribution<int> dist(1, 1'000'000);

    for (auto& x : data)
        x = dist(rng);

    return data;
}

int main() {
    const size_t SIZE1 = 1'000'000;  // 1 million elements
    const size_t SIZE2 = 5'000'000;  // 5 million elements
    const size_t SIZE3 = 10'000'000; // 10 million elements

    std::cout << "Generating data...\n";

    // Generate three datasets with different sizes
    std::vector<int> data1 = generateRandomData(SIZE1);
    std::vector<int> data2 = generateRandomData(SIZE2);
    std::vector<int> data3 = generateRandomData(SIZE3);

    // Compare sequential vs concurrent merge sort on each dataset
    std::cout << "\nBenchmarking on 1 million elements:\n";
    benchmark("Sequential Merge Sort (1M)", sequentialMergeSort<int>, data1);
    benchmark("Concurrent Merge Sort (1M)", concurrentMergeSort<int>, data1);

    std::cout << "\nBenchmarking on 5 million elements:\n";
    benchmark("Sequential Merge Sort (5M)", sequentialMergeSort<int>, data2);
    benchmark("Concurrent Merge Sort (5M)", concurrentMergeSort<int>, data2);

    std::cout << "\nBenchmarking on 10 million elements:\n";
    benchmark("Sequential Merge Sort (10M)", sequentialMergeSort<int>, data3);
    benchmark("Concurrent Merge Sort (10M)", concurrentMergeSort<int>, data3);

    return 0;
}
