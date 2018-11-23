#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
using namespace std;
using std::vector;
using std::priority_queue;
using std::unordered_map;

struct Process {
    int id;
    double arrival_time;
    double burst_time;
    int priority;
    bool is_running = false;
};

struct ProcessStatistics {
    double wait_time = 0.0;
    double burst_time = 0.0;
    double GetTurnAroundTime() { return wait_time + burst_time; }
    double GetWeightedTATime() { return GetTurnAroundTime() / burst_time; }
};

class Scheduler {
protected:
    const double step_time;
    const double context_time;
    double current_context_time;
    double current_time;
    unordered_map<int, ProcessStatistics> process_statistics;
public:
    Scheduler(double step_time, double context_time) : step_time(step_time), context_time(context_time), current_time(0), current_context_time(0.0) { }
    virtual void AddProcess(int id, double arrival_time, double burst_time, int priority) = 0;
    virtual void AddProcess(Process& process) = 0;
    virtual void Step() = 0;
    virtual int GetCurrentlyRunningProcess() = 0;
    virtual bool IsDone() = 0;
    double GetCurrentTime() { return current_time; }
    const double GetStepTime() { return step_time; }
    void ProcessFired(const Process& p, bool ranPreviousStep) 
    {
        //cout << "\t\t\t" << p.id << "\t" << p.is_running << "\t" << ranPreviousStep << "\n";
        if (!ranPreviousStep)
            process_statistics[p.id].wait_time += (current_time - p.arrival_time); 
        process_statistics[p.id].burst_time += step_time;
    }
    void PrintStatistics()
    {
        if (process_statistics.empty())
            return; // nothing to print.
        cout << "pid\twait\tburst\tTA\tweiTA\n";
        int numProcesses = 0;
        double averageTA = 0.0;
        double averageWTA = 0.0;
        for (auto& it : process_statistics) {
            ProcessStatistics& ps = it.second;
            cout << it.first << "\t" << ps.wait_time << "\t" << ps.burst_time << "\t" << ps.GetTurnAroundTime() << "\t" << ps.GetWeightedTATime() << "\n";
            numProcesses += 1;
            averageTA += ps.GetTurnAroundTime();
            averageWTA += ps.GetWeightedTATime();
        }
        averageTA /= numProcesses;
        averageWTA /= numProcesses;
    }
};

class HPFSchedulerCompare {
    public:
    static double current_time;
    bool operator() (Process& p1, Process& p2) {
        if (p1.arrival_time <= current_time) {
            if (p2.arrival_time > current_time)  // if p2 is in the future, return false.
                return false;
            else if (p1.is_running) // p1 is running and we are non-preemptive, so ! (p1 < p2)
                return false;
            else if (p2.is_running)
                return true;
            else if (p1.priority < p2.priority) // p2 has a higher priority so it comes first.
                return true;
            else if (p1.priority == p2.priority)
                return p1.id > p2.id;
            else
                return false;
        }
        else {
            if (p2.arrival_time > current_time)
                if (p2.arrival_time == p1.arrival_time)
                    return p1.id > p2.id;
                else
                    return (p2.arrival_time < p1.arrival_time);
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

class RRSchedulerCompare {
    public:
    static double current_time;
    bool operator() (Process& p1, Process& p2) {
        if (p1.arrival_time <= current_time) {
            if (p2.arrival_time > current_time)  // if p2 is in the future, return false.
                return false;
            else if (p2.arrival_time < p1.arrival_time) // p1 arrives later than p2 -> p1 < p2
                return true;
            else if (p2.arrival_time > p1.arrival_time)
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
                if (p2.arrival_time == p1.arrival_time)
                    return p1.id > p2.id;
                else
                    return (p2.arrival_time < p1.arrival_time);
            else
                return true;
        }
    }
};

class RRScheduler : public Scheduler {
public:
    RRScheduler(double step_time, double context_time, int quantum);
    virtual void AddProcess(Process& process);
    virtual void AddProcess(int id, double arrival_time, double burst_time, int priority);
    virtual void Step();
    virtual int GetCurrentlyRunningProcess();
    virtual bool IsDone();
private:
    void SetTopIsRunning(bool is_running);
    void AddToBurstTime(double value);
    int quantum;
    double current_quantum;
    priority_queue<Process, std::vector<Process>, RRSchedulerCompare> queue;
};

class FCFSScheduler : public Scheduler {
public:
    FCFSScheduler(double step_time, double context_time);
    virtual void AddProcess(Process& process);
    virtual void AddProcess(int id, double arrival_time, double burst_time, int priority);
    virtual void Step();
    virtual int GetCurrentlyRunningProcess();
    virtual bool IsDone();
private:
    void SetTopIsRunning(bool is_running);
    void AddToBurstTime(double value);
    priority_queue<Process, std::vector<Process>, RRSchedulerCompare> queue;
};

class SRTNSchedulerCompare {
    public:
    static double current_time;
    bool operator() (Process& p1, Process& p2) {
        //cout << "Comparing " << p1.id << " and " << p2.id << "\n";
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
                if (p2.arrival_time == p1.arrival_time)
                    return p1.id > p2.id;
                else
                    return (p2.arrival_time < p1.arrival_time);
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
    void FixUpContextSwitching(Process& prev);
    priority_queue<Process, std::vector<Process>, SRTNSchedulerCompare> queue;
};

#endif // SCHEDULER_H