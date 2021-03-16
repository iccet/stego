#include <QtTest>

#include "../../src/abstractencoder.hpp"
#include "../../src/lsb.hpp"

class LsbTestCase : public QObject
{
    Q_OBJECT

    QString _current_path = QDir::currentPath();
    Lsb *encoder;

public:
    LsbTestCase() = default;
    ~LsbTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();
    void init();
    void encodingTestCase();
    void cleanupTestCase();
};

void LsbTestCase::initTestCase() {
    encoder = new Lsb(this);
}

void LsbTestCase::initTestCase_data() {
    QTest::addColumn<QString>("data");
    QTest::addColumn<QByteArray>("container");
    QTest::newRow("Small string") << "test" << QByteArray(100, 0);
    QTest::newRow("Pixel") << "p" << QByteArray(100, 0xf0);
}

void LsbTestCase::init() {
    QFETCH_GLOBAL(QString, data);
    QFETCH_GLOBAL(QByteArray, container);

    qDebug() << "Data :" << data;
    qDebug() << "Container:" << container;
}

void LsbTestCase::encodingTestCase()
{
    QFETCH_GLOBAL(QString, data);
    QFETCH_GLOBAL(QByteArray, container);

    encoder->encode(data, container);
    qDebug() << container;
}

void LsbTestCase::cleanupTestCase()
{
//    delete encoder;
}

QTEST_APPLESS_MAIN(LsbTestCase)

#include "tst_lsbtestcase.moc"
