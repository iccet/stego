#include <QtTest>

#include "../../src/abstractencoder.hpp"
#include "../../src/lsb.hpp"

class LsbTestCase : public QObject
{
    Q_OBJECT

    QString _current_path = QDir::currentPath();
    Lsb *_encoder;
    QByteArray _container;
    QString _data;

    const QByteArray Empty = QByteArray(100, 0);
    const QByteArray Filled = QByteArray(100, 0xf1);

public:
    LsbTestCase() = default;
    ~LsbTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void encodingTestCase_data();
    void encodingTestCase();

    void decodingTestCase_data();
    void decodingTestCase();

    void cleanupTestCase();
};

void LsbTestCase::initTestCase() {
    _encoder = new Lsb(this);
}

void LsbTestCase::initTestCase_data() {
    QTest::addColumn<QString>("data");

    QTest::newRow("Small string") << "test";
    QTest::newRow("Single char") << "p";
}

void LsbTestCase::init() {
    QFETCH_GLOBAL(QString, data);
    QFETCH(QByteArray, container);

    qDebug() << "Data :" << data;
    qDebug() << "Container:" << container;

    _data = data;
    _container = container;
}

void LsbTestCase::encodingTestCase_data()
{
    QTest::addColumn<QByteArray>("container");

    QTest::newRow("Empty container") << Empty;
    QTest::newRow("Filled container") << Filled;
}

void LsbTestCase::encodingTestCase()
{
    QSKIP("Skip encoding");

    _encoder->encode(_data, _container);
    qDebug() << _container;

    QVERIFY(_container.count());
}

void LsbTestCase::decodingTestCase_data()
{
    QTest::addColumn<QByteArray>("container");

    auto empty = QByteArray();
    auto filled = QByteArray();

    copy(Empty, empty);
    copy(Filled, filled);

    _encoder->encode(_data, empty);
    _encoder->encode(_data, filled);

    QTest::newRow("Empty encoded container") << empty;
    QTest::newRow("Filled encoded container") << filled;
}

void LsbTestCase::decodingTestCase()
{
    auto actual = _encoder->decode(_container);
    qDebug() << actual;

    QCOMPARE(actual, _data);
}

void LsbTestCase::cleanupTestCase()
{
    delete _encoder;
}

QTEST_APPLESS_MAIN(LsbTestCase)

#include "tst_lsbtestcase.moc"
