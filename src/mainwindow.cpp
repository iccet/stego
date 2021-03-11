#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionLoad_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Select file", QDir::homePath());
    QFile file(name);

    QImageReader (name);
    qDebug() << file;
}
