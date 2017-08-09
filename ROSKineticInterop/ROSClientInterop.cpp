//#pragma push_macro("check") //all this throw away
//#undef check
//#include "rosproc.h" //throw this away after testing
//#pragma pop_macro("check") //end throw away


// ROSClientInterop.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
//#include "rosimu.h"
//#include "VictoryBPLibraryPrivatePCH.h"

#pragma push_macro("check")
#undef check


#include "rosproc.h"
#include <string>

//#undef ROS_INDIGO_EXPORTS //because we are not a DLL here, we are local plugin.


#if PLATFORM_ANDROID
#include <android/log.h>
#endif

//#include <conio.h> //for _getch() in courtesy function
#include<boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp> 


#pragma pop_macro("check")


#define SLEEP(T) boost::this_thread::sleep(boost::posix_time::milliseconds(T));

using namespace std;



#define _CRTDBG_MAP_ALLOC

#if defined(WIN32) || defined(PLATFORM_WINDOWS)
#define ROS_INDIGO_EXPORTS
//#define ROS_INDIGO_EXPORTS  __declspec(dllexport)
#pragma message("We are all static now, so not using dllexport")
#else
#define ROS_INDIGO_EXPORTS __attribute__((visibility("default")))
#endif



ROSProc * g_ROSProc = 0;

int bytesToInt(uint8_t * byte);
void intToBytes(uint32_t longInt, uint8_t * byteArray);
void dump(uint8_t * b, int size);
void ros_walltime(uint32_t& sec, uint32_t& nsec);
void getLaunchParams(std::string path, std::map<string, string> & params);
bool isInt(std::string someString);
bool isFloat(std::string someString);


//HWND gConsoleHandle = 0;

//boost::unordered_map<std::string, boost::shared_ptr< rosbag::Bag>> * gpBags = 0; //initialized in RosInit



// CreateSafeArrayFromBSTRArray()
// This function will create a SafeArray of BSTRs using the BSTR elements found inside
// the first parameter "pBSTRArray".
//
// Note well that the output SafeArray will contain COPIES of the original BSTRs
// inside the input parameter "pBSTRArray".
//
//long CreateSafeArrayFromBSTRArray(BSTR* pBSTRArray, ULONG ulArraySize, SAFEARRAY** ppSafeArrayReceiver);
//converts regular std::string to wide string

std::wstring s2ws(const std::string& s);

_ROSCircQueue_shared cb_messages;

tf::TransformBroadcaster * gpTFBroadcaster = NULL;

int  gKeyPressed = 0; //temporary, this is for the keyboardMonitor courtesy function. 
boost::thread * gWorker = 0;


// Must provide storage for non-integral static const class members.
// Otherwise you get undefined symbol errors on OS X (why not on Linux?).
// Thanks to Rob for pointing out the right way to do this.
// In C++0x this must be initialized here #5401
//Seem to need this, do NOT know why.
//const double tf::Transformer::DEFAULT_CACHE_TIME = 10.0;




//namespace ros
//{
//	namespace console
//	{
//		namespace impl
//		{
//			void addLogger(const char * logger, int level);
//		}
//	}
//}
//;


template<typename M>
boost::shared_array<uint8_t>  SerializeROSMessage(const M& message)
{

	ros::SerializedMessage m = ros::serialization::serializeMessage<M>(message);
	uint8_t* ptr = m.buf.get();
	uint8_t temp[255];

	int size = m.num_bytes; //size of the TRUE message.  This will be 24 for point, for ex., changed this from message->size since a config doesnt have this attribute. Not sure it will work. 

	boost::shared_array<uint8_t> ar(new uint8_t[size + 4]); //putting size up front, now we have *28*, thats 24 after the first 4 which will be our size

	memcpy(ar.get(), ptr, size + 4);
	return ar;


}


extern "C"
{


	//	ROS_INDIGO_EXPORTS void getLoggers(uint8_t * b, long *size)
	//	{
	//		dynamic_reconfigure::Config config;
	//		dynamic_reconfigure::StrParameter s;
	//
	//
	//		std::map<std::string, ros::console::levels::Level> loggers;
	//		std::map<std::string, ros::console::levels::Level>::iterator it;
	//
	//		ros::console::get_loggers(loggers);
	//
	//		for (it = loggers.begin(); it != loggers.end(); it++)
	//		{
	//			s.name = it->first;
	//			s.value = std::to_string(it->second);
	//
	//			config.strs.push_back(s);
	//
	//			// iterator->first = key
	//			// iterator->second = value
	//			// Repeat if you also want to iterate through the second map.
	//		}
	//
	//
	//
	//
	//
	//
	//		_ROSBinMessage rb = SerializeROSMessage<dynamic_reconfigure::Config>(config);
	//		*size = bytesToInt(rb.get());
	//		memcpy(b, rb.get() + 4, *size);
	//
	//
	//
	//	}
	//


	void ROSMasterToPortAndIP(string &ip, string &port)
	{
		std::string s;
		s = getenv("ROS_MASTER_URI");

		typedef boost::tokenizer<boost::char_separator<char> >
			tokenizer;
		boost::char_separator<char> sep(":/");//, "/");//, boost::keep_empty_tokens);
		tokenizer tok(s, sep);

		auto it = std::next(tok.begin(), 1);
		ip = *std::next(tok.begin(), 1);
		port = *std::next(tok.begin(), 2);


	}




	ROS_INDIGO_EXPORTS int isROSRunning()
	{

		//		WHEREAMI
		//
		//			bool b = false;
		//
		//		string ip, port;
		//		ROSMasterToPortAndIP(ip, port);
		//
		//		b = isPortOpen(ip.c_str(), boost::lexical_cast<int>(port));
		//
		//		return (int)b;
		//
		return 0; //TODO: make this real

	}


	ROS_INDIGO_EXPORTS void getTimeStamp(int32_t *sec, int32_t *nsec)
	{

		ros::Time t = ros::Time::now();

		*sec = t.sec;
		*nsec = t.nsec;

	}

#ifdef USE_LOGALONG
	ROS_INDIGO_EXPORTS void logAlong(const char * logger, int level, const char * msg)
	{
		if (!g_ROSProc)
			return;

		//removed below because we don't want to change level automatically. Nor
		//do we want to create loggers implicitly.  Create Logger will do this. 
		//		ros::console::impl::addLogger(logger, level);//this will only add if it is not there already

		switch (level)
		{
		case 0: //debug
			ROS_DEBUG_NAMED(logger, msg);
			break;

		case 1: //info
			ROS_INFO_NAMED(logger, msg);
			break;

		case 2: //warn
			ROS_WARN_NAMED(logger, msg);
			break;

		case 3: //error
			ROS_ERROR_NAMED(logger, msg);
			break;

		case 4: //fatal
			ROS_FATAL_NAMED(logger, msg);
			break;

		default:
			ROS_INFO("A log message was put in logAlong that did not have a proper level:%s", msg);
			;
		}


	}
#endif

	ROS_INDIGO_EXPORTS void ROSBegin()
	{
		WHEREAMI

			g_ROSProc = new ROSProc(); // argc, arv, nodeName);
		RDB("\tInitializing core ROS.");


	}

	ROS_INDIGO_EXPORTS bool db_getMessage(int & size)
	{
		WHEREAMI
			size = 0;

		return false;



	}

	ROS_INDIGO_EXPORTS int getMessageQueueSize(const char * topic)
	{
		WHEREAMI

			if (!g_ROSProc)
			{

				RDB("\nROS Not initialized..");

				return 0;
			}

		boost::unordered_map<std::string, _ROSCircQueue_shared >::iterator it;

		it = g_ROSProc->mInBuffers.find(topic);

		if (it == g_ROSProc->mInBuffers.end())
		{
			RDB("\titerator found no topic. Throwing Exception.");
			//throw NULL;
			return 0;
		}
		else
		{

			return it->second->size();


		}


	}

	//ROS_INDIGO_EXPORTS bool getMessage(const char * topic, unsigned char * b, int *size)
	ROS_INDIGO_EXPORTS bool getMessage(const char * topic, uint8_t * b, long *size)
	{
		WHEREAMI


			//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&LINE:%d", __LINE__);			

			//	cout << fname << endl;
			//	cout << ":" << strcmp(fname, "") << ":" << endl;
			if (!g_ROSProc)
			{
				//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&LINE:%d", __LINE__);						

				RDB("\nROS Not initialized..");
				*size = 0;
				//	ForceEAX();
				return false;
			}

		boost::mutex::scoped_lock lock(g_ROSProc->mSubQueueMutex);


		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&LINE:%d", __LINE__);			

		try
		{
			//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&LINE:%d", __LINE__);			
			boost::unordered_map<std::string, _ROSCircQueue_shared >::iterator it;

			it = g_ROSProc->mInBuffers.find(topic);

			if (it == g_ROSProc->mInBuffers.end())
			{
				//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&NOTOPICSLINE:%d", __LINE__);			
				ROS_DEBUG_THROTTLE_NAMED(5, "interop_poll", "\titerator found no topic:%s. Throwing Exception.", topic);
				throw NULL;
			}
			else
			{
				//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&LINE:%d", __LINE__);			
				cb_messages = it->second; // g_ROSProc->mInBuffers[topic];
				RDB("\tJust searched for %s", topic);
				if (cb_messages == NULL) //overkill at this point, but inherited from before I put in the iterator search.
				{
					//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&LINE:%d", __LINE__);			
					throw NULL;
				}
			}

		}
		catch (...)
		{
			//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&EXCEPTION_LINE:%d", __LINE__);			
			ROS_DEBUG_THROTTLE_NAMED(5,
				"interop_poll",
				"\tWhoah!  Trying to pop a circ queue for a topic that is not registered with mInBuffers:%s at line:%d",
				topic,
				__LINE__);

			*size = 0;
			//		ForceEAX();
			return false;

		}


		if (cb_messages->size() > 0)
		{

			_ROSBinMessage rb = cb_messages->operator[](0);
			*size = bytesToInt(rb.get());

			//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&POPLINE:%d SIZE MSG:%d", __LINE__,*size);			
			RDB("\tpopped message of size:%ld and sending to host", *size);
			memcpy(b, rb.get() + 4, *size);

			cb_messages->pop_front();

			//	dump(b, *size);
			//	ForceEAX();
			return true;

		}
		else
		{
			//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "&&NOMESSAGELINE:%d", __LINE__);			
			RDB("\tgetMessage called but nothing in queue.");
			//ForceEAX();
			return false; //no messages.
		}




		//cout << "size buffer is:" << *size << endl;


		//if (strcmp(fname, ""))//we have a real filename
		//{
		//	//	cout << "reading file" << endl;
		//	std::ifstream f(fname, std::ios::binary);
		//	f.read((char*)b, *size);
		//	*size = f.gcount();


		//	//cout << "nothing here for filename" << endl;
		//	//	(b)[0] = 6;
		//	return 0;
		//}
		////do something else, this is live from ROS i guess. 

		//(b)[0] = 11;
		//(b)[1] = 12;
		//*size = 66;

		//	return *size;



	}

	ROS_INDIGO_EXPORTS int send_(unsigned char * b, int size, const char * fname)
	{

		std::ofstream f(fname, std::ios::binary);

		f.write((const char*)b, size);

		std::cout << "size is:" << size << std::endl;

		for (int i = 0; i < size; i++)
		{
			std::cout << (int)b[i] << ",";
		}

		return 0;

	}

	ROS_INDIGO_EXPORTS bool testROS(const char * msg)
	{


		ROS_INFO("interop:%s", msg);
		return true;

	}

	ROS_INDIGO_EXPORTS bool spinPublisher(const char * topic,
		const char * MD5,
		const char * dataType,
		const char* msgDefinition,
		int loopRate,
		int qsize,
		bool latching = false)


	{
		WHEREAMI

			if (!g_ROSProc)
			{
				ROS_DEBUG_NAMED("interop", "\tmain ROSProc not initialized, run ROSInit()");

				return false;
			}

		if (topic == NULL)
		{

			ROS_DEBUG_NAMED("interop", "\tnull topicname");

			return false;

		}

		//InitHelper inh(argc, argv, nodeName);


		try
		{
			g_ROSProc->spinPublisher(topic, MD5, dataType, msgDefinition, loopRate, qsize, latching);
		}
		catch (...)
		{


			RDB("\tCatastophic error.");

		}


		return true;

	}

	ROS_INDIGO_EXPORTS bool spinSubscriber(const char * topic,
		const char * MD5,
		const char * dataType,
		const char* msgDefinition,
		int loopRate,
		int qsize,
		bool latching = false)


	{
		WHEREAMI

			if (!g_ROSProc)
			{
				ROS_DEBUG_NAMED("interop", "\tmain ROSProc not initialized, run ROSInit()");

				return false;
			}

		if (topic == NULL)
		{
			//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "$LINE:%d", __LINE__);			

			ROS_DEBUG_NAMED("interop", "\tnull topicname");

			return false;

		}


		//InitHelper inh(argc, argv, nodeName);


		//g_ROSProc->spinPublisher(  inh, topic, MD5, dataType, msgDefinition, loopRate, latching);
		try
		{
			//			__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "$LINE:%d, topic is:%s", __LINE__, topic);			
			g_ROSProc->spinSubscriber(topic, MD5, dataType, msgDefinition, loopRate, qsize, latching);
		}
		catch (...)
		{
			//		__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "$OHNO LINE:%d", __LINE__);			
			ROS_DEBUG_NAMED("interop", "\tCatastrophic error");

		}


		return true;

	}

	typedef std::map<string, string> map_t;

	ROS_INDIGO_EXPORTS void setParamsFromLaunchFile(const char * path)
	{

		std::map<string, string> params;

		getLaunchParams(path, params);


		/*numbers with '.'s are floating point, integers otherwise;
		"true" and "false" are boolean(not case-sensitive).
		all other values are strings
		*/

		BOOST_FOREACH(map_t::value_type  &place, params)
		{
			//		printf("%s->%s\n", place.first.c_str(), place.second.c_str());

			if (isFloat(place.second))
			{
				//	ros::param::set()

			}
			else if (isInt(place.second))
			{

			}
			else if (place.second == "true" || place.second == "false")
			{

			}

			//n.setParam(place.first.c_str(), place.second.c_str());

		}




	}


	ROS_INDIGO_EXPORTS void setMasterTimeout(int seconds)
	{//will prevent hangups when initializating if core is not there. 
		ros::master::setRetryTimeout(ros::WallDuration(seconds, 0));


	}



	ROS_INDIGO_EXPORTS bool ROSInit(int argc, const char **arv, const char* nodeName)
	{
		WHEREAMI

			//greg:new
			//first check old school and see if roscore is out there and listening. 
			//using winsock because I don't trust the ROS apis. 

			ROS_INFO("In ROSInit()");


		//


		bool b = true;
		ros::Time::init(); //new: hope this doesn't mess anything up.

		if (!g_ROSProc)
		{

			g_ROSProc = new ROSProc(); // argc, arv, nodeName);
			RDB("\tInitializing core ROS.");

			//gpBags = new boost::unordered_map<std::string, boost::shared_ptr< rosbag::Bag>>;
			RDB("\tInitialized map of ROS bags.");



			for (int i = 0; i < argc; i++)
			{
				RDB("\tCommand Line arg %d is:%s", i, arv[i]);

			}

			b = g_ROSProc->ros_init(argc, arv, nodeName);

		}
		else
		{
			RDB("\tROS already initialized.");
		}



		//g_ROSProc = new ROSProc(); // argc, arv, nodeName);
		//ROS_INFO("Initializing core ROS.");


		return b;


	}

	ROS_INDIGO_EXPORTS bool softShutdown(int param)
	{

		g_ROSProc->ros_soft_shutdown(); //kills all threads and everything, but leaves nodes alive.
		ROS_INFO_NAMED("interop", "ros soft shutdown called...");

		if (g_ROSProc->mp_NodeHandle)
		{
			g_ROSProc->mp_NodeHandle->shutdown();
			delete g_ROSProc->mp_NodeHandle;
			g_ROSProc->mp_NodeHandle = 0;
			return 0;

		}

		return 0; //todo:make this real
	}

	ROS_INDIGO_EXPORTS bool softStartup(int param)
	{

		if (!g_ROSProc->mp_NodeHandle)
		{

			g_ROSProc->mp_NodeHandle = new ros::NodeHandle();

		}

		return true;
	}


	ROS_INDIGO_EXPORTS bool ROSInitSimple(const char* nodeName)
	{

#if defined(WIN32)	|| defined (PLATFORM_WINDOWS)
		char *argv[] = { "dummyexe" }; //, "arg1", "arg2", NULL
#elif PLATFORM_ANDROID
		char *argv[3];
		char temp[255];
		strcpy(temp, "jesuschrist");
		argv[0] = temp;

#endif

		int argc = sizeof(argv) / sizeof(char*);
		ROS_INFO("Calling ROSInit");
		return ROSInit(argc, (const char**)argv, nodeName);

	}



	//	ROS_INDIGO_EXPORTS void createLogger(const char * logname, int level)
	//	{
	//		ros::console::impl::addLogger(logname, level);//this will only add if it is not there already
	//													  //ros::console::notifyLoggerLevelsChanged();
	//	}

	ROS_INDIGO_EXPORTS void setLoggerLevel(const char * logname, int level)
	{


		if (ros::console::set_logger_level(logname, (ros::console::levels::Level)level))
		{

			RDB("\tLogger level changed successfully.");
			ros::console::notifyLoggerLevelsChanged();
		}
		else
			RDB("\tCould not set logging level for %s to %d", logname, level);




	}

	ROS_INDIGO_EXPORTS bool ROSShutdown(bool softShutdown)
	{
		WHEREAMI

			ROS_WARN_NAMED("interop", "\tOnce you shutdown ROS you can not restart it without rebooting process host.  This is a limitation in ROS.");


		if (gpTFBroadcaster)
		{

			RDB("About to delete gpBroadcasterTF");

			delete gpTFBroadcaster;

		}

		if (g_ROSProc)
		{
			if (!softShutdown)
				g_ROSProc->ros_shutdown();
			else
			{
				g_ROSProc->ros_soft_shutdown();
				return true;
			}


			RDB("\tAbout to delete g_ROSProc.");
			cout << "1" << endl;


			if (g_ROSProc)
			{
				delete g_ROSProc;

			}

			//if (gpBags)
			//	delete gpBags;

			cout << "2" << endl;
			g_ROSProc = NULL;
			return true;
		}
		else
			RDB("\tShutdown called prior to Init being called. Ignored.");
		RDB("\tYou should exit the process now. ROS may not be restarted.");

		return false;

	}

	ROS_INDIGO_EXPORTS void dummyCreate()
	{
		g_ROSProc = new ROSProc();

	}

	ROS_INDIGO_EXPORTS void dummyTest()
	{
		WHEREAMI



			//g_ROSProc->commandThread("booby",ROSProc::threadAction::SHUTDOWN);


			//	char * c[1][255];

			//	c[0][0] = "appname";
			//	
			//	int argc = 1;

			////	ros::init(argc,( char**)c,"test");
			//	ros::shutdown();

	}
	ROS_INDIGO_EXPORTS int UnityTest()
	{




		return 42;


	}

	ROS_INDIGO_EXPORTS int pubMessage(const char * topic, unsigned char  * b, int size)
	{
		if (!g_ROSProc)
		{
			RDB("ROS NOT INITIALIZED.");
			return 0;

		}


		g_ROSProc->pubMessage(topic, (uint8_t*)b, size);

		return size;

	}

	ROS_INDIGO_EXPORTS bool changeLoopRate(const char * topic, int loop_rate)
	{
		WHEREAMI
			if (!g_ROSProc)
			{
				RDB("\tROS NOT INITIALIZED.");
				return 0;

			}

		return g_ROSProc->changeLoopRate(topic, loop_rate);


	}


	ROS_INDIGO_EXPORTS  void notifyPublisherQueue(const char * topic, short taction)
	{
		WHEREAMI
			if (!g_ROSProc)
			{
				RDB("\tROS NOT INITIALIZED.");
				return;

			}

		g_ROSProc->notifyPublisherQueue(topic, (ROSProc::threadAction)taction);



	}
	ROS_INDIGO_EXPORTS void notifySubscriberQueue(const char * topic, short taction)
	{
		WHEREAMI
			if (!g_ROSProc)
			{
				RDB("\tROS NOT INITIALIZED.");
				return;

			}
		g_ROSProc->notifySubscriberQueue(topic, (ROSProc::threadAction)taction);

	}


	ROS_INDIGO_EXPORTS void commandThread(const char * topic, short cmd) //warning, this doesn't distinguish between pub or sub, so if you have sub and pub on a topic, this is bad news. 
	{
		WHEREAMI
			if (!g_ROSProc)
			{
				RDB("\tROS NOT INITIALIZED.");
				return;

			}
		g_ROSProc->commandThread(topic, (ROSProc::threadAction)cmd);

	}


	ROS_INDIGO_EXPORTS void commandThread2(short pubsub, const char * topic, short cmd) //warning, this doesn't distinguish between pub or sub, so if you have sub and pub on a topic, this is bad news. 
	{
		WHEREAMI
			if (!g_ROSProc)
			{
				RDB("\tROS NOT INITIALIZED.");
				return;

			}

		g_ROSProc->commandThread2(pubsub, topic, (ROSProc::threadAction)cmd);

	}






	ROS_INDIGO_EXPORTS void storeProperty(const char * name, unsigned char  * b, int size)
	{
		WHEREAMI
			if (g_ROSProc)
			{

				g_ROSProc->storeProperty(name, b, size);

			}


	}

	ROS_INDIGO_EXPORTS void getProperty(const char * name, unsigned char  * b, int *size)
	{
		WHEREAMI

			if (g_ROSProc)
			{

				g_ROSProc->getProperty(name, b, size);

			}


	}



	struct ROSParam
	{
		char *name;
		int fieldType;
		int boolType;
		int intType;
		char * stringType;
		char * retstringType;
		int paramExists;
		double dType;

	};



	ROS_INDIGO_EXPORTS void getParam(ROSParam & rp)
	{
		WHEREAMI

			std::string s1;
		//int size = s1.length() + 1;
		//rp.retstringType = (char*)::CoTaskMemAlloc(size);
		//memset(rp.retstringType, 0, size);
		//strcpy(rp.retstringType, s1.c_str());
		//return;
		bool b;

		if (!g_ROSProc)
			return;
		try
		{
			switch (rp.fieldType)
			{
			case 0: //bool
				if (!ros::param::get(rp.name, b))
				{
					throw NULL;
				}
				else
				{
					rp.boolType = b ? 1 : 0;
				}
				break;
			case 1: //int
				if (!ros::param::get(rp.name, rp.intType))
				{
					throw NULL;
				}
				break;
			case 3: //double
				if (!ros::param::get(rp.name, rp.dType))
				{
					throw NULL;
				}
				break;
			case 2: //string
				if (ros::param::get(rp.name, s1))
				{
					//rp.retstringType = (char*)::CoTaskMemAlloc(s1.length()+1);
					//					rp.retstringType = (char*)::GlobalAlloc(GMEM_FIXED, s1.length() + 1);
					//
					//					memset(rp.retstringType, 0, s1.length() + 1);
					//					strcpy(rp.retstringType, s1.c_str());
					break;
				}
				else
				{
					throw NULL;
				}

			}
		}
		catch (...)
		{
			//RDB("\tCould not find property.");

			rp.paramExists = 0;
		}

		rp.paramExists = 1;


	}

	ROS_INDIGO_EXPORTS void setParam(ROSParam rp)
	{
		WHEREAMI

			//		cout << rp.name << " " << rp.fieldType << " " << rp.boolType << " " << rp.intType << " " << rp.stringType << endl;
			//return;



			if (!g_ROSProc)
				return;

		try
		{
			switch (rp.fieldType)
			{
			case 0: //bool

				ros::param::set(rp.name, rp.boolType == 1 ? true : false);
				break;
			case 1: //int

				ros::param::set(rp.name, rp.intType);
				break;
			case 2: //string
				ros::param::set(rp.name, rp.stringType);
				break;
			case 3: //double
				ros::param::set(rp.name, rp.dType);
				break;

			}
		}
		catch (std::exception se)
		{
			RDB("\nException setting parameter:%s", se.what());

		}



	}


	ROS_INDIGO_EXPORTS void startTransformBroadcast()
	{
		if (!gpTFBroadcaster)
			gpTFBroadcaster = new tf::TransformBroadcaster();

	}


	ROS_INDIGO_EXPORTS void stopTransformbroadcast()
	{
		if (gpTFBroadcaster)
		{
			delete gpTFBroadcaster;
			gpTFBroadcaster = NULL;
		}


	}


	ROS_INDIGO_EXPORTS void sendTransform(unsigned char  * b, int size)
	{


		if (!gpTFBroadcaster)
		{
			ROS_INFO_NAMED("interop", "Broadcaster not created, creating it...");
			startTransformBroadcast();


		}

		//static tf::TransformBroadcaster br;
		geometry_msgs::TransformStamped t;

		ros::serialization::IStream stream(b + 4, size - 4); //works
		ros::serialization::deserialize(stream, t);
		gpTFBroadcaster->sendTransform(t);

		ROS_DEBUG_NAMED("interop",
			"Sent transform size:%d x:%4.2f y:%4.2f z:%4.2f : x:%4.2f y:%4.2f z:%4.2f w:%4.2f",
			size,
			t.transform.translation.x,
			t.transform.translation.y,
			t.transform.translation.z,
			t.transform.rotation.x,
			t.transform.rotation.y,
			t.transform.rotation.z,
			t.transform.rotation.w
		);

		//geometry_msgs::TransformStamped tf;

		//dont need shapeshifter.  Just should need ros deserialize

	}


	//Literal copy of the time.cpp function so that we can get timing calls without having to initialize ros. 
	//Or have daemon running. For simulation stuff, you want to be able to get this for Stamped messages, etc. 
	//	ROS_INDIGO_EXPORTS void getROSWallTime(uint32_t * sec, uint32_t*  nsec)
	//	{
	//		ros_walltime(*sec, *nsec);
	//
	//	}

	//DO NOT USE!  Causes blow ups when used from Unity.  
	ROS_INDIGO_EXPORTS void setENV(const char * env) //call this before init
	{
		//		WHEREAMI
		//
		//			if(g_ROSProc)
		//		{
		//
		//			ROS_INFO_NAMED("interop", "Can not call this method after ROS is initialized.");
		//			return;
		//		}
		//
		//		_putenv(env);

	}


	//ROSBAG Stuff











	//used for clients to publist a position without needing to have all of ROS.  
	ROS_INDIGO_EXPORTS void ROSPublishPos(const char * topic,
		float posX,
		float posY,
		float posZ,
		float quatX,
		float quatY,
		float quatZ,
		float quatW)
	{
		geometry_msgs::Pose p;
		p.position.x = posX;
		p.position.y = posY;
		p.position.z = posZ;

		p.orientation.x = quatX;
		p.orientation.y = quatY;
		p.orientation.z = quatZ;
		p.orientation.w = quatW;

		ros::SerializedMessage m = ros::serialization::serializeMessage<geometry_msgs::Pose>(p);
		pubMessage(topic, m.buf.get(), m.num_bytes); //I don't think size does anythin, but be carefull. 


	}










	//courtesy function for use of clients so that they don't have to include boost.
	ROS_INDIGO_EXPORTS void sleepThread(int msec)
	{
		SLEEP(msec);

	}



	ROS_INDIGO_EXPORTS int getKeyPressed()
	{
		return gKeyPressed;
	}




	//warning, only works with C++ Clients below

	ROS_INDIGO_EXPORTS void getPublishers(std::shared_ptr<std::vector<std::string>>  pubs)
	{

		if (!g_ROSProc)
		{
			return;
			ROS_DEBUG_NAMED("unreal", "rosproc not initialized");
		}



		ROS_DEBUG_NAMED("unreal", "count of items in pub:%d", g_ROSProc->mInBuffers.size());


		for (auto &i : g_ROSProc->mOutBuffers)
		{
			pubs->push_back(i.first);

		}

	}


	ROS_INDIGO_EXPORTS void getSubscribers(std::shared_ptr<std::vector<std::string>> subs)
	{
		if (!g_ROSProc)
			return;

		for (auto &i : g_ROSProc->mInBuffers)
		{
			subs->push_back(i.first);

		}

	}







}





//copied time functions from main library so that they could be used without initialization of ROS.  Handy in Unity.
void normalizeSecNSecUnsigned(int64_t& sec, int64_t& nsec)
{
	int64_t nsec_part = nsec % 1000000000L;
	int64_t sec_part = sec + nsec / 1000000000L;
	if (nsec_part < 0)
	{
		nsec_part += 1000000000L;
		--sec_part;
	}

	if (sec_part < 0 || sec_part > UINT_MAX)
		throw std::runtime_error("Time is out of dual 32-bit range");

	sec = sec_part;
	nsec = nsec_part;
}

