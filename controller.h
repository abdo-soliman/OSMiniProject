#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <fstream>
using namespace std;

enum algorithm {
    HPF,
    FCFS,
    RR,
    SRTN
};

class controller {
public:
    controller();
    bool setAlgorithm(algorithm algo);
    void setFileName(string name);
    void testCasting(int num1=0, int num2=0);

private:
    algorithm algo;
    string filename;
};

#endif // CONTROLLER_H
