#ifndef LSB_HPP
#define LSB_HPP

#include <QObject>
#include <QDataStream>

#include "bits.hpp"
#include "abstractencoder.hpp"

class Lsb : public QObject, public AbstractEncoder
{
    Q_OBJECT
    Q_INTERFACES(AbstractEncoder)
public:
    using Base = AbstractEncoder;

private:
    inline int channel(int bitIndex);

public:

    explicit Lsb(QObject *parent = nullptr);
    virtual ~Lsb() = default;

    bool encode(QString data, QByteArray &container) override;

    QByteArray decode(const QByteArray &container) override;
};

#endif // LSB_HPP
