#ifndef KUTTER_HPP
#define KUTTER_HPP

#include <QObject>
#include <QDebug>
#include <QRgb>
#include <QColor>
#include <QBitArray>

#include "abstractencoder.hpp"

class Kutter : public QObject, public AbstractEncoder
{
    Q_OBJECT
public:
    explicit Kutter(QObject *parent = nullptr);

    bool encode(QString data, QByteArray &container) override;
    bool encode(QString data, uchar *container, int size) override;
};

#endif // KUTTER_HPP
