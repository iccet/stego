#include <QtTest>

#include "stego/abstractencoder.hpp"
#include "stego/lsb.hpp"

class LsbEncodingTestCase : public QObject
{
    Q_OBJECT

    Lsb *_encoder;

public:
    LsbEncodingTestCase() = default;
    ~LsbEncodingTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void encodingTestCase_data();
    void encodingTestCase();

    void cleanupTestCase();
};

void LsbEncodingTestCase::initTestCase_data() {
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
    QTest::newRow("Phrase") << "Hello world";
}

void LsbEncodingTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbEncodingTestCase::init()
{
}

void LsbEncodingTestCase::encodingTestCase_data()
{
    QTest::addColumn<QByteArray>("container");

    QTest::newRow("Empty container") << QByteArray(1000, 0);
    QTest::newRow("Filled container") << QByteArray(1000, 0xf1);
    QTest::newRow("Random byte container") << QByteArray(1000, QRandomGenerator::global()->generate());
}

void LsbEncodingTestCase::encodingTestCase()
{
    QFETCH_GLOBAL(QString, data);
    QFETCH(QByteArray, container);
    QVERIFY(_encoder->encode(data, container));
    QVERIFY(container.count());
}

void LsbEncodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbEncodingTestCase)

#include "tst_lsbencodingtestcase.moc"
