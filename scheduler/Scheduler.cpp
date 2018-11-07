#include "Scheduler.h"
#include <iostream>
using std::cout;

double HPFSchedulerCompare::current_time = 0.0;
double SRTNSchedulerCompare::current_time = 0.0;

HPFScheduler::HPFScheduler(double step_time, double context_time) : Scheduler(step_time, context_time) {

}

void HPFScheduler::AddProcess(Process& process) {
    queue.push(process);
}

void HPFScheduler::AddProcess(int id, double arrival_time, double burst_time, int priority) {
    Process process;
    process.id = id; // Add check here.
    process.arrival_time = arrival_time;
    process.burst_time = burst_time;
    process.priority = priority;
    AddProcess(process);
}

void HPFScheduler::SetTopIsRunning(bool is_running) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.is_running = is_running && (process.arrival_time <= current_time);
    queue.push(process);
}

void HPFScheduler::AddToBurstTime(double value) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.burst_time += value;
    queue.push(process);
}

void HPFScheduler::Step() {
    if (current_context_time >= 0)
        current_context_time -= step_time;
    if (!queue.empty()) {
        Process current = queue.top();
        if (current.is_running) {
            // If our current process is done, remove it from the queue and set the switching time.
            if (current.burst_time - step_time <= 0) {
                queue.pop();
                current_context_time = context_time;
            } else {
               AddToBurstTime(-1.0 * step_time);
            }
        }
        if (current_context_time <= 0) {
            SetTopIsRunning(true);
        }
    }
    current_time += step_time;
    HPFScheduler::current_time = current_time;
}

int HPFScheduler::GetCurrentlyRunningProcess() {
    return ((queue.empty() || !queue.top().is_running) ? 0 : queue.top().id);
}

bool HPFScheduler::IsDone() {
    return queue.empty();
}

SRTNScheduler::SRTNScheduler(double step_time, double context_time) : Scheduler(step_time, context_time) {
    SRTNSchedulerCompare::current_time = 0.0;
}

void SRTNScheduler::AddProcess(Process& process) {
    queue.push(process);
    //cout << "added " << process.id << " top is " << queue.top().id << "\n";
}

void SRTNScheduler::AddProcess(int id, double arrival_time, double burst_time, int priority) {
    Process process;
    process.id = id; // Add check here.
    process.arrival_time = arrival_time;
    process.burst_time = burst_time;
    process.priority = priority;
    AddProcess(process);
}

void SRTNScheduler::SetTopIsRunning(bool is_running) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.is_running = is_running && (process.arrival_time <= current_time);
    queue.push(process);
}

void SRTNScheduler::AddToBurstTime(double value) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.burst_time += value;
    process.is_running = false;
    queue.push(process);
}

void SRTNScheduler::Step() {
    if (current_context_time >= 0)
        current_context_time -= step_time;
    if (!queue.empty()) {
        Process current = queue.top();
        if (current.is_running) {
            // If our current process is done, remove it from the queue and set the switching time.
            if (current.burst_time - step_time <= 0) {
                queue.pop();
                current_context_time = context_time;
            } else {
                int original_pid = current.id;
                AddToBurstTime(-1.0 * step_time);
                int new_pid = queue.top().id;
                // Is a context change in order? If so, change the context time.
                if (new_pid != original_pid)
                    current_context_time = context_time;
            }
        }
        if (current_context_time <= 0) {
            SetTopIsRunning(true);
        }
    }
    current_time += step_time;
    SRTNSchedulerCompare::current_time = current_time;
}

int SRTNScheduler::GetCurrentlyRunningProcess() {
    return ((queue.empty() || !queue.top().is_running) ? 0 : queue.top().id);
}

bool SRTNScheduler::IsDone() {
    return queue.empty();
}