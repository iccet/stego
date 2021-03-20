#include <QtTest>

#include "../../../src/abstractencoder.hpp"
#include "../../../src/lsb.hpp"

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
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
    QTest::newRow("Phrase") << "Hello world";
}

void LsbRawDecodingTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbRawDecodingTestCase::init()
{
}

void LsbRawDecodingTestCase::imageTestCase_data()
{
    Q_INIT_RESOURCE(data);
    QTest::addColumn<QImage>("image");

    QDirIterator it(":jpg", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto file = it.next();
        QTest::newRow(QString("Jpg %1").arg(it.fileName()).toLocal8Bit()) << QImage(file);
    }
}

void LsbRawDecodingTestCase::imageTestCase()
{
    QFETCH_GLOBAL(QString, data);
    QFETCH(QImage, image);

    QRgb *bits = (QRgb *) image.bits();
    int count = image.width() * image.height();

    QVERIFY(count);
    QVERIFY(_encoder->encode(data, bits, count));
}

void LsbRawDecodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbRawDecodingTestCase)

#include "tst_lsbrawdecodingtestcase.moc"
