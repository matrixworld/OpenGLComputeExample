#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer,SIGNAL(timeout()),ui->openGLWidget,SLOT(update()));
    timer.start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}
