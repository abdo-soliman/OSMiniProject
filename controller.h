#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include "graph.h"
#include "scheduler/Scheduler.h"
using std::vector;

enum algorithm {
    HPF,
    FCFS,
    RR,
    SRTN
};

class Controller {
public:
    bool setParameters(int algo, string filename, double step_time, double s, int quantum = 0);
    bool run();
    void plot(vector<double> keys, vector<double> values);

private:
    Scheduler* scheduler;
    string filename;
    Graph g;
};

#endif // CONTROLLER_H
