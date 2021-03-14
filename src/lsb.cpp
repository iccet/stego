#include "lsb.hpp"

Lsb::Lsb(QObject *parent) : QObject(parent)
{

}

void Lsb::encode(QString data, QByteArray &container)
{
    for (auto i = 0; i < container.size(); i++) {
        container[i] = QColor(20, 150, 200).rgb();
    }
}

void Lsb::encode(QString data, QRgb *container, int size)
{
    foreach(auto byte, data.toLocal8Bit())
    {
        qDebug() << byte;
    }

    for (auto i = 0; i < size; i++) {
        container[i] = QColor(25, 150, 200).rgb();
    }
}
