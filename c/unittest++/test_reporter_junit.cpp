#include <test_reporter_junit.h>
#include <unittest++/TestDetails.h>
#include <unittest++/DeferredTestResult.h>

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

using std::string;
using std::ostringstream;
using std::ostream;

static const char* suite_root = "Linux";

namespace {

    void ReplaceChar(string& str, char c, string const& replacement)
    {
	for (size_t pos = str.find(c); pos != string::npos; pos = str.find(c, pos + 1))
	{
	    str.replace(pos, 1, replacement);
	}
    }

    string XmlEscape(string const& value)
    {
	string escaped = value;

	ReplaceChar(escaped, '&', "&amp;");
	ReplaceChar(escaped, '<', "&lt;");
	ReplaceChar(escaped, '>', "&gt;");
	ReplaceChar(escaped, '\'', "&apos;");
	ReplaceChar(escaped, '\"', "&quot;");
 
	return escaped;
    }

    string BuildFailureMessage(string const& file, int line, string const& message)
    {
	ostringstream failureMessage;
	failureMessage << file << "(" << line << ") : " << message;
	return failureMessage.str();
    }

}

namespace UnitTest {

    Test_reporter_junit::Test_reporter_junit(std::ostream& ostream) : m_ostream(ostream)
    {
    }

    void Test_reporter_junit::ReportSummary(int totalTestCount, int failedTestCount,int failureCount, float secondsElapsed)
    {
	AddXmlElement(m_ostream, NULL);
	BeginResults(m_ostream, totalTestCount, failedTestCount, failureCount, secondsElapsed);

	SuiteResultsList::iterator m_it, s_it;

	for (m_it = m_suite_results.begin();  m_it != m_suite_results.end();  m_it = s_it)
	{
	    string suite_name = (*m_it).first;

	    AddSuite(m_ostream);

	    // Iterate over all map elements with key == suite_name
	    std::pair<SuiteResultsList::iterator, SuiteResultsList::iterator> keyRange = m_suite_results.equal_range(suite_name);
	    for (s_it = keyRange.first;  s_it != keyRange.second;  ++s_it)
	    {
		// Add testcase
		DeferredTestResult const& result = (*s_it).second;
		BeginTest(m_ostream,result);
		if (result.failed)
		{
		    AddFailure(m_ostream, result);
		}
		EndTest(m_ostream, result);
          
	    }
	    EndSuite(m_ostream);
	}
	EndResults(m_ostream);

    
	std::cout << std::flush << std::endl;
	if (failedTestCount == 0)
	{
	    std::cout << "Done. All tests completed successfully." << std::endl;
	} 
	else 
	{
	    std::cout << "Done. Tests completed with " << failedTestCount << " failures." << std::endl;
	}
	std::cout << std::endl;
    }

    void Test_reporter_junit::AddSuite(std::ostream& os)
    {
	os << "<testsuite>";
    }
    
    void Test_reporter_junit::EndSuite(std::ostream& os)
    {
	os << "</testsuite>";
    }

    void Test_reporter_junit::AddXmlElement(ostream& os, char const* encoding)
    {
	os << "<?xml version=\"1.0\"";

	if (encoding != NULL)
	{
	    os << " encoding=\"" << encoding << "\"";
	}

	os << "?>";
    }

    void Test_reporter_junit::BeginResults(std::ostream& os, int totalTestCount, int failedTestCount, 
					   int failureCount, float secondsElapsed)
    {
	os << "<testsuites>";
    }

    void Test_reporter_junit::EndResults(std::ostream& os)
    {
	os << "</testsuites>";
    }

    void Test_reporter_junit::BeginTest(std::ostream& os, DeferredTestResult const& result)
    {
	os << "<testcase"
	   << " classname=\"" << suite_root << "." << result.suiteName << "\"" 
	   << " name=\"" << result.testName << "\""
	   << " time=\"" << result.timeElapsed << "\"";
    }

    void Test_reporter_junit::EndTest(std::ostream& os, DeferredTestResult const& result)
    {
	if (result.failed)
	{
	    os << "</testcase>";
	}
	else
	{
	    os << "/>";
	}
    }

    void Test_reporter_junit::AddFailure(std::ostream& os, DeferredTestResult const& result)
    {
	os << ">"; // close <test> element

	for (DeferredTestResult::FailureVec::const_iterator it = result.failures.begin(); it != result.failures.end(); ++it)
	{
	    string const escapedMessage = XmlEscape(std::string(it->second));
	    string const message = BuildFailureMessage(result.failureFile, it->first, escapedMessage);
	    os << "<failure" << " message=\"" << message << "\"" << "/>";
	}
    }

    void Test_reporter_junit::ReportTestStart(UnitTest::TestDetails const& test)
    {
	static int number = 1;
	char const* const format = "%d) %s::%s\n";
	printf(format,number,test.suiteName, test.testName);
	number++;

	m_deferred_result = m_suite_results.insert(std::make_pair<std::string,DeferredTestResult>(test.suiteName,DeferredTestResult(test.suiteName, test.testName)));

    }

    void Test_reporter_junit::ReportTestFinish(UnitTest::TestDetails const& details, float secondsElapsed)
    {
	DeferredTestResult& r = m_deferred_result->second;
	r.timeElapsed = secondsElapsed;
    }

    void Test_reporter_junit::ReportFailure(UnitTest::TestDetails const& details, char const* failure)
    {
	char const* const errorFormat = "%s:%d: error: Failure in %s: %s\n";

	using namespace std;
	printf(errorFormat, details.filename, details.lineNumber, details.testName, failure);

	DeferredTestResult& r = m_deferred_result->second;
	r.failed = true;
	r.failures.push_back(DeferredTestResult::Failure(details.lineNumber, failure));
	r.failureFile = details.filename;
    }
}

