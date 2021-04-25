#include <QtTest>

#include "stego/skip.hpp"

using namespace Stg;

class ConstSkipIteratorTestCase : public QObject
{
    Q_OBJECT

public:
    ConstSkipIteratorTestCase() = default;
    ~ConstSkipIteratorTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void skipTestCase_data();
    void skipTestCase();

    void cleanupTestCase();
};

void ConstSkipIteratorTestCase::initTestCase_data() { }

void ConstSkipIteratorTestCase::initTestCase() { }

void ConstSkipIteratorTestCase::init() { }

void ConstSkipIteratorTestCase::skipTestCase_data() {
    QTest::addColumn<int>("skip");
    QTest::addColumn<int>("sum");
    QTest::addColumn<QList<int>>("container");

    auto l = QList<int>{1, 2, 3, 4, 5, 6};
    QTest::newRow("Small list range skip 3") << 4 << 6 << l;
    QTest::newRow("Small list range skip 2") << 2 << 9 << l;
    QTest::newRow("Small list range skip 1") << 1 << 21 << l;
}

void ConstSkipIteratorTestCase::skipTestCase()
{
    QFETCH(QList<int>, container);
    QFETCH(int, sum);
    QFETCH(int, skip);

    using T = QList<int>::ConstIterator;

    auto actual = std::accumulate(
            ConstSkipIterator(skip, container.cbegin()),
            ConstSkipIterator(container.cend()), 0);
    QCOMPARE(actual, sum);
}

void ConstSkipIteratorTestCase::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(ConstSkipIteratorTestCase)

#include "tst_skiptestcase.moc"
