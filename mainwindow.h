#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "util.h"
#include "controller.h"

using std::string;
using std::cout;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_submit_btn_clicked();

    void on_algorithms_combo_currentIndexChanged(int index);

    void on_browse_btn_clicked();

private:
    Controller controller;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
