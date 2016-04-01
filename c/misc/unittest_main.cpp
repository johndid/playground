#include <fstream>
#include <unittest++/UnitTest++.h>
#include <unittest++/TestRunner.h>
#include <test_reporter_junit.h>

using namespace std;
using namespace UnitTest;

int main()
{
    ofstream f("test-report.xml");
    Test_reporter_junit reporter(f);
    TestRunner runner(reporter);
    return runner.RunTestsIf(Test::GetTestList(),NULL,True(),0);
}
