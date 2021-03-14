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

    QByteArray array = QByteArray::fromRawData((const char*)bits, count);
//    QBuffer buffer(&array);
//    buffer.open(QIODevice::WriteOnly);
//    image.save(&buffer, format);

    encoder->encode("test", bits, count);
    encoder->encode("test", array);

//    for (int p = 0; p < count; p++) {
//        bits[p] = (QRgb)array.at(p);
//    }

    if(image.save("encoded.png"))
        qDebug() << "Successfully saved";
}


