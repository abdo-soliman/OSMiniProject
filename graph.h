#ifndef GRAPH_H
#define GRAPH_H

/*
 * This class is a simple QWidget with QcustomPlot for plotting Bar Charts
 * Keys represent X axis and Values represent Y axis
*/

#include "qcustomplot.h"
#include <string>
#include <vector>
#include <QWidget>

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT
    bool empty;
    int range_staus;
    QCPBars *my_bars;
    QVector<double> key_data;
    QVector<double> value_data;

public:
    explicit Graph(QWidget *parent = 0);
    void plot();

    void setName(std::string name);

    // set Keys or Values or both
    void setKeys(std::vector<double> keys);
    void setValues(std::vector<double> values);
    void setKeyValue(std::vector<double> keys, std::vector<double> values);

    // append a single value to Keys or Values or both
    void appendKey(double key);
    void appendValue(double value);
    void appendKeyValue(double key, double value);

    // set ranges for X axis or Y axis or both
    void setXRange(int x_bottom, int x_up);
    void setYRange(int y_bottom, int y_up);
    void setRange(int x_bottom, int x_up, int y_bottom, int y_up);

    // set labels for X axis or Y axis or both
    void setXLabel(std::string label);
    void setYLabel(std::string label);
    void setLabels(std::string x_label, std::string y_label);

    // set legend visibility default is visible
    void setLegendVisible(bool option);
    ~Graph();

private:
    Ui::Graph *ui;
};

#endif // GRAPH_H
