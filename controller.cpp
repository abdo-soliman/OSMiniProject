#include "controller.h"

Controller::Controller() {
    clear_graph = false;
}

bool Controller::setParameters(int algo, string filename, double step_time, double s, int quantum) {
    if (step_time <= 0 || s < 0 || (algo == RR && quantum <= 0))
        return false;

    if (algo == 0) // case HPF
        scheduler = new HPFScheduler(step_time, s);
    else if (algo == 1) // case FCFS not available yet
        scheduler = new FCFSScheduler(step_time, s);
    else if (algo == 2) // case RR
        scheduler = new RRScheduler(step_time, s, quantum);
    else if (algo == 3) // case SRTN
        scheduler = new SRTNScheduler(step_time, s);

    this->filename = filename;
    return true;
}

bool Controller::run() {
    int num_processes;
    int id;
    double arrival_time;
    double burst_time;
    double priority;

    vector<double> keys;
    vector<double> values;

    ifstream input(filename.c_str());
    vector<Process> processes;

    if (input.is_open()) {
        input >> num_processes;

        for (int i = 0; i < num_processes; i++) {
            input >> id >> arrival_time >> burst_time >> priority;
            Process p;
            p.id = id;
            p.arrival_time = arrival_time;
            p.burst_time = burst_time;
            p.priority = priority;
            processes.push_back(p);
            // scheduler->AddProcess(id, arrival_time, burst_time, priority);
        }

    }
    else
        return false;

    keys.push_back(0);
    values.push_back(0);

    while (!processes.empty() || !scheduler->IsDone()) {
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= scheduler->GetCurrentTime()) {
                scheduler->AddProcess(processes[i]);
                processes.erase(processes.begin() + i);
                i = i - 1;
            }
        }
        scheduler->Step();
        cout << scheduler->GetCurrentTime();
        keys.push_back(scheduler->GetCurrentTime());
        values.push_back(scheduler->GetCurrentlyRunningProcess());
    }

    keys.push_back(scheduler->GetCurrentTime());
    values.push_back(0);

    if (clear_graph)
        delete g;

    plot(keys, values);

    ofstream output("statistics.csv");
    if (output.is_open())
        scheduler->PrintStatistics(output);

    return true;
}

void Controller::plot(vector<double> keys, vector<double> values) {
    clear_graph = true;
    g  = new Graph;
    g->setKeys(keys);
    g->setValues(values);

    g->setXLabel("time");
    g->setYLabel("PID");

//    g.setXRange(x_range.first, x_range.second);
//    g.setYRange(y_range.first, y_range.second);

    g->setName("Scheduling Processes");

    g->plot();

    g->show();
}
