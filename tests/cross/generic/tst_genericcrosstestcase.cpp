#include <QtTest>

#include "stego/cross.hpp"
#include "stego/meta.hpp"

template<class T, size_t Size>
using Row = std::array<T, Size>;

template<class T, size_t Size>
using Matrix = std::array<Row<T, Size>, Size>;

constexpr static int Size = 6;

using R = Row<int, Size>;
using M = Matrix<int, Size>;

Q_DECLARE_METATYPE(M)

using Seq = std::integer_sequence<int, 3, 3>;
Q_DECLARE_METATYPE(Seq)

class GenericCrossIteratorTestCase : public QObject
{
    Q_OBJECT

public:
    GenericCrossIteratorTestCase() = default;
    ~GenericCrossIteratorTestCase() = default;

private:

private slots:
    void initTestCase();
    void initTestCase_data();

    void init();

    void accumulateTestCase_data();
    void accumulateTestCase();

    void cleanupTestCase();
};

void GenericCrossIteratorTestCase::initTestCase_data()
{
    QTest::addColumn<M>("container");

    R r = create_array<R::value_type, Size>();
    M m = { r, r, r, r, r, r };

    QTest::newRow("Range matrix") << m;
}

void GenericCrossIteratorTestCase::initTestCase() { }

void GenericCrossIteratorTestCase::init() { }

void GenericCrossIteratorTestCase::accumulateTestCase_data()
{
    QTest::addColumn<Seq>("position");
    QTest::addColumn<int>("expected");

    QTest::newRow("Center") << Seq() << 30;
}

void GenericCrossIteratorTestCase::accumulateTestCase()
{
    QFETCH_GLOBAL(M, container);
    QFETCH(Seq, position);
    QFETCH(int, expected);

    auto actual = std::accumulate(
            CrossIterator<2, M::const_iterator, 3, 3>(container.cbegin(), position),
            CrossIterator<2, M::const_iterator, 3, 3> (container.cend()), 0);
    QCOMPARE(actual, expected);
}

void GenericCrossIteratorTestCase::cleanupTestCase() { }

QTEST_APPLESS_MAIN(GenericCrossIteratorTestCase)

#include "tst_genericcrosstestcase.moc"
