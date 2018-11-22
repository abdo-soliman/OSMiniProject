#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
using std::vector;
using std::priority_queue;

struct Process {
    int id;
    double arrival_time;
    double burst_time;
    int priority;
    bool is_running = false;
};

class Scheduler {
protected:
    const double step_time;
    const double context_time;
    double current_context_time;
    double current_time;
public:
    Scheduler(double step_time, double context_time) : step_time(step_time), context_time(context_time), current_time(0.0), current_context_time(0.0) { }
    virtual void AddProcess(int id, double arrival_time, double burst_time, int priority) = 0;
    virtual void AddProcess(Process& process) = 0;
    virtual void Step() = 0;
    virtual int GetCurrentlyRunningProcess() = 0;
    virtual bool IsDone() = 0;
};

class HPFSchedulerCompare {
    public:
    static double current_time;
    bool operator() (Process& p1, Process& p2) {
        if (p1.arrival_time <= current_time) {
            if (p2.arrival_time > current_time)  // if p2 is in the future, return false.
                return false;
            else if (p1.priority < p2.priority) // p2 has a higher priority so it comes first.
                return true;
            else if (p1.priority == p2.priority)
                return p1.id > p2.id;
            else
                return false;
        }
        else {
            if (p2.arrival_time > current_time)
                return (p2.arrival_time < p1.arrival_time); // bug
            else
                return true;
        }
    }
};

class HPFScheduler : public Scheduler {
public:
    HPFScheduler(double step_time, double context_time);
    virtual void AddProcess(Process& process);
    virtual void AddProcess(int id, double arrival_time, double burst_time, int priority);
    virtual void Step();
    virtual int GetCurrentlyRunningProcess();
    virtual bool IsDone();
private:
    void SetTopIsRunning(bool is_running);
    void AddToBurstTime(double value);
    priority_queue<Process, std::vector<Process>, HPFSchedulerCompare> queue;
};

class SRTNSchedulerCompare {
    public:
    static double current_time;
    bool operator() (Process& p1, Process& p2) {
        if (p1.arrival_time <= current_time) { 
            if (p2.arrival_time > current_time) // if p2 is in the future, return false.
                return false;
            if (p1.burst_time > p2.burst_time) // p2 is shorter so it comes first
                return true;
            else if (p1.burst_time < p2.burst_time)
                return false;
            else if (p1.priority < p2.priority)
                return true;
            else if (p1.priority == p2.priority)
                return p1.id > p2.id;
            else
                return false;
        }
        else {
            if (p2.arrival_time > current_time)
                return (p2.arrival_time < p1.arrival_time); // bug
            else
                return true;
        }
    }
};


class SRTNScheduler : public Scheduler {
public:
    SRTNScheduler(double step_time, double context_time);
    virtual void AddProcess(Process& process);
    virtual void AddProcess(int id, double arrival_time, double burst_time, int priority);
    virtual void Step();
    virtual int GetCurrentlyRunningProcess();
    virtual bool IsDone();
private:
    void SetTopIsRunning(bool is_running);
    void AddToBurstTime(double value);
    void PrintIDAndPriority();
    priority_queue<Process, std::vector<Process>, SRTNSchedulerCompare> queue;
};

#endif