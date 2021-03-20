#include <QtTest>

#include "../../../src/abstractencoder.hpp"
#include "../../../src/lsb.hpp"

class LsbDecodingTestCase : public QObject
{
    Q_OBJECT

    Lsb *_encoder;
    QByteArray _container;
    QString _data;

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
    QTest::newRow("Phrase unicode") << "Hello world!";
    QTest::newRow("Phrase utf-8") << QString::fromUtf8("Привет мир");
}

void LsbDecodingTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbDecodingTestCase::init() {
    QFETCH_GLOBAL(QString, data);
    QFETCH(QByteArray, container);

    _data = data;
    _encoder->encode(_data, container);
    _container = container;
}

void LsbDecodingTestCase::decodingTestCase_data()
{
    QTest::addColumn<QByteArray>("container");

    QTest::newRow("Empty encoded container") << QByteArray(1000, 0);
    QTest::newRow("Filled encoded container") << QByteArray(1000, 0xf1);
}

void LsbDecodingTestCase::decodingTestCase()
{
    auto actual = _encoder->decode(_container);
    QCOMPARE(QString(actual), _data);
}

void LsbDecodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbDecodingTestCase)

#include "tst_lsbdecodingtestcase.moc"
