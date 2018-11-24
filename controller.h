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
    Controller();
    bool setParameters(int algo, string filename, double step_time, double s, int quantum = 0);
    bool run();
    void plot(vector<double> keys, vector<double> values);

private:
    Scheduler* scheduler;
    string filename;
    Graph* g;
    bool clear_graph;
};

#endif // CONTROLLER_H
