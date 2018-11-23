#include <iostream>
#include "scheduler/ProcessGenerator.h"
#include "scheduler/Scheduler.h"
#include <fstream>
#include <iomanip>
using namespace std;

void TestScheduler(ifstream& input, Scheduler* scheduler) {
    int num_processes = 0;
    input >> num_processes;
    vector<Process> processes;
    cout << setw(6) << "pid\tarrival\tburst\tpriority\n";
    double step_time = scheduler->GetStepTime();
    for (int i = 0; i < num_processes; i++) {
        int pid;
        double arrival_time;
        double burst_time;
        int priority;
        input >> pid >> arrival_time >> burst_time >> priority;
        cout << setw(6) << pid << "\t" << arrival_time << "\t" <<  burst_time << "\t" << priority << "\n";
        Process p;
        p.id = pid;
        p.arrival_time = arrival_time;
        p.burst_time = burst_time;
        p.priority = priority;
        processes.push_back(p);
    }
    cout << "\n\n";
    while (!processes.empty() || !scheduler->IsDone()) {
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= scheduler->GetCurrentTime())
            {
                scheduler->AddProcess(processes[i]);
                processes.erase(processes.begin() + i);
                i = i - 1;
            }
        }
        scheduler->Step();
        cout << "t = " << setw(4) << scheduler->GetCurrentTime() - 1 << ":\t" << scheduler->GetCurrentlyRunningProcess() << "\n";
    }
    cout << "\n";
    scheduler->PrintStatistics();
}


int main()
{
    ifstream input;
    /*
    ofstream output; 
    output.open("output.txt");
    input.open("input.txt");
    try {
        GenerateProcesses(input, output);
    } catch (const char* e) {
        cout << "Could not generate processes. " << e;
    }
    input.close();
    output.close();
    */
    input.open("test.txt");
    Scheduler* scheduler = new RRScheduler(1, 1, 2);
    TestScheduler(input, scheduler);
    input.close();
    return 0;
}