#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <stdlib.h>
#include <string>
using namespace std;

// function that converts QString to std::string
string qs2s(QString qs);

// function that converts QString to int
int qs2i(QString qs);

// function that converts QString to double
double qs2d(QString qs);

// function that checks if a string value is double or not
bool isDouble(QString qs);

#endif // UTIL_H
