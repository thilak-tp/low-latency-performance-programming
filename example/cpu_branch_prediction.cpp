#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Program to check the CPU Branchprediction and the cost of misprediction by the CPU
// Run using g++ -O2 -march=native cpu_branch_prediction.cpp
using namespace std;
using namespace std::chrono;

int main() {
    
    // Creating a list of 1M Numbers
    const int N = 1'000'000;
    vector<int> data(N);

    // Generating random numbers between 0 and 100
    mt19937 rng(1337);
    uniform_int_distribution<int> dist(0, 100);
    for (int& x : data)
        x = dist(rng);

    // -------- Branch-heavy version --------
    // Here we are using an If condition, CPUs tend to predict the answer and tend to miss 
    // so this drops the performance. This is an Unpredictable addition since we are using
    // Random numbers
    auto start1 = steady_clock::now();
    long long sum1 = 0;

    for (int x : data) {
        if (x < 50)
            sum1 += x;
    }

    auto end1 = steady_clock::now();
    // Calculating the difference between the start and the end time to get the duration of execution
    auto time1 = duration_cast<nanoseconds>(end1 - start1).count();

    // -------- Branch-free version --------
    // Here we are using the conditional operator instead, we are avoiding the If statement so prediction
    // is avoided here. This should improve performance
    auto start2 = steady_clock::now();
    long long sum2 = 0;

    for (int x : data) {
        sum2 += (x < 50) ? x : 0;
    }

  
    // Calculating the difference between the start and the end time to get the duration of execution
    auto end2 = steady_clock::now();
    auto time2 = duration_cast<nanoseconds>(end2 - start2).count();

    // Prevent optimization
    cout << "Sum1: " << sum1 << ", Sum2: " << sum2 << endl;

    cout << "Branch-heavy Time: " << time1 << " ns\n";
    cout << "Branch-free Time:  " << time2 << " ns\n";
    cout << "Speedup:           " << (double)time1 / time2 << "x\n";

    return 0;
}

