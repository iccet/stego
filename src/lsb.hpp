#ifndef LSB_HPP
#define LSB_HPP

#include <QObject>
#include "abstractencoder.hpp"

class Lsb : public QObject, public AbstractEncoder
{
    Q_OBJECT
    Q_INTERFACES(AbstractEncoder)

public:
    explicit Lsb(QObject *parent = nullptr);
    virtual ~Lsb() = default;

    void encode(QString data, QByteArray &container) override;
    void encode(QString data, QRgb *container, int size) override;
    QByteArray decode(QRgb *container, int size) override;
    QByteArray decode(QByteArray &container) override;
};

#endif // LSB_HPP
