#ifndef PROCESS_GENERATOR_H
#define PROCESS_GENERATOR_H
#include <iostream>
#include <random>
#include <exception>
using std::ostream;
using std::istream;

template <typename T>
T RectifiedLinear(T value) {
    return (value >= 0) ? value : 0;
}

void GenerateProcesses(int num_processes, double arrival_mean, double arrival_std, double burst_mean, double burst_std, double priority_lambda, ostream& output) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> arrival_dist(arrival_mean, arrival_std);
    std::normal_distribution<> burst_dist(burst_mean, burst_std);
    std::poisson_distribution<int> priority_dist(priority_lambda);
    output << num_processes << "\n";
    for (int i = 0; i < num_processes; i++) {
        double arrival_time = RectifiedLinear(arrival_dist(gen));
        double burst_time = RectifiedLinear(burst_dist(gen));
        burst_time = (burst_time <= 0) ? 0.1 : burst_time; 
        int priority = RectifiedLinear(priority_dist(gen));
        output << (i+1) << " " << arrival_time << " " << burst_time << " " << priority << "\n";
    }
}

void GenerateProcesses(istream& input, ostream& output) {
    int num_processes = 0;
    double arrival_mean = 0.0;
    double arrival_std = 0.0;
    double burst_mean = 0.0;
    double burst_std = 0.0;
    double priority_lambda = 0.0;
    input >> num_processes >> arrival_mean >> arrival_std >> burst_mean >> burst_std >> priority_lambda;
    std::cout << num_processes << " " << arrival_mean << " " << arrival_std << " " << burst_mean << " " << burst_std << " " << priority_lambda << "\n";
    if (num_processes < 0) { throw "Error: Number of processes can not be negative.\n"; }
    if (arrival_std < 0 || burst_std < 0) { throw "Error: standard deviations can not be negative."; }
    GenerateProcesses(num_processes, arrival_mean, arrival_std, burst_mean, burst_std, priority_lambda, output);
}

#endif // PROCESS_GENERATOR_H