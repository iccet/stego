#include <QtTest>

#include "stego/abstractencoder.hpp"
#include "stego/kutter.hpp"

using namespace Stg;

class KutterEncodingTestCase : public QObject
{
    Q_OBJECT

    Kutter *_encoder;

public:
    KutterEncodingTestCase() = default;
    ~KutterEncodingTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void encodingTestCase_data();
    void encodingTestCase();

    void cleanupTestCase();
};

void KutterEncodingTestCase::initTestCase_data() {
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
    QTest::newRow("Phrase") << "Hello world";
}

void KutterEncodingTestCase::initTestCase() {
    _encoder = new Kutter(this);
}

void KutterEncodingTestCase::init()
{
}

void KutterEncodingTestCase::encodingTestCase_data()
{
    QTest::addColumn<QByteArray>("container");

    QTest::newRow("Filled container") << QByteArray(1000, 0xf1);
    QTest::newRow("Random byte container") << QByteArray(1000, QRandomGenerator::global()->generate());
}

void KutterEncodingTestCase::encodingTestCase()
{
    QFETCH_GLOBAL(QString, data);
    QFETCH(QByteArray, container);
    QVERIFY(_encoder->encode(data, container));
    qDebug() << container;
    QVERIFY(container.count());
}

void KutterEncodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(KutterEncodingTestCase)

#include "tst_kutterencodingtestcase.moc"
