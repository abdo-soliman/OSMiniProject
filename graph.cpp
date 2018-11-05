#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    my_bars = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);

    // bar chart is empty and range status 0 for no bar chart
    empty = true;
    range_staus = 0;

    // show legend with slightly transparent background brush
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    ui->customPlot->legend->setVisible(true);
}

void Graph::plot() {
    my_bars->setData(key_data, value_data);

    if (!empty) {
        if (range_staus == 0)
            ui->customPlot->rescaleAxes();
        else if (range_staus == 1) {
            double max = value_data[0];
            double min = value_data[0];

            for (int i = 0; i < value_data.size(); i++) {
                if (value_data[i] > max)
                    max = value_data[i];
                if (value_data[i] < min)
                    min = value_data[i];
            }
            setYRange(min, max);
        }
        else if (range_staus == 2) {
            double max = key_data[0];
            double min = key_data[0];

            for (int i = 0; i < key_data.size(); i++) {
                if (key_data[i] > max)
                    max = key_data[i];
                if (key_data[i] < min)
                    min = key_data[i];
            }
            setXRange(min, max);
        }
    }

    ui->customPlot->replot();
}

void Graph::setName(std::string name) {
    my_bars->setName(name.c_str());
}

void Graph::setKeys(std::vector<double> keys) {
    empty = false;
    for (std::vector<double>::iterator it = keys.begin(); it != keys.end(); ++it)
        key_data.append(*it);
}

void Graph::setValues(std::vector<double> values) {
    empty = false;
    for (std::vector<double>::iterator it = values.begin(); it != values.end(); ++it)
        value_data.append(*it);
}

void Graph::setKeyValue(std::vector<double> keys, std::vector<double> values){
    empty = false;
    for (int i = 0; i < keys.size(); i++) {
        key_data.append(keys[i]);
        value_data.append(values[i]);
    }
}

void Graph::appendKey(double key) {
    empty = false;
    key_data.append(key);
}

void Graph::appendValue(double value) {
    empty = false;
    value_data.append(value);
}

void Graph::appendKeyValue(double key, double value) {
    empty = false;
    key_data.append(key);
    value_data.append(value);
}

void Graph::setXRange(int x_bottom, int x_up) {
    if (range_staus == 2)
        range_staus = 3;
    else
        range_staus = 1;

    ui->customPlot->xAxis->setRange(x_bottom, x_up);
}

void Graph::setYRange(int y_bottom, int y_up) {
    if (range_staus == 1)
        range_staus = 3;
    else
        range_staus = 2;

    ui->customPlot->yAxis->setRange(y_bottom, y_up);
}

void Graph::setRange(int x_bottom, int x_up, int y_bottom, int y_up) {
    range_staus = 3;

    ui->customPlot->xAxis->setRange(x_bottom, x_up);
    ui->customPlot->yAxis->setRange(y_bottom, y_up);
}

void Graph::setXLabel(std::string label) {
    ui->customPlot->xAxis->setLabel(label.c_str());
}

void Graph::setYLabel(std::string label) {
    ui->customPlot->yAxis->setLabel(label.c_str());
}

void Graph::setLabels(std::string x_label, std::string y_label) {
    ui->customPlot->xAxis->setLabel(x_label.c_str());
    ui->customPlot->yAxis->setLabel(y_label.c_str());
}

void Graph::setLegendVisible(bool option) {
    if (option)
        ui->customPlot->legend->setVisible(true);
    else
        ui->customPlot->legend->setVisible(false);
}

Graph::~Graph()
{
    delete ui;
}
