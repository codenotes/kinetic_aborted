
#ifndef ROS_INDIGO_EXPORTS
#define ROS_INDIGO_EXPORTS
#endif

#include <memory>
#include <vector>
#include <string>


namespace ros
{
	class NodeHandle;
}


extern "C"
{

#include <string>
#include <stdint.h>

	ROS_INDIGO_EXPORTS bool softShutdown(int param);
	ROS_INDIGO_EXPORTS bool softStartup(int param);

	ROS_INDIGO_EXPORTS void ROSBagWrite(const char * filename, const char * topic,
		const char * MD5,
		const char * dataType,
		int latching,
		unsigned char  * msg, int size);


	//used for clients to publist a position without needing to have all of ROS.  
	ROS_INDIGO_EXPORTS void ROSPublishPos(const char * topic, float posX, float posY, float posZ,
		float quatX,
		float quatY,
		float quatZ,
		float quatW
		);


	//int bytesToInt(uint8_t * byte);
	//void intToBytes(uint32_t longInt, uint8_t * byteArray);
	//void dump(uint8_t * b, int size);
	//void ros_walltime(uint32_t& sec, uint32_t& nsec)
	//void getLaunchParams(std::string path, std::map<string, string> & params);
	//bool isInt(std::string someString)
	//bool isFloat(std::string someString);
	ROS_INDIGO_EXPORTS void getLoggers(uint8_t * b, long *size);
	ROS_INDIGO_EXPORTS int isPortOpen(const char* ip, int port);
	ROS_INDIGO_EXPORTS void getTimeStamp(int32_t *sec, int32_t *nsec);
	ROS_INDIGO_EXPORTS void logAlong(const char * logger, int level, const char * msg);
	ROS_INDIGO_EXPORTS void ROSBegin();
	ROS_INDIGO_EXPORTS bool db_getMessage(int & size);
	ROS_INDIGO_EXPORTS int getMessageQueueSize(const char * topic);
	ROS_INDIGO_EXPORTS bool getMessage(const char * topic, uint8_t * b, long *size);
	ROS_INDIGO_EXPORTS int send_(unsigned char * b, int size, const char * fname);
	ROS_INDIGO_EXPORTS bool testROS(const char * msg);
	ROS_INDIGO_EXPORTS bool spinPublisher(const char * topic, const char * MD5, const char * dataType, const char* msgDefinition, int loopRate, int qsize, bool latching = false);
	ROS_INDIGO_EXPORTS bool spinSubscriber(const char * topic, const char * MD5, const char * dataType, const char* msgDefinition, int loopRate, int qsize, bool latching = false);
	ROS_INDIGO_EXPORTS void setParamsFromLaunchFile(const char * path);
	ROS_INDIGO_EXPORTS void setMasterTimeout(int seconds);
	ROS_INDIGO_EXPORTS bool ROSInit(int argc, const char **arv, const char* nodeName);
	ROS_INDIGO_EXPORTS bool ROSInitSimple(const char* nodeName);
	ROS_INDIGO_EXPORTS void createLogger(const char * logname, int level);
	ROS_INDIGO_EXPORTS void setLoggerLevel(const char * logname, int level);
	ROS_INDIGO_EXPORTS bool ROSShutdown(bool softShutdown);
	ROS_INDIGO_EXPORTS void dummyCreate();
	ROS_INDIGO_EXPORTS void dummyTest();
	ROS_INDIGO_EXPORTS int UnityTest();
	ROS_INDIGO_EXPORTS int pubMessage(const char * topic, unsigned char  * b, int size);
	ROS_INDIGO_EXPORTS bool changeLoopRate(const char * topic, int loop_rate);
	ROS_INDIGO_EXPORTS  void notifyPublisherQueue(const char * topic, short taction);
	ROS_INDIGO_EXPORTS void notifySubscriberQueue(const char * topic, short taction);
	ROS_INDIGO_EXPORTS void commandThread(const char * topic, short cmd); //warning, this doesn't distinguish between pub or sub, so if you have sub and pub on a topic, this is bad news. ;
	ROS_INDIGO_EXPORTS void commandThread2(short pubsub, const char * topic, short cmd); //warning, this doesn't distinguish between pub or sub, so if you have sub and pub on a topic, this is bad news. ;
	//Use for Unity.  Unity can't handle the SAFEARRAY marshalling, so we need to do a couple steps per below. ;
	//http://limbioliong.wordpress.com/2011/08/14/returning-an-array-of-strings-from-c-to-c-part-1/;
	ROS_INDIGO_EXPORTS void getTopicsUnity(/*[out]*/ char*** ppStringBufferReceiver,/*[out]*/ int* piStringsCountReceiver, char*** ppStringBufferReceiver2,/*[out]*/ int* piStringsCountReceiver2);
	ROS_INDIGO_EXPORTS void storeProperty(const char * name, unsigned char  * b, int size);
	ROS_INDIGO_EXPORTS void getProperty(const char * name, unsigned char  * b, int *size);


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


	ROS_INDIGO_EXPORTS void getParam(ROSParam & rp);
	ROS_INDIGO_EXPORTS void setParam(ROSParam rp);
	ROS_INDIGO_EXPORTS void startTransformBroadcast();
	ROS_INDIGO_EXPORTS void stopTransformbroadcast();
	ROS_INDIGO_EXPORTS void sendTransform(unsigned char  * b, int size);
	//Literal copy of the time.cpp function so that we can get timing calls without having to initialize ros. ;
	//Or have daemon running. For simulation stuff, you want to be able to get this for Stamped messages, etc. ;
	ROS_INDIGO_EXPORTS void getROSWallTime(uint32_t * sec, uint32_t*  nsec);

	ROS_INDIGO_EXPORTS void ROSBagOpen(const char * filename, int appendMode);
	ROS_INDIGO_EXPORTS void ROSBagClose(const char * filename);
	ROS_INDIGO_EXPORTS void ROSBagRead(const char * filename, const char *topic, uint8_t * b, long *size);
	ROS_INDIGO_EXPORTS void showHideConsoleWindow(int showHide);
	ROS_INDIGO_EXPORTS void createConsoleWindow(int stayOnTop);
	ROS_INDIGO_EXPORTS void CloseConsoleWindow();
	//courtesy function for use of clients so that they don't have to include boost.
	ROS_INDIGO_EXPORTS void sleepThread(int msec);
	ROS_INDIGO_EXPORTS int getKeyPressed();
	ROS_INDIGO_EXPORTS void terminateKeyboardMonitor();
	ROS_INDIGO_EXPORTS void createKeyboardMonitor();

	//CORE library exports, from roscpp, not interop dll.

	//add and remove loggers dynamically, in rosconsole_print.cpp
	ROS_INDIGO_EXPORTS void addDynamicLogger(const char *name, int level);
	ROS_INDIGO_EXPORTS void removeLogger(const char*);

	//changes the output print function for console so it can be directed to an internal log, file, or whatever.  Used mostly by unreal
	ROS_INDIGO_EXPORTS void setPrintFunc(void * pFunc);
	
	ROS_INDIGO_EXPORTS void getPublishers(std::shared_ptr<std::vector<std::string>>  pubs);
	ROS_INDIGO_EXPORTS void getSubscribers(std::shared_ptr<std::vector<std::string>> subs);

	ROS_INDIGO_EXPORTS void getNodeHandle(ros::NodeHandle *&nh);

	ROS_INDIGO_EXPORTS bool pgmb_to_pgma(char *file_in_name, char *file_out_name);


	//test if rosmaster is running or really if any port in a location is.
	void getIPandPort(const char * instr, std::string &ip, std::string  & port);
	bool is_port_open(const char *ip, const char *  port, int timeout );


	//this is exported from rosconsole_print.cpp
	void saveLoggers();

}