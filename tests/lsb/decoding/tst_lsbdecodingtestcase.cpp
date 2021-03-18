#include <QtTest>

#include "../../../src/abstractencoder.hpp"
#include "../../../src/lsb.hpp"

class LsbDecodingTestCase : public QObject
{
    Q_OBJECT

    QString _current_path = QDir::currentPath();
    Lsb *_encoder;
    QByteArray _container;
    QString _data;

    const QByteArray Empty = QByteArray(100, 0);
    const QByteArray Filled = QByteArray(100, 0xf1);

public:
    LsbDecodingTestCase() = default;
    ~LsbDecodingTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void decodingTestCase_data();
    void decodingTestCase();

    void cleanupTestCase();
};

void LsbDecodingTestCase::initTestCase_data() {
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
}

void LsbDecodingTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbDecodingTestCase::init() {
    QFETCH_GLOBAL(QString, data);
    QFETCH(QByteArray, container);

    qDebug() << "Data :" << data;
//    qDebug() << "Container:" << container;

    _data = data;
    _encoder->encode(_data, container);
    _container = container;
}

void LsbDecodingTestCase::decodingTestCase_data()
{
    QTest::addColumn<QByteArray>("container");

    QTest::newRow("Empty encoded container") << Empty;
//    QTest::newRow("Filled encoded container") << Filled;
}

void LsbDecodingTestCase::decodingTestCase()
{
    auto actual = _encoder->decode(_container);
    qDebug() << actual;

    QCOMPARE(QString(actual), _data);
}

void LsbDecodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbDecodingTestCase)

#include "tst_lsbdecodingtestcase.moc"
