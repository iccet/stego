#include <QtTest>

#include "stego/abstractencoder.hpp"
#include "stego/lsb.hpp"

using namespace Stg;

class LsbRawDecodingTestCase : public QObject
{
    Q_OBJECT
    Lsb *_encoder;

public:
    LsbRawDecodingTestCase() = default;
    ~LsbRawDecodingTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();


    void imageTestCase_data();
    void imageTestCase();

    void cleanupTestCase();
};

void LsbRawDecodingTestCase::initTestCase_data() {
    Q_INIT_RESOURCE(data);
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
    QTest::newRow("Phrase") << "Hello world";

    auto file = QFile(":txt/regular.txt");
    file.open(QIODevice::ReadOnly);
    QTest::newRow("Text") << QString(file.readAll());
}

void LsbRawDecodingTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbRawDecodingTestCase::init()
{
}

void LsbRawDecodingTestCase::imageTestCase_data()
{
    QTest::addColumn<QImage>("image");

    QDirIterator it(":jpg", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        auto file = it.next();
        QTest::newRow(QString("Jpg %1").arg(it.fileName()).toLocal8Bit()) << QImage(file);
    }
}

void LsbRawDecodingTestCase::imageTestCase()
{
    QFETCH_GLOBAL(QString, data);
    QFETCH(QImage, image);

    auto *bits = image.bits();
    int count = image.width() * image.height();

    QVERIFY(count);
    QVERIFY(_encoder->Base::encode(data, bits, count));
    QBENCHMARK
    {
        auto actual = _encoder->Base::decode(bits, count);
        QCOMPARE(QString(actual), data);
    }
}

void LsbRawDecodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbRawDecodingTestCase)

#include "tst_lsbrawdecodingtestcase.moc"
