#include "Scheduler.h"
#include <iostream>
using std::cout;

double HPFSchedulerCompare::current_time = 0.0;
double RRSchedulerCompare::current_time = 0.0;
double SRTNSchedulerCompare::current_time = 0.0;

HPFScheduler::HPFScheduler(double step_time, double context_time) : Scheduler(step_time, context_time) {
    HPFSchedulerCompare::current_time = current_time;
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
                ProcessFired(current, true);
                AddToBurstTime(-1.0 * step_time);
            }
        }
        if (current_context_time <= 0) {
            bool was_running = current.is_running;
            SetTopIsRunning(true);
            if (!was_running)
                ProcessFired(queue.top(), false);
        }
    }
    current_time += step_time;
    HPFSchedulerCompare::current_time = current_time;
}

int HPFScheduler::GetCurrentlyRunningProcess() {
    return ((queue.empty() || !queue.top().is_running) ? 0 : queue.top().id);
}

bool HPFScheduler::IsDone() {
    return queue.empty();
}

RRScheduler::RRScheduler(double step_time, double context_time, int quantum) : Scheduler(step_time, context_time) {
    RRSchedulerCompare::current_time = current_time;
    this->quantum = quantum;
    this->current_quantum = quantum * step_time;
}

void RRScheduler::AddProcess(Process& process) {
    queue.push(process);
}

void RRScheduler::AddProcess(int id, double arrival_time, double burst_time, int priority) {
    Process process;
    process.id = id; // Add check here.
    process.arrival_time = arrival_time;
    process.burst_time = burst_time;
    process.priority = priority;
    AddProcess(process);
}

void RRScheduler::SetTopIsRunning(bool is_running) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.is_running = is_running && (process.arrival_time <= current_time);
    queue.push(process);
}

void RRScheduler::AddToBurstTime(double value) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.burst_time += value;
    queue.push(process);
}

void RRScheduler::Step() {
    if (current_context_time > 0)
        current_context_time -= step_time;
    if (!queue.empty()) {
        Process current = queue.top();
        if (current.is_running) {
            current_quantum -= step_time;
            if (current.burst_time - step_time <= 0) {
                queue.pop();
                current_context_time = context_time;
                current_quantum = quantum * step_time;
            }
            else if (current_quantum <= 0) {
                current.arrival_time = current_time - step_time;
                current.is_running = false;
                current.burst_time -= step_time;
                queue.pop();
                queue.push(current);
                current_context_time = context_time;
                current_quantum = quantum * step_time;
            }
            else {
                AddToBurstTime(-1.0 * step_time);
                ProcessFired(current, true);
            }
        }
        if (current_context_time <= 0) {
            bool was_running = queue.top().is_running;
            SetTopIsRunning(true);
            if (!was_running)
                ProcessFired(queue.top(), false);
        }
    }
    current_time += step_time;
    RRSchedulerCompare::current_time = current_time;
}

int RRScheduler::GetCurrentlyRunningProcess() {
    return ((queue.empty() || !queue.top().is_running) ? 0 : queue.top().id);
}

bool RRScheduler::IsDone() {
    return queue.empty();
}

FCFSScheduler::FCFSScheduler(double step_time, double context_time) : Scheduler(step_time, context_time) {
    RRSchedulerCompare::current_time = current_time;
}

void FCFSScheduler::AddProcess(Process& process) {
    queue.push(process);
}

void FCFSScheduler::AddProcess(int id, double arrival_time, double burst_time, int priority) {
    Process process;
    process.id = id; // Add check here.
    process.arrival_time = arrival_time;
    process.burst_time = burst_time;
    process.priority = priority;
    AddProcess(process);
}

void FCFSScheduler::SetTopIsRunning(bool is_running) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.is_running = is_running && (process.arrival_time <= current_time);
    queue.push(process);
}

void FCFSScheduler::AddToBurstTime(double value) {
    if (queue.empty())
        return;
    Process process = queue.top();
    queue.pop();
    process.burst_time += value;
    queue.push(process);
}

void FCFSScheduler::Step() {
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
                ProcessFired(current, true);
                AddToBurstTime(-1.0 * step_time);
            }
        }
        if (current_context_time <= 0) {
            bool was_running = current.is_running;
            SetTopIsRunning(true);
            if (!was_running)
                ProcessFired(queue.top(), false);
        }
    }
    current_time += step_time;
    RRSchedulerCompare::current_time = current_time;
}

int FCFSScheduler::GetCurrentlyRunningProcess() {
    return ((queue.empty() || !queue.top().is_running) ? 0 : queue.top().id);
}

bool FCFSScheduler::IsDone() {
    return queue.empty();
}


SRTNScheduler::SRTNScheduler(double step_time, double context_time) : Scheduler(step_time, context_time) {
    SRTNSchedulerCompare::current_time = current_time;
}

void SRTNScheduler::AddProcess(Process& process) {
    bool currentQueueState = !queue.empty(); //queue.top().is_running;
    if (currentQueueState) {
        Process previous = queue.top();
        previous.arrival_time = current_time;
        previous.is_running = false;
        previous.burst_time -= step_time;
        queue.pop();
        queue.push(process);
        queue.push(previous);
        if (previous.id == queue.top().id) {
            queue.pop();
            previous.is_running = true;
            previous.burst_time += step_time;
            queue.push(previous);
        }
        else {
            current_context_time = context_time + step_time;
        }
    }
    else {
        queue.push(process);
    }
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
    process.arrival_time = current_time;
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
                ProcessFired(current, true);
                AddToBurstTime(-1.0 * step_time);
                int new_pid = queue.top().id;
                // Is a context change in order? If so, change the context time.
                if (new_pid != original_pid)
                    current_context_time = context_time;
            }
        }
        if (current_context_time <= 0) {
            bool was_running = !queue.empty() && current.is_running;
            SetTopIsRunning(true);
            if (!was_running)
                ProcessFired(queue.top(), false);
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