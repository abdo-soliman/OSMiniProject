#include "controller.h"

bool Controller::setParameters(int algo, string filename, double step_time, double s, int quantum) {
    if (step_time <= 0 || s < 0 || (algo == RR && quantum <= 0))
        return false;

    if (algo == 0) // case HPF
        scheduler = new HPFScheduler(step_time, s);
//    else if (algo == 1) // case FCFS not available yet
//        scheduler = new FCFSScheduler(step_time, s);
    else if (algo == 2) // case RR
        scheduler = new RRScheduler(step_time, s, quantum);
    else if (algo == 3) // case SRTN
        scheduler = new SRTNScheduler(step_time, s);

    this->filename = filename;
    return true;
}

void Controller::run() {
    // TODO read file and add processes

    while (!scheduler->IsDone())
        scheduler->Step();

    // TODO plot statistics
}

void Controller::plot() {
    // plot some random data for testing need to be replaced with real statistics

    vector<double> keys;
    vector<double> values;

    for (int i = 1; i < 6; i++) {
        keys.push_back(i);
        values.push_back(2*i);
    }

    g.setKeys(keys);
    g.setValues(values);

    g.appendKey(3.5);
    g.appendValue(7);

    g.setXLabel("time");
    g.setYLabel("PID");

    g.setXRange(-3, 10);
    g.setYRange(0, 20);

    g.setName("test graph");

    g.plot();

    g.show();
}
