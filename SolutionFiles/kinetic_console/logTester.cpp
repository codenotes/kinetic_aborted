#include "stdafx.h"

// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <string>
#include <log4cxx/helpers/pool.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/simplelayout.h>
#include "log4cxx/consoleappender.h"
#include <log4cxx\xml\domconfigurator.h>
#include <log4cxx/appenderskeleton.h>
#include <vector>
#include <log4cxx/spi/loggingevent.h>
#include <log4cxx/nt/outputdebugstringappender.h>
#include <log4cxx/helpers/transcoder.h>
#include "sampleAppender.h"
#include <iostream>
#include <map>
#include "tuplelog.h"

//https://stackoverflow.com/questions/13967382/how-to-set-log4cxx-properties-without-property-file
//aybe ok, https://dreamcubes.wordpress.com/2008/06/10/log4cxx-tutorial-in-visual-c/

using namespace std;

log4cxx::LoggerPtr logger;
//not working
void test1()
{
	log4cxx::FileAppender * fileAppender = new log4cxx::FileAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()), L"c:\\temp\\logfileboob", false);

	log4cxx::ConsoleAppender * consoleAppender = new log4cxx::ConsoleAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()));

	log4cxx::helpers::Pool p;
	fileAppender->activateOptions(p);
	//fileAppender->setImmediateFlush(true);

	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(fileAppender));
	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(consoleAppender));
	log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getDebug());
	log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("logger");
	logger->addAppender(fileAppender);
	LOG4CXX_INFO(logger, "Created FileAppender appender");
}
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


//LoggerPtr loggerMyFunctionA(Logger::getLogger(_T("MyFunctionA")));
//not working
void test2() 
{
	log4cxx::FileAppender * fileAppender = new log4cxx::FileAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()),
		L"booblogfilefuck.log", true);
	log4cxx::ConsoleAppender * consoleAppender = new log4cxx::ConsoleAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()));

	log4cxx::nt::OutputDebugStringAppender * outputDebugStringAppender =
		new log4cxx::nt::OutputDebugStringAppender();




	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(consoleAppender));
	log4cxx::helpers::Pool p;

	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(fileAppender));
	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(outputDebugStringAppender));
	fileAppender->activateOptions(p);

	log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getDebug());
	log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("logger");

	//	fileAppender->setBufferedIO(true);
	fileAppender->setImmediateFlush(true);
	//fileAppender->setFile(L"c:\\temp\\fuck.log",true,false,1,p);
	LOG4CXX_DEBUG(logger, "Created FileAppender appender");

}

void test3() //working
{
	log4cxx::FileAppender * fileAppender = new
		log4cxx::FileAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()),
			L"logfile2", false);

	log4cxx::helpers::Pool p;
	fileAppender->activateOptions(p);
	log4cxx::ConsoleAppender * consoleAppender = new log4cxx::ConsoleAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()));

	log4cxx::nt::OutputDebugStringAppender * oda =
		new log4cxx::nt::OutputDebugStringAppender();

	log4cxx::VectorAppender* v = new log4cxx::VectorAppender();
	
	
	log4cxx::LoggerPtr roslogger = log4cxx::Logger::getLogger("ros");
	log4cxx::LoggerPtr greglogger = log4cxx::Logger::getLogger("ros.greg");
		
	auto rootlogger = log4cxx::Logger::getRootLogger();
	rootlogger->setLevel(log4cxx::Level::getError());
//	rootlogger->setAdditivity(false);

	roslogger->setLevel(log4cxx::Level::getError());
	roslogger->setAdditivity(false); //turns off the double log that happens
	
	//log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(fileAppender)); //same as addAppender
	roslogger->addAppender(log4cxx::AppenderPtr(fileAppender)); //we can add appdenders directly to specific loggers!  If we use "configure" it goes to the root.  And that conflicts with the setadditivity(). 

	log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(consoleAppender));


	//do this, and it access violates
	//log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(oda));
	
	//below works
	//log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(v));
	
	//root logs
	LOG4CXX_DEBUG(rootlogger, L"testDEBUG");
	LOG4CXX_ERROR(rootlogger, L"testERROR");



	LOG4CXX_DEBUG(roslogger, L"testDEBUG, I should see this on the roslogger, because it was set to error");
	LOG4CXX_ERROR(roslogger, L"testERROR, I should see this on the roslogger, because it was set to error");

	//LOG4CXX_INFO(greglogger, L"testINFO, shouldn't see this because ros is set to ERROR, and INFO is less priority");


	//logger->addAppender(outputDebugStringAppender);

	/*LOG4CXX_INFO(roslogger, L"Created FileAppender appender");
	LOG4CXX_DEBUG(roslogger, L"!" << _T("this is a debug  message.") << 66);
	LOG4CXX_INFO(roslogger, _T("this is a info message, just ignore."));
	LOG4CXX_WARN(roslogger, _T("this is a warn message, dont worry too much."));
*/
	//std::cout << v->vector.size()<<std::endl;




}


void doit()
{
	TupleLog::loganything(1, 2, "three", 3.14f, 1, "can it really do any num?", true);
	printf("\n");
}


//static delclaration, need to move this into a macro but good here for now
//map<string, string>  TupleLog::fformatters =
//{
//	{ "int","%d" },
//	{ "bool","%d" },
//	{ "char const * __ptr64","'%s'" },
//	{ "char const *","'%s'" },
//	{ "char *","'%s'" },
//	{ "float","%f" },
//	{ "float *","%d" },
//	{ "float * __ptr64","%d" },
//	{ "double","%f" },
//	{ "long","%d" },
//	{ "long * __ptr64","%d" },
//	{ "long *","%d" }
//};

//template <class T>
//void whatis(const T &x)
//{
//
//	if (std::is_same<int, T>::value)
//	{
//		cout << "is an int" << endl;
//	}
//	else if (std::is_same<int, T>::value)
//	{
//		cout << " is a char" << endl;
//	}
//
//}

GREG_TUPLELOG_DECLARE_FORMATTERS



#ifdef TEST_LOGGER
int main()
{
	//test3(); //working
	int x = 1;
	char c = 's';
	auto t = std::make_tuple(x, c);
	TupleLog::initFormatters();

	TupleLog::loganything(x, c);
	
	
	return 0;

	DOMConfigurator::configure("C:\\repos\\apache-log4cxx-0.10.0\\ConsoleApplication1\\Config.xml");

	LoggerPtr loggerToFile(Logger::getLogger(_T("another.file")));

	LOG4CXX_DEBUG(loggerToFile, _T("this is a debug message."));
	LOG4CXX_INFO(loggerToFile, _T("this is a info message, just ignore."));
	LOG4CXX_WARN(loggerToFile, _T("this is a warn message, dont worry too much."));

}

#endif