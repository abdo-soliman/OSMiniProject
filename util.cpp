#include "util.h"

string qs2s(QString qs) {
    return qs.toUtf8().constData();
}

int qs2i(QString qs) {
    string s = qs2s(qs);
    return atoi(s.c_str());
}

double qs2d(QString qs) {
    string s = qs2s(qs);
    return atof(s.c_str());
}
