#include <QtTest>

// add necessary includes here

class StringTest : public QObject
{
    Q_OBJECT

public:
    StringTest();
    ~StringTest();

private slots:
    void test_case1();
    void test_case1_data();

};

StringTest::StringTest()
{

}

StringTest::~StringTest()
{

}

//void StringTest::test_case1()
//{
//    QString str = "text1";
//    QVERIFY2(true, "Failure");
//    QCOMPARE(str.toUpper(), QString("TEXT"));
//}


void StringTest::test_case1()
{
    QFETCH(QString, string);
    QFETCH(QString, result);
    QCOMPARE(string.toUpper(),result);
    QVERIFY2(true, "Failure");
}

void StringTest::test_case1_data(){
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");
    QTest::newRow("lower")<<QString("kde")<<QString("KDE");
    QTest::newRow("mixed")<<QString("KdE")<<QString("KDE");
}

QTEST_APPLESS_MAIN(StringTest)

#include "tst_stringtest.moc"
