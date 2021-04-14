#include <QtTest>

#include "stego/abstractencoder.hpp"
#include "stego/kutter.hpp"

class KutterRawDecodingTestCase : public QObject
{
    Q_OBJECT
    Kutter *_encoder;

public:
    KutterRawDecodingTestCase() = default;
    ~KutterRawDecodingTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void imageTestCase_data();
    void imageTestCase();

    void cleanupTestCase();
};

void KutterRawDecodingTestCase::initTestCase_data()
{
    Q_INIT_RESOURCE(data);
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
    QTest::newRow("Phrase") << "Hello world";

    auto file = QFile(":txt/regular.txt");
    file.open(QIODevice::ReadOnly);
    QTest::newRow("Text") << QString(file.readAll());
}

void KutterRawDecodingTestCase::initTestCase()
{
    _encoder = new Kutter(this);
}

void KutterRawDecodingTestCase::init() { }

void KutterRawDecodingTestCase::imageTestCase_data()
{
    QTest::addColumn<QImage>("image");

    QDirIterator it(":jpg", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        auto file = it.next();
        QTest::newRow(QString("Jpg %1").arg(it.fileName()).toLocal8Bit()) << QImage(file);
    }
}

void KutterRawDecodingTestCase::imageTestCase()
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
        QVERIFY(!actual.isEmpty());
    }
}

void KutterRawDecodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(KutterRawDecodingTestCase)

#include "tst_kutterrawdecodingtestcase.moc"
