#include <iostream>
#include <fstream>
#include <string>
#include "ProcessGenerator.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc < 3)
        cout << "Error: missing file names, too few arguments" << endl;
    else if (argc > 3)
        cout << "Error: too many arguments" << endl;

    ifstream input(argv[1]);
    ofstream output(argv[2]);
    
    if (input.is_open() && output.is_open())
        GenerateProcesses(input, output);
    else
        cout << "Error: can't open file please make sure file names are valid" << endl;

    return 0;
}