#ifndef LSB_HPP
#define LSB_HPP

#include <QObject>
#include "abstractencoder.hpp"

class Lsb : public QObject, public AbstractEncoder
{
    Q_OBJECT
public:
    explicit Lsb(QObject *parent = nullptr);

    void encode(QString data, QByteArray &container) override;
    void encode(QString data, QRgb *container, int size) override;
};

#endif // LSB_HPP
