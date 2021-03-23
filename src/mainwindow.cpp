#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , encoder(new Lsb)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Select file", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
    QFile file(name);

    QImageReader reader(name);

    Q_ASSERT(reader.canRead());

    auto format = reader.format();
    QImage image = reader.read();

    auto *bits =  image.bits();
    int count = image.width() * image.height();

    if(encoder->encode("hello world", bits, count))
        qDebug() << "Successfully encoded";

    if(image.save("encoded.png"))
        qDebug() << "Successfully saved";

    qDebug() << QString(encoder->decode(bits, count));
}


