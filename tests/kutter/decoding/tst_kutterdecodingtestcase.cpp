#include <QtTest>

#include "stego/abstractencoder.hpp"
#include "stego/kutter.hpp"

class KutterDecodingTestCase : public QObject
{
    Q_OBJECT

    Kutter *_encoder;
    QByteArray _container;
    QString _data;

public:
    KutterDecodingTestCase() = default;
    ~KutterDecodingTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void decodingTestCase_data();
    void decodingTestCase();

    void cleanupTestCase();
};

void KutterDecodingTestCase::initTestCase_data() {
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
    QTest::newRow("Phrase unicode") << "Hello world!";
    QTest::newRow("Phrase utf-8") << QString::fromUtf8("Привет мир");
}

void KutterDecodingTestCase::initTestCase()
{
    _encoder = new Kutter(this);
}

void KutterDecodingTestCase::init() {
    QFETCH_GLOBAL(QString, data);
    QFETCH(int, height);
    QFETCH(int, width);
    QFETCH(QByteArray, container);

    _data = data;
    _encoder->encode(_data, container);
    _container = container;
}

void KutterDecodingTestCase::decodingTestCase_data()
{
    QTest::addColumn<int>("height");
    QTest::addColumn<int>("width");
    QTest::addColumn<QByteArray>("container");

    QTest::newRow("Filled encoded container") << 25 << 40 << QByteArray(25 * 40, 0xf1);
}

void KutterDecodingTestCase::decodingTestCase()
{
    auto actual = _encoder->decode(_container);
    qDebug() << QString(actual);
}

void KutterDecodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(KutterDecodingTestCase)

#include "tst_kutterdecodingtestcase.moc"
