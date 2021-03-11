#include <QtTest>

class TestCase : public QObject
{
    Q_OBJECT
    QString _current_path = QDir::currentPath();

public:
    TestCase() = default;
    ~TestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();
    void init();
    void cleanupTestCase();
};

void TestCase::initTestCase() {
}

void TestCase::initTestCase_data() {
    QTest::addColumn<QString>("path");
    QTest::newRow("regular") << _current_path;
}

void TestCase::init() {
    QFETCH_GLOBAL(QString, path);
}

void TestCase::cleanupTestCase() {
}

QTEST_APPLESS_MAIN(TestCase)

#include "tst_testcase.moc"
