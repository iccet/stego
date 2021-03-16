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

    QRgb *bits = (QRgb *) image.bits();
    int count = image.width() * image.height();

//    QBuffer buffer(&array);
//    buffer.open(QIODevice::WriteOnly);
//    image.save(&buffer, format);

    encoder->encode("test", bits, 100);

    if(image.save("encoded.png"))
        qDebug() << "Successfully saved";

    qDebug() << encoder->decode(bits, count);
    qDebug() << encoder->decode(bits, count);
}


