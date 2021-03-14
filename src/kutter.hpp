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

    void encode(QString data, QByteArray &container) override;
    void encode(QString data, QRgb *container, int size) override;
};

#endif // KUTTER_HPP
