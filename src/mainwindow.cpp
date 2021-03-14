#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , kutter()
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

    QImageReader reader(name);

    Q_ASSERT(reader.canRead());

    auto format = reader.format();
    QImage image = reader.read();

    QRgb *bits = (QRgb *) image.bits();
    int count = image.width() * image.height();

    QByteArray array = QByteArray::fromRawData(reinterpret_cast<const char*>(bits), count);
    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, format);

    kutter->encode(bits, count);
//    kutter->encode(arr);

//    for (quint64 p = 0; p < count; p++) {
//        bits[p] = (QRgb)arr.at(p);
//    }

    if(image.save("encoded.png"))
        qDebug() << "Successfully saved";
}


