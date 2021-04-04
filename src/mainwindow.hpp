#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>
#include <QRgb>
#include <QImageReader>
#include <QStandardPaths>

#include "stego/kutter.hpp"
#include "stego/lsb.hpp"
#include "stego/abstractencoder.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace Stg;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();

private:
    Ui::MainWindow *ui;
    AbstractEncoder *encoder;
};
#endif // MAINWINDOW_HPP
