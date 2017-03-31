#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::quit_clicked() {
    emit quit();
}
