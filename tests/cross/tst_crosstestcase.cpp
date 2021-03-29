#include <QtTest>

#include "stego/cross.hpp"

class CrossIteratorTestCase : public QObject
{
    Q_OBJECT
    template<class T>
    using Matrix = QVector<QVector<T>>;

public:
    CrossIteratorTestCase() = default;
    ~CrossIteratorTestCase() = default;

private:

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void accumulateTestCase_data();
    void accumulateTestCase();

    void cleanupTestCase();
};

void CrossIteratorTestCase::initTestCase_data()
{
    QTest::addColumn<Matrix<int>>("container");

    int s = 6;
    QVector<int> range(s);
    std::iota(range.begin(), range.end(), 0);
    Matrix<int> rangeMatrix(s);
    std::fill(rangeMatrix.begin(), rangeMatrix.end(), range);

    QTest::newRow("Range matrix") << rangeMatrix;
}

void CrossIteratorTestCase::initTestCase() { }

void CrossIteratorTestCase::init() { }

void CrossIteratorTestCase::accumulateTestCase_data() {
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("crossSize");
    QTest::addColumn<int>("expected");

    QTest::newRow("Center") << 3 << 3 << 2 << 27;
    QTest::newRow("Left top") << 1 << 1 << 1 << 5;
    QTest::newRow("Right bottom") << 4 << 4 << 1 << 20;
    QTest::newRow("Custom position") << 2 << 2 << 2 << 18;
}

void CrossIteratorTestCase::accumulateTestCase()
{
    QFETCH_GLOBAL(Matrix<int>, container);
    QFETCH(int, expected);
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, crossSize);

    foreach(auto row, container)
    {
        qDebug() << row;
    }

    auto actual = std::accumulate(
            ConstCrossIterator(container.cbegin(), crossSize, x, y),
            ConstCrossIterator(container.cend()), 0);
    QCOMPARE(actual, expected);
}

void CrossIteratorTestCase::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(CrossIteratorTestCase)

#include "tst_crosstestcase.moc"
