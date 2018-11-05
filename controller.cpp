#include "controller.h"

controller::controller() {
    // empty contructor
}

bool controller::setAlgorithm(algorithm algo) {
    if (algo < 0 || algo > 3)
        return false;

    this->algo = algo;
    return true;
}

void controller::setFileName(string name) {
    this->filename = name;
}

void controller::testCasting(int num1, int num2) {
    ofstream output ("file");

    if (output.is_open()) {
        // print file name in a file to make sure it's casted properly to std::string
        output << this->filename << "\n";

        /* - print numbers in a file and add any integer value to them to make sure they casted properly to numbers
           - if no numbers are passed defualt values would be printed in file
           - expected output in case if errors is either garbage values or exception */
        output << (num1+5) << "\n";
        output << (num2+2) << "\n";
    }

}
