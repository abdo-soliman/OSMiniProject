#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "controller.h"
#include "util.h"

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
    controller control;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
