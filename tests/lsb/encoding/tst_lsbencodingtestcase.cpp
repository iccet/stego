#include <QtTest>

#include "../../../src/abstractencoder.hpp"
#include "../../../src/lsb.hpp"

class LsbEncodingTestCase : public QObject
{
    Q_OBJECT

    QString _current_path = QDir::currentPath();
    Lsb *_encoder;
    QByteArray _container;
    QString _data;

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
}

void LsbEncodingTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbEncodingTestCase::init() {
    QFETCH_GLOBAL(QString, data);
    QFETCH(QByteArray, container);

    qDebug() << "Data :" << data;
    qDebug() << "Container:" << container;

    _data = data;
    _container = container;
}

void LsbEncodingTestCase::encodingTestCase_data()
{
    QTest::addColumn<QByteArray>("container");

    QTest::newRow("Empty container") << QByteArray(100, 0);
    QTest::newRow("Filled container") << QByteArray(100, 0xf1);
    QTest::newRow("Random byte container") << QByteArray(100, QRandomGenerator::global()->generate());
}

void LsbEncodingTestCase::encodingTestCase()
{
    _encoder->encode(_data, _container);
    qDebug() << _container;

    QVERIFY(_container.count());
}

void LsbEncodingTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbEncodingTestCase)

#include "tst_lsbencodingtestcase.moc"
