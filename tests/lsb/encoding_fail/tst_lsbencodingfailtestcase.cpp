#include <QtTest>

#include "stego/abstractencoder.hpp"
#include "stego/lsb.hpp"

class LsbEncodingFailTestCase : public QObject
{
    Q_OBJECT

    Lsb *_encoder;

public:
    LsbEncodingFailTestCase() = default;
    ~LsbEncodingFailTestCase() = default;

private slots:
    void initTestCase_data();
    void initTestCase();

    void init();

    void failTestCase();

    void cleanupTestCase();
};

void LsbEncodingFailTestCase::initTestCase_data()
{
    QTest::addColumn<QString>("data");
    QTest::addColumn<QByteArray>("container");
    QTest::addColumn<bool>("success");

    QTest::newRow("Small string") << "test" << QByteArray(1000, 0) << true;
    QTest::newRow("Single char") << "p" << QByteArray(1000, 0) << true;
    QTest::newRow("Huge string") << "Hello world" << QByteArray(100, 0) << false;
}

void LsbEncodingFailTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbEncodingFailTestCase::init()
{
}

void LsbEncodingFailTestCase::failTestCase()
{
    QFETCH_GLOBAL(QString, data);
    QFETCH_GLOBAL(QByteArray, container);
    QFETCH_GLOBAL(bool, success);

    QCOMPARE(_encoder->encode(data, container), success);
}

void LsbEncodingFailTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbEncodingFailTestCase)

#include "tst_lsbencodingfailtestcase.moc"
