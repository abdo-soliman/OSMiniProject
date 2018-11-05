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
    ui->s_input->setValidator(new QDoubleValidator(this));
    ui->quantum_input->setValidator(new QDoubleValidator(this));

    // intialzing controller
    this->control = controller();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_btn_clicked()
{
    // testing if values are passed and casted to basic c++ data types properly
    this->control.setFileName(qs2s(ui->file_input->text()));
    this->control.testCasting(qs2d(ui->s_input->text()), qs2i(ui->quantum_input->text()));
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
