#pragma once

#include <mutex>
#include <condition_variable>
//#include "tf/transform_broadcaster.h" //I don't like that this is here, but it didn't work in stdafx.h, only seems to work here so...

#include "stdint.h"
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
//#pragma once
//#include "targetver.h"

#if PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

//#include "winsock2.h"
#endif
// Windows Header Files:

//#include <windows.h>

#include <string>
#include <iostream>
#include <sstream>
//#if 0
//#include <ros/ros.h>// this file can cause winsock2 errors from boost...maybe I am including multiple times?
#include <std_msgs/string.h>
#include <geometry_msgs/point.h>
#include <ros/serialized_message.h>
#include <topic_tools/shape_shifter.h>
#include <boost/thread.hpp> 
#include <boost/circular_buffer.hpp>
#include <boost/unordered_map.hpp> 
#include <boost/foreach.hpp>
#include <iostream>
#include <fstream>
#include <ros/console.h>
//#include <log4cxx/logger.h>
//#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/functional/hash.hpp>
#include <signal.h>
//#include "ROSProc.h"

//#include <OaIdl.h> //for SAFEARRAY

//for TF
#include "tf2_msgs/TFMessage.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf/transform_broadcaster.h"

#include "dynamic_reconfigure/Config.h"


#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>


//#include <rosbag/bag.h>
//#include <rosbag/view.h>
#include "geometry_msgs/Pose.h"

//#include "winsock2.h"
// TODO: reference additional headers your program requires here



// TODO: reference additional headers your program requires here


class InitHelper;

typedef boost::shared_array<uint8_t> _ROSBinMessage;
typedef boost::circular_buffer<_ROSBinMessage> _ROSCircularBuffer;
typedef boost::shared_ptr < _ROSCircularBuffer> _ROSCircQueue_shared;



#define FILENOPATH (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

//issue with these, not sure what
#if PLATFORM_ANDROID
#define WHEREAMI
#else
#define WHEREAMI ROS_DEBUG_NAMED("interop","FUNC:%s, \tLINE:%d, \tFILE:%s \tTHREADID:%s", __FUNCTION__, __LINE__, FILENOPATH, boost::lexical_cast<std::string>(boost::this_thread::get_id()) );
#endif
#define RDB(X,...) ROS_DEBUG_NAMED("interop",X, ##__VA_ARGS__) //can not have an empty value for X or you get error
//#define RDB(...) ROS_DEBUG_NAMED("interop", __VA_ARGS__) ;//can not have an empty value for X or you get error
//#define WHEREANI
//#define RDB


//void silltest()
//{
//	//RDB("\tnot implemented",0);
//	WHEREAMI
//	RDB("something%d", 2);
//		
//	
//}

#define MAPHAS(I,S) !(I.find(S) == I.end())
#define SLEEP(T) boost::this_thread::sleep(boost::posix_time::milliseconds(T));

class ROSProc
{
public:
	enum threadAction { SHUTDOWN, CHANGE_MODE, POLL, CHANGE_POLL_RATE };
private:
	struct threadHelper
	{


		struct threadCommand
		{
			enum threadAction cmd;

			int iArg;
			void * args;
			threadCommand(enum threadAction ta) : cmd(ta) {};
			threadCommand() {};


		};

		boost::shared_ptr<boost::thread > mThread;
		boost::mutex m;
		boost::condition_variable cv;
		bool bROSInitialized = false;
		ros::Publisher m_pub;
		ros::Subscriber * m_sub;
		ros::TransportHints hint;


		static tf::TransformBroadcaster m_broadcaster;



		int loop_rate;

		threadHelper(boost::shared_ptr<boost::thread > th) :mThread(th)
		{
			WHEREAMI
				plk = boost::unique_lock<boost::mutex>(m);
			loop_rate = 1;
		};
		boost::lockfree::spsc_queue<threadHelper::threadCommand, boost::lockfree::capacity<10>> cmdQueue;

		boost::unique_lock<boost::mutex> plk;





	};


public:
	ros::NodeHandle *m_node = NULL;
	bool m_advertised = false;
	std::string m_input_topic;
	std::string m_output_topic;
	bool m_lazy;
	ros::TransportHints m_th;
	ros::NodeHandle * mp_NodeHandle = 0;
	boost::unordered_map<std::string, _ROSCircQueue_shared > mOutBuffers;
	boost::unordered_map<std::string, _ROSCircQueue_shared > mInBuffers;
	boost::unordered_map<std::string, boost::shared_ptr < threadHelper> > mPubThreads;
	boost::unordered_map<std::string, boost::shared_ptr < threadHelper> > mSubThreads;

	boost::unordered_map<std::string, _ROSBinMessage > mPropertyBag;

	//boost::shared_ptr < tf::Transform> mTFOut;


	boost::mutex mSubQueueMutex;
	boost::mutex mPubQueueMutex;

	//lock all queues
	boost::mutex mGlobalPubSubMutex;

	ROSProc(int argc, const char **arv, const char * nodeName)
	{
		WHEREAMI

			//RDB("\tnot implemented");
	}


	ROSProc()
	{
	}

	~ROSProc()
	{
	}

	void addThread(const char * topic, boost::shared_ptr<boost::thread > th);
	void ros_shutdown();
	bool ros_init(int argc, const char ** arv, const char * nodeName);
	void conn_cb(const ros::SingleSubscriberPublisher&);
	void ros_pub(std::string topic, std::string  MD5, std::string dataType, std::string definition, int loopRate, bool latching);
	void ros_sub(std::string topic, std::string  MD5, std::string dataType, std::string definition, int loopRate, bool latching);

	int spinPublisher(const char * topic, const char * MD5, const char * dataType, const char* msgDefinition, int loopRate, int qsize, bool latching);
	int spinSubscriber(const char * topic, const char * MD5, const char * dataType, const char* msgDefinition, int loopRate, int qsize, bool latching);

	int pubMessage(const char * topic, uint8_t * msg, int size);
	void dumpTopic(const char * topic);
	void test();
	void commandThread(const char * topic, threadAction t);
	void commandThread2(short pubsub, const char * topic, threadAction t);
	bool changeLoopRate(const char * topic, int loop_rate);
	void ros_soft_shutdown();
	void storeProperty(const char * name, uint8_t * msg, int size);
	void getProperty(const char * name, uint8_t * msg, int * size);
	//void storeParam(const char * name, uint8_t * msg, int size);
	//void getParam(const char * name, uint8_t * msg, int * size);
	void notifyPublisherQueue(const char * topic, threadAction t);
	void notifySubscriberQueue(const char * topic, threadAction t);

private:
	bool popPubMsg(const char * topic, topic_tools::ShapeShifter & sh);
	bool createPubQueue(const char * topic, int qsize);
	bool createSubQueue(const char * topic, int qsize);
	void notifyPubThread(const char * topic, bool bWakeEveryone = false);
	void notifyThread(boost::unordered_map<std::string, boost::shared_ptr < threadHelper> >& map,
		const char * topic, bool bWakeEveryone = false);


	void processThreadCommand(boost::shared_ptr<ROSProc::threadHelper> th);
	void sub_cb(const ros::MessageEvent<topic_tools::ShapeShifter>& msg_event, std::string topic);
	void dumpMap(boost::unordered_map<std::string, _ROSCircQueue_shared > & m);
	void terminateThreads();


};

class InitHelper
{
public:

	int argc;
	std::vector<std::string> argv;
	std::string nodeName;

	InitHelper(int _argcblah, const char ** _argvblah, std::string _nodeName)
	{
		argc = _argcblah;

		for (int i = 0; i < argc; i++)
		{
			argv.push_back(_argvblah[i]);
		}


		nodeName = _nodeName;


	}



};


class argvHelper
{

	int sz = 0;
	int argc2 = 3;
	int maxSize = 0;
	int pos = 0;
	char **String = 0;// no need to be global variable
	int row, col;

public:


	argvHelper(std::vector<std::string> v)
	{
		row = v.size();

		String = new char *[row]; //argc

		for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
		{

			if (maxSize < it->size())
				maxSize = it->size();
		}

		col = maxSize;



		for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
		{
			sz = it->size();
			String[pos] = new char[maxSize + 1];
			strcpy(&String[pos][0], it->c_str());
			pos++;

		}

		//cout << String[0] << "\n" << String[2] << endl;
	}

	const char ** getArgv()
	{

		return (const char**)String;


	}

	~argvHelper()
	{

		// release dynamically allocated memory
		for (int i = 0; i < row; i++)
		{

			delete[] String[i];// each array of characters
		}

		delete[] String;// the array of pointers
	}


	void dump()
	{

		for (int i = 0; i < row; i++)
		{

			std::cout << String[i] << std::endl;


		}



	}
};

//#endif