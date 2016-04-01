
#ifndef UNITTEST_TEST_REPORTER_JUNIT_H
#define UNITTEST_TEST_REPORTER_JUNIT_H

#include <unittest++/DeferredTestReporter.h>

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

namespace UnitTest
{
    class Test_reporter_junit : public DeferredTestReporter
    {
    public:
	explicit Test_reporter_junit(std::ostream& ostream);

	virtual void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);

    private:
	Test_reporter_junit(Test_reporter_junit const&);
	Test_reporter_junit& operator=(Test_reporter_junit const&);

	void AddXmlElement(std::ostream& os, char const* encoding);
	void BeginResults(std::ostream& os, int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);
	void EndResults(std::ostream& os);
	void BeginTest(std::ostream& os, DeferredTestResult const& result);
	void AddFailure(std::ostream& os, DeferredTestResult const& result);
	void EndTest(std::ostream& os, DeferredTestResult const& result);
	void AddSuite(std::ostream& os);
	void EndSuite(std::ostream& os);

	virtual void ReportTestStart(UnitTest::TestDetails const& test);
	virtual void ReportTestFinish(UnitTest::TestDetails const& test, float secondsElapsed);
	virtual void ReportFailure(UnitTest::TestDetails const& test, char const* failure);

	std::ostream& m_ostream;

	typedef std::multimap< std::string, DeferredTestResult > SuiteResultsList;
    
	SuiteResultsList m_suite_results;
	SuiteResultsList::iterator m_deferred_result;
    };

}

#endif //UNITTEST_TEST_REPORTER_JUNIT_H
