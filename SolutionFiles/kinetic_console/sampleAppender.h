#pragma once
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

namespace log4cxx
{


	/**
	An appender that appends logging events to a vector.
	*/
	class VectorAppender : public AppenderSkeleton
	{
	public:
		DECLARE_LOG4CXX_OBJECT(VectorAppender)
		BEGIN_LOG4CXX_CAST_MAP()
			LOG4CXX_CAST_ENTRY(VectorAppender)
			LOG4CXX_CAST_ENTRY_CHAIN(AppenderSkeleton)
		END_LOG4CXX_CAST_MAP()

		std::vector<spi::LoggingEventPtr> vector;


		/**
		This method is called by the AppenderSkeleton#doAppend
		method.
		*/
		void append(const spi::LoggingEventPtr& event, log4cxx::helpers::Pool& p);

		const std::vector<spi::LoggingEventPtr>& getVector() const
		{
			return vector;
		}

		void close();

		bool isClosed() const
		{
			return closed;
		}

		bool requiresLayout() const
		{
			return false;
		}
	};
	typedef helpers::ObjectPtrT<VectorAppender> VectorAppenderPtr;
}
