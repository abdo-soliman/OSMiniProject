#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setting quantum input textline as its only a parameter for RR algorithm
    ui->quantum_input->setVisible(false);
    ui->quantum_label->setVisible(false);

    // adding supported algorithms as combobox options
    ui->algorithms_combo->addItems({
                                       "Non-Preemptive Highest Priority First (HPF)",
                                       "First Come First Served (FCFS)",
                                       "Round Robin with fixed time quantum (RR)",
                                       "Preemptive Shortest Remaining Time Next (SRTN)"
                                   });

    // intializing validators to restrict input to numerical values only
    ui->quantum_input->setValidator(new QIntValidator(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_btn_clicked()
{
    double s = -1;
    double step = -1;
    int quantum = -1;
    string filename = qs2s(ui->file_input->text());

    if (filename == "") {
        QMessageBox msgBox;
        msgBox.setText("Error: invalid filename can't be empty!!!");
        msgBox.exec();
        return;
    }

    if (isDouble(ui->s_input->text()))
        s = qs2d(ui->s_input->text());
    else {
        QMessageBox msgBox;
        msgBox.setText("Error: context switching time must a positive double value!!!");
        msgBox.exec();
        return;
    }

    if (isDouble(ui->step_time_input->text()))
        step = qs2d(ui->step_time_input->text());
    else {
        QMessageBox msgBox;
        msgBox.setText("Error: step time must a positive double value!!!");
        msgBox.exec();
        return;
    }

    if (ui->algorithms_combo->currentIndex() == 2 && ui->quantum_input->text() == "") {
        QMessageBox msgBox;
        msgBox.setText("Error: quantum must a positive integer value!!!");
        msgBox.exec();
        return;
    }
    else if (ui->algorithms_combo->currentIndex() == 2)
        quantum = qs2i(ui->quantum_input->text());

    if (!controller.setParameters(ui->algorithms_combo->currentIndex(), filename, step, s, quantum)) {
        QMessageBox msgBox;
        msgBox.setText("Error: invalid data please make sure that all data meet the required constrains!!!");
        msgBox.exec();
        return;
    }

    // run Scheduler
    controller.run();

}

void MainWindow::on_algorithms_combo_currentIndexChanged(int index)
{
    // if index equal 2 then RR algorithm is selected then show quantum input textline
    if (index == 2) {
        ui->quantum_input->setVisible(true);
        ui->quantum_label->setVisible(true);
    }
    else {
        ui->quantum_input->setVisible(false);
        ui->quantum_label->setVisible(false);
    }
}

void MainWindow::on_browse_btn_clicked()
{
    // get filename from file dialog and set file input textline text to the chosen file
    ui->file_input->setText(QFileDialog::getOpenFileName(this, "Choose A File", "/home/abdo/"));
}
