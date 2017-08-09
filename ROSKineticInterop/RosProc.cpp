

//#include "VictoryBPLibraryPrivatePCH.h"
//#include "rosimu.h"


#pragma push_macro("check")

#undef check


#include "rosproc.h"
#include <exception>

#if PLATFORM_ANDROID
#include <android/log.h>
#endif




#if 1
/*
below:so that the thread can lookup its topic name in the message callback
This is otherwise not accessible to the callback function who needs it.

*/
//static boost::thread_specific_ptr< char> gThreadTopic; 
//__declspec(thread) char gThreadTopic2[512] = { 0 }; //windows

#if PLATFORM_ANDROID
//__thread char gThreadTopic2[512] = { 0 }; //TODO: DOERSNT WORK FOR ANDROID
char gThreadTopic2[512] = { 0 }; //TODO: DOERSNT WORK FOR ANDROID
#elif defined(WIN32) || defined(PLATFORM_WINDOWS)
__declspec(thread) char gThreadTopic2[512] = { 0 };

#endif




void dump(uint8_t * b, int size)
{
	std::cout << "size is:" << size << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << (int)b[i] << ",";
	}

	std::cout << '\b' << std::endl;



}

int bytesToInt(uint8_t * byte) //big endian is used apparently
{

	//unsigned char* byte = reinterpret_cast<unsigned char*(b);
	return ((byte[3] << 24) | (byte[2] << 16) | (byte[1] << 8) | (byte[0]));

}

void intToBytes(uint32_t longInt, uint8_t * byteArray)
{



	// convert from an unsigned long int to a 4-byte array
	byteArray[3] = (int)((longInt >> 24) & 0xFF);
	byteArray[2] = (int)((longInt >> 16) & 0xFF);
	byteArray[1] = (int)((longInt >> 8) & 0XFF);
	byteArray[0] = (int)((longInt & 0XFF));

}


void mySigintHandler(int sig)
{
	// Do some custom action.
	// For example, publish a stop message to some other nodes.
	RDB("=======================================captured ctrl-c in DLL\n");

	// All the default sigint handler does is call shutdown()
	//   ros::shutdown();
}

//THIS IS CALLED By ROSInit()
//copy of original and with ROS_INFO everywhere for debugging on android.
bool ROSProc::ros_init(int argc, const char ** arv, const char * nodeName)
{
	WHEREAMI

		ROS_INFO("Calling ros::init and creating nodehandle, nodeName:%s", nodeName);
	signal(SIGINT, mySigintHandler);

	ROS_INFO("^ROS_MASTER_URI = %s", getenv("ROS_MASTER_URI"));
	ROS_INFO("ROS_CONFIG_FILE is = %s", getenv("ROSCONSOLE_CONFIG_FILE"));


	if (!getenv("ROS_MASTER_URI"))
	{

		ROS_INFO("setting local host as ROS_CONIF_FILE as temporary measure by default");
		ROS_INFO("removed putenv, failure possible.");
		ROS_INFO("NO MASTER_URI");

		//	putenv("ROS_MASTER_URI=http://127.0.0.1:11311");


	}

	//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===LINE:%d", __LINE__);

	ROS_INFO("about to call INIT...nodename:%s", nodeName);
	try
	{
		//	__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===LINE:%d", __LINE__);
		ros::init(argc, (char**)arv, nodeName, ros::init_options::NoSigintHandler);
	}
	catch (std::exception& e)
	{
		//e.what();
		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===EXCEPT:%s", e.what());
		ROS_INFO("exception:%s", e.what());
	}
	catch (...)
	{
		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===LINE:%d", __LINE__);
		ROS_INFO("Error calling ROSInit, unknown exception");
		return false;

	}


	if (!ros::master::check())
	{

		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===ROSCORE NOT RUNNING, But should I be checking? LINE:%d", __LINE__);		
		ROS_INFO("ROScore does not seem to be running..returning.");
		ROS_INFO("roscore not running.  Unfortunately will need to tear down and restart this process. But continuing anyway, maybe it will work.");
		//	return false;


	}


	ROS_INFO("about to create nodehandle");

	mp_NodeHandle = new ros::NodeHandle();
	return true;

}


/*
bool ROSProc::ros_init(int argc, const char ** arv, const char * nodeName)
{
WHEREAMI

ROS_DEBUG_NAMED("\tinterop", "Calling ros::init and creating nodehandle, nodeName:%s", nodeName);
signal(SIGINT, mySigintHandler);

ROS_DEBUG_NAMED("interop", "ROS_MASTER_URI = %s", getenv("ROS_MASTER_URI"));
ROS_DEBUG_NAMED("interop", "ROS_CONFIG_FILE is = %s", getenv("ROSCONSOLE_CONFIG_FILE"));


if (!getenv("ROS_MASTER_URI"))
{

ROS_DEBUG_NAMED("interop", "setting local host as ROS_CONIF_FILE as temporary measure by default");
ROS_DEBUG_NAMED("interop", "removed putenv, failure possible.");
ROS_FATAL_NAMED("interop", "NO MASTER_URI");

//	putenv("ROS_MASTER_URI=http://127.0.0.1:11311");


}

//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===LINE:%d", __LINE__);


try
{
//	__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===LINE:%d", __LINE__);
ros::init(argc, (char**)arv, nodeName, ros::init_options::NoSigintHandler);
}
catch (std::exception& e)
{
e.what();
//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===EXCEPT:%s", e.what());
}
catch (...)
{
//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===LINE:%d", __LINE__);
ROS_DEBUG_NAMED("\tinterop", "Error calling ROSInit");
return false;

}


if (!ros::master::check())
{

//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "===ROSCORE NOT RUNNING, But should I be checking? LINE:%d", __LINE__);
ROS_DEBUG_NAMED("\tinterop", "ROScore does not seem to be running..returning.");
ROS_FATAL("roscore not running.  Unfortunately will need to tear down and restart this process.");
return false;


}




mp_NodeHandle = new ros::NodeHandle();
return true;

}
*/
void ROSProc::terminateThreads()
{

	boost::unordered_map<std::string, _ROSCircQueue_shared >::iterator it;

	for (it = mInBuffers.begin(); it != mInBuffers.end(); it++)
		commandThread(it->first.c_str(), ROSProc::threadAction::SHUTDOWN);

	for (it = mOutBuffers.begin(); it != mOutBuffers.end(); it++)
		commandThread(it->first.c_str(), ROSProc::threadAction::SHUTDOWN);

}

void ROSProc::ros_soft_shutdown()
{
	WHEREAMI

		terminateThreads();
	notifyThread(mPubThreads, "", true); //wake everyone, may not be necessary, but just in case.
	notifyThread(mSubThreads, "", true); //wake everyone in the event they are sleeping
	RDB("\tSoft shutdown.  Node still active. Subs and Pubs all shutdown");
}


void ROSProc::ros_shutdown()
{
	WHEREAMI

		terminateThreads();
	notifyThread(mPubThreads, "", true); //wake everyone, may not be necessary, but just in case.
	notifyThread(mSubThreads, "", true); //wake everyone in the event they are sleeping
	RDB("\tabout to call ROS::shutdown()");

	ros::shutdown();
	RDB("\tcompleted call to ROS::shutdown(). Should exit host process now.");
	std::cout << "here now" << std::endl;

	mp_NodeHandle->shutdown();//just added

	if (mp_NodeHandle)
		delete mp_NodeHandle;

}

void ROSProc::conn_cb(const ros::SingleSubscriberPublisher&)
{
	WHEREAMI

		ROS_DEBUG_NAMED("\tinterop", "in conn_cb, not sure what it does or is for.");
	// If we're in lazy subscribe mode, and the first subscriber just
	// connected, then subscribe, #3389.
	/*if (g_lazy && !g_sub)
	{
	ROS_DEBUG_NAMED("interop","lazy mode; resubscribing");
	subscribe();
	}*/
}



bool ROSProc::popPubMsg(const char * topic, topic_tools::ShapeShifter & sh)
{
	//WHEREAMI

	boost::mutex::scoped_lock lock(mPubQueueMutex);

	_ROSCircQueue_shared cb_messages;

	try
	{
		cb_messages = mOutBuffers[topic];
	}
	catch (...)
	{


		ROS_ERROR_NAMED("\twhoah!  Trying to pop a circ queue for a topic that is not registered with mOutBuffers:%s at line:%d", topic, __LINE__);
		return false;

	}


	if (cb_messages->size() > 0)
	{

		_ROSBinMessage rb = cb_messages->operator[](0);
		cb_messages->pop_front();
		ROS_DEBUG_NAMED("interop_poll", "\t****************popped a message, size is %d in ros_pub", bytesToInt(rb.get()));

		int msgSize = bytesToInt(rb.get());
		ros::serialization::OStream s(rb.get() + 4, msgSize + 4);
		sh.read(s);
		return true;
	}
	else
	{

		return false;

	}

}


void ROSProc::processThreadCommand(boost::shared_ptr<ROSProc::threadHelper> th)
{
	WHEREAMI

		//PRESENTLY not doing anything, keep around just in case.

#if defined(WIN32) || defined (PLATFORM_WINDOWS)
#pragma message("processThreadCommand not presently being used.")
#else
		//#pragma message "processThreadCommand not presently being used."
#endif

		threadHelper::threadCommand tc;

	if (th->cmdQueue.pop(tc))
	{

		RDB("\tCommand in cmdQueue for this thread.  Enum command value is %d", tc.cmd);

	}


}



void ROSProc::ros_pub(std::string topic,
	std::string  MD5,
	std::string dataType,
	std::string definition,
	int loopRate,
	bool latching)

{


	WHEREAMI

		/*char *tmp = new char[topic.size() + 1];
		strcpy(tmp, topic.c_str());
		gThreadTopic.reset(tmp);*/


		RDB("\t sleeping for a bit to make certain I am registered in the queue");
	RDB("\tAwoke.");
	SLEEP(1000);

	if (!MAPHAS(mPubThreads, topic))
	{

		ROS_FATAL("\tno publisher thread registered for this topic. line:%d", __LINE__);
		return;


	}

	boost::shared_ptr<ROSProc::threadHelper> th = mPubThreads[topic];
	threadHelper::threadCommand tc;



	RDB("\tmorphing shapeshifter: topic:%s, md5:%s", topic.c_str(), MD5.c_str());
	RDB("\tdatatype:%s:, definition:%s, looprate:%d", dataType.c_str(), definition.c_str(), loopRate);//, latching);


	boost::shared_ptr < threadHelper> st = mPubThreads[topic];

	topic_tools::ShapeShifter sh;


	sh.morph(MD5, dataType, definition, latching ? "true" : "false");
	th->m_pub = sh.advertise(*mp_NodeHandle, topic.c_str(), loopRate, latching, boost::bind(&ROSProc::conn_cb, this, _1));

	int count = 0;

	ros::Rate *plr = new ros::Rate(loopRate);



	while (ros::ok())
	{
		//	mGlobalPubSubMutex.lock();

		/*wait until a new topic is published before I wake up
		why waste cycles if I don't need to.
		every call to pub will pulse this conditional.

		if it awakes for "spurious" reasons, it will be ok because popPubMsg won't return true unless there is a message waiting.
		*/
		//WHEREAMI
		//	RDB("\tCYCLE %s", topic.c_str());
		//std::cout << topic << std::endl;

		//print out every 5 seconds so it is clear we are in a little loop
		ROS_DEBUG_THROTTLE_NAMED(5, "interop_poll", "(1)%s:In publication loop for topic (%s)", __FUNCTION__, topic.c_str());
		//continue; //WTF, did I put this here? This fucked up everything.   Can't IMAGINE why I would have this here...very old github look doesn't show this...

		//	RDB("1\n");
		if (popPubMsg(topic.c_str(), sh))
		{
			//					RDB("2\n");
			th->m_pub.publish(sh);
			//					RDB("3\n");

		}
		{

			//RDB("NO MESSAGE ON QUEUE");
		}
		//		RDB("4\n");
		//	RDB("4\n");
		if (th->cmdQueue.pop(tc))
		{

			RDB("\tCommand in cmdQueue for this thread.  Enum command value is %d", tc.cmd);
			switch (tc.cmd)
			{
			case(threadAction::CHANGE_POLL_RATE):
				RDB("\tChanging pub rate for topic:%s to %d", topic.c_str(), th->loop_rate);
				delete plr;
				plr = new ros::Rate(th->loop_rate);
				break;

			case(threadAction::SHUTDOWN):
				RDB("\tShutdown message recieved...returning from thread.");
				th->m_pub.shutdown(); //may not be necessary

				mPubThreads.erase(topic); //remove myself from the queue, I am gone forever
				mOutBuffers.erase(topic); //not sure this is a good idea
				RDB("\tremoved thread from mPubThreads.");
				//		gThreadTopic.release(); //8/31
				delete plr;
				//ros::shutdown();

				return;

			default:

				break;

			}

		}

		//		st->cv.wait(st->plk);
		//RDB("5\n");

		try
		{
			ros::spinOnce();
		}
		catch (...)
		{

			RDB("BOOM!!");
		}
		//	RDB("5.1\n");
		//	mGlobalPubSubMutex.unlock();


		plr->sleep();
		//	RDB("5.2\n");
		++count;


	}
	//this area probably never called unless rude shutdown.
	//	gThreadTopic.release(); //8/31
	delete plr;
	//	RDB("6\n");
	RDB("\tLeft publishing loop, thread termninating.");


}

//any time message is coming in, this gets called back.
void ROSProc::sub_cb(const ros::MessageEvent<topic_tools::ShapeShifter>& msg_event, std::string topic)
{

	//WHEREAMI

	//greg11, 10/17, addthing this because thread is not on the same TLS as ros_sub.
	if (gThreadTopic2[0] == 0)
	{
		strcpy(gThreadTopic2, topic.c_str());
		RDB("*Initial copy of TLS topic:%s, thread_id:%d\n",
			gThreadTopic2, boost::lexical_cast<int>(boost::this_thread::get_id()));
	}



	boost::shared_ptr<topic_tools::ShapeShifter const> const &msg = msg_event.getConstMessage();
	boost::shared_ptr<const ros::M_string> const& connection_header = msg_event.getConnectionHeaderPtr();

	ros::SerializedMessage m = ros::serialization::serializeMessage<topic_tools::ShapeShifter>(*msg);
	uint8_t* ptr = m.buf.get();


	//	uint8_t temp[255];



	int size = msg->size(); //size of the TRUE message.  This will be 24 for point, for ex.
	_ROSBinMessage ar(new uint8_t[size + 4]); //putting size up front, now we have *28*, thats 24 after the first 4 which will be our size

											  //RDB("**size:%d, threadtopic:%s", size, gThreadTopic.get() );
	memcpy(ar.get(), ptr, size + 4);
	try
	{
		boost::mutex::scoped_lock lock2(mGlobalPubSubMutex);
		boost::mutex::scoped_lock lock(mSubQueueMutex);
		// mInBuffers[gThreadTopic.get()]->push_back(ar); //TODO: put a reference to mInBuffers in TLS so that we don't incur this call with every message received. //greg 8/31

		mInBuffers[gThreadTopic2]->push_back(ar); //TODO: put a reference to mInBuffers in TLS so that we don't incur this call with every message received. //greg 8/31

	}
	catch (...)
	{
		WHEREAMI
			RDB("\tFATAL: Crash on push_back.");


	}


}



void ROSProc::ros_sub(std::string topic,
	std::string  MD5,
	std::string dataType,
	std::string definition,
	int loopRate,
	bool latching)
{

	WHEREAMI

		//copy topic into global TLS for access by callback
		/*char *tmp = new char[topic.size()+1];
		strcpy(tmp, topic.c_str());
		gThreadTopic.reset(tmp);*/ //8/31, causing collisions with pub for some reason.  Decided to go compiler-specific TLS

		//greg1, 10-17 commented out below 2 lines as these turn out to be in different threads
		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "--ROSSUBLINE:%d", __LINE__);			
		RDB("*ros_sub, diaplaying:topic:%s, threadid:%d\n", topic.c_str(), boost::lexical_cast<int>(boost::this_thread::get_id()));
	//strcpy(gThreadTopic2, topic.c_str());


	//end copy

	RDB("\t sleeping for a bit to make certain I am registered in the queue");
	SLEEP(1000);
	RDB("\tAwoke.");

	if (!MAPHAS(mSubThreads, topic))
	{
		ROS_FATAL("\tno Subscriber thread registered for this topic. line:%d", __LINE__);
		return;
	}

	boost::shared_ptr<ROSProc::threadHelper> th = mSubThreads[topic];
	threadHelper::threadCommand tc;

	RDB("\tmorphing shapeshifter: topic:%s, md5:%s, datatype:%s, definition:%s, looprate:%d",
		topic.c_str(),
		MD5.c_str(),
		dataType.c_str(),
		definition.c_str(),
		loopRate);//,
				  //latching);

				  //boost::shared_ptr < threadHelper> st = mSubThreads[topic]; //not this

				  //topic_tools::ShapeShifter sh;

	ros::Rate * plr = new ros::Rate(loopRate);

	int count = 0;

	//greg1 mod 10/17
	//th->m_sub = new ros::Subscriber(mp_NodeHandle->subscribe(topic, 10, &ROSProc::sub_cb, this, th->hint)); //leak!
	//boost::function<void(const ros::MessageEvent<topic_tools::ShapeShifter&>)> f1(boost::bind(&ROSProc::sub_cb, this,_1)); //reference

	//greg1:added 10/17
	th->m_sub = new ros::Subscriber(mp_NodeHandle->subscribe< topic_tools::ShapeShifter  >(topic, 10,
		boost::bind(&ROSProc::sub_cb, this, _1, topic))); //leak!

														  //__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "--CREATE_SUBSCRIBER_LINE:%d", __LINE__);			


	while (ros::ok())
	{

		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "--entering loop:%d", __LINE__);			

#ifdef LOG_IN_ROS_SUB		
		WHEREAMI
			RDB("\tSUB CYCLE %s", topic.c_str());
#endif
		//print out every 5 seconds so it is clear we are in a little loop
		ROS_DEBUG_THROTTLE_NAMED(5, "interop_poll", "%s: In subscription loop for topic %s", __FUNCTION__, topic.c_str());

		if (th->cmdQueue.pop(tc))
		{

			RDB("\tCommand in cmdQueue for this thread.  Enum command value is %d", tc.cmd);
			boost::mutex::scoped_lock lock(mSubQueueMutex); //in case we are going to pull ourselves from mInBuffers. 
			int loc;

			switch (tc.cmd)
			{
			case(threadAction::CHANGE_POLL_RATE):
				RDB("\tChanging %s sub loop rate to:%d", topic.c_str(), th->loop_rate);
				delete plr;
				plr = new ros::Rate(th->loop_rate);

				break;

			case(threadAction::SHUTDOWN):
				RDB("\tShutdown message recieved...returning from thread.");
				th->m_sub->shutdown(); //may not be necessary
				mSubThreads.erase(topic); //remove myself from the queue, I am gone forever

				loc = mInBuffers.erase(topic); //not sure this is a good idea
				delete th->m_sub;

				RDB("\tremoved thread for topic %s from mSubThreads and mInBuffers, erased at location %d.", topic.c_str(), loc);
				delete plr;
				return;

			default:

				break;

			}

		}

		//	st->cv.wait(st->plk); //dont want this on a subscriber, never know when something is coming in. 

		ros::spinOnce();
		//		ros::spin();
		//		loop_rate.sleep(); //not sure i need this, but we will leave this for the time being, the cvar is doing this job. 
		plr->sleep();
		++count;

	}






	//	if (plr)
	//	delete plr;
	RDB("\tLeft publishing loop, thread termninating.");



}



void pubProxyTest(std::string  topic)
{

	std::cout << "\nproxy test:" << topic << "tid:" << boost::this_thread::get_id() << std::endl;

}


void ROSProc::addThread(const char * topic, boost::shared_ptr<boost::thread > th)
{
	WHEREAMI

		boost::shared_ptr<threadHelper> sh(new threadHelper(th));
	mPubThreads[topic] = sh;


}

//int ROSProc::spinPublisher(InitHelper &inh, const char * topic, const char * MD5, const char * dataType,
//	const char* msgDefinition, int loopRate, bool latching)



void ROSProc::dumpTopic(const char * topic)
{

	BOOST_FOREACH(_ROSBinMessage & b, *(mOutBuffers[topic]))
	{
		int size = bytesToInt(b.get());

		ROS_DEBUG_NAMED("interop", "Unpacked size for %s is:%d", topic, size);

		dump(b.get() + 4, size);
	}


	/*_ROSBinMessage sh(mOutBuffers[topic]->operator[](0));
	int size= bytesToInt(sh.get());

	ROS_INFO("Unpacked size for %s is:%d", topic, size);

	dump(sh.get() + 4, size);*/


}


void ROSProc::test()
{
	//ROS_DEBUG_NAMED("interop","test func in RosProc");
	//_ROSCircQueue_shared shq(new _ROSCircularBuffer(nCirqSize)); //new share pointer to a new circular topic buffer
	//_ROSBinMessage ar(new uint8_t[10]);
	//uint8_t msg[10];
	//memcpy(ar.get(), msg, 10);

	//mOutBuffers["test"] = shq;
	//mOutBuffers["test"]->push_back(ar);

	//mOutBuffers["test"]->pop_front();
	//
	//ROS_DEBUG_NAMED("interop","end test, shq:%d ar:%d",shq.use_count(), ar.use_count());
	std::string s("hi there");


	boost::thread *t = new boost::thread(boost::bind(pubProxyTest, _1), s);
	return;




}


bool ROSProc::createPubQueue(const char * topic, int qsize)
{
	WHEREAMI


		if (!mOutBuffers.count(topic))
		{
			_ROSCircQueue_shared shq(new _ROSCircularBuffer(qsize)); //new share pointer to a new circular topic buffer
			mOutBuffers[topic] = shq;
			ROS_DEBUG_NAMED("interop", "\tPUB Topic queue did not exist...CREATING and adding, size of:%d.", qsize);
			return true;

		}
		else
		{
			ROS_DEBUG_NAMED("interop", "\tPUB Topic ALREADY exists...adding new message to topic %s", topic);
			dumpMap(mOutBuffers);

			return false;
		}

}


void  ROSProc::dumpMap(boost::unordered_map<std::string, _ROSCircQueue_shared > & m)
{
	WHEREAMI

		boost::unordered_map<std::string, _ROSCircQueue_shared >::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		RDB("\tTopicDump:%s", it->first.c_str());

	}


}

bool ROSProc::createSubQueue(const char * topic, int qsize)
{
	WHEREAMI


		if (!mInBuffers.count(topic))
		{
			_ROSCircQueue_shared shq(new _ROSCircularBuffer(qsize)); //new share pointer to a new circular topic buffer
			mInBuffers[topic] = shq;
			ROS_DEBUG_NAMED("interop", "\tSub Topic queue did not exist...CREATING and adding, size of:%d.", qsize);
			return true;

		}
		else
		{
			ROS_DEBUG_NAMED("interop", "\tSub Topic ALREADY exists...adding new message to topic %s", topic);

			dumpMap(mInBuffers);

			return false;
		}

}

//deprecated
void ROSProc::notifyPubThread(const char * topic, bool bWakeEveryone)
{

	WHEREAMI

		RDB("\tdeprecated");


	if (!bWakeEveryone)
	{
		int cnt = mPubThreads.count(topic);

		if (!cnt)
		{
			RDB("\tno publisher thread waiting on topic %s, returning", topic);
			return;
		}

		try
		{
			RDB("\t********number of pubs for this topic is: %d", cnt);
			mPubThreads[topic]->cv.notify_one();
			RDB("\t++++after");
		}
		catch (...)
		{

			RDB("\tcould not get conditional variable for %s", topic);

		}
	}
	else
	{
		typedef boost::unordered_map<std::string, boost::shared_ptr < threadHelper> > map_t;
		map_t mmap;

		BOOST_FOREACH(map_t::value_type &i, mPubThreads)
		{
			RDB("\twaking thread:%s", i.first.c_str());
			i.second->cv.notify_all();

		}


	}
}

void ROSProc::notifyThread(boost::unordered_map<std::string,
	boost::shared_ptr < threadHelper> >& map,
	const char * topic,
	bool bWakeEveryone)
{

	WHEREAMI

		if (!bWakeEveryone)
		{
			int cnt = map.count(topic);

			if (!cnt)
			{
				RDB("\tno publisher/sub thread waiting on topic %s, returning", topic);
				return;
			}

			try
			{
				RDB("\t********number of pub/subs for this topic is: %d", cnt);
				map[topic]->cv.notify_one();
				RDB("\t++++after");
			}
			catch (...)
			{

				RDB("\tcould not get conditional variable for %s", topic);

			}
		}
		else
		{
			typedef boost::unordered_map<std::string, boost::shared_ptr < threadHelper> > map_t;
			map_t mmap;

			BOOST_FOREACH(map_t::value_type &i, map)
			{
				RDB("\twaking thread:%s", i.first.c_str());
				i.second->cv.notify_all();

			}


		}
}


int ROSProc::pubMessage(const char * topic, uint8_t * msg, int size) //note size is deprecated, we aren't using it, we are looking at message beginning
{

	WHEREAMI

		//first check if this topic is in our outqueues, if not add it
		ROS_DEBUG_NAMED("interop", "\tMessage size is: %d, at line:%d", bytesToInt(msg), __LINE__);

	boost::mutex::scoped_lock lock(mPubQueueMutex);

	if (!mOutBuffers.count(topic)) //I hate this check.  TODO: find a better way than burn cycles on this every time. 
	{
		RDB("\tNo publisher queue exists for this topic.  Possibly not created yet or otherwise torn down. Returning.");
		return 0;

	}
	//commented below because I think we are actually +4 when you include the 4 byte size header in the beginning
	//size = bytesToInt(msg);
	//if (!mOutBuffers.count(topic))
	//{
	//	_ROSCircQueue_shared shq(new _ROSCircularBuffer(nCirqSize)); //new share pointer to a new circular topic buffer
	//	mOutBuffers[topic] = shq;
	//	ROS_DEBUG_NAMED("interop","\tTopic queue did not exist...creating and adding.");
	//}
	//else
	//	ROS_DEBUG_NAMED("interop","\tTopic already exists...adding new message to topic %s", topic);
	//now lets put our message on the queue
	//_ROSBinMessage ar(new uint8_t[size-4]);//chop off the leading size parameter

	_ROSBinMessage ar(new uint8_t[size]);//dont chop off leading 4, we need it later to deserialize
	memcpy(ar.get(), msg, size);

	//don't want to do below if spinpub hasn't been called. 
	try
	{

		mOutBuffers[topic]->push_back(ar); //TODO: make sure the buffer is there and not torn down

	}
	catch (...)
	{
		RDB("\tTried to publish message on non-existant queue.  Pub thread was likely explicitly ordered to shutdown.");


	}
	ROS_DEBUG_NAMED("interop", "\tMessage placed on queue:%s, count msgs for topic:%d", topic, mOutBuffers[topic]->size());

	//#define ENABLE_DEPRECATED
#ifdef ENABLE_DEPRECATED
	notifyPubThread(topic);
#endif

	//create new topic circular buffer, yikes
	//boost::unordered_map<std::string, _ROSCircQueue_shared > test;
	//	if (test.count("testkey"))
	//	{
	//	
	//	_ROSCircQueue_shared sh2(test["testkey"]);
	//	sh2->push_back(ar);
	//}
	//else //it aint there yet, but it in.
	//{
	//	_ROSCircQueue_shared sh(new _ROSCircularBuffer(10)); //new share pointer to a new circular topic buffer
	//	sh->push_back(ar); //add on our binary array
	//	test["testkey"] = sh;
	//}
	//_ROSCircQueue_shared sh3(test["testkey"]);
	//_ROSBinMessage rbm(sh3->operator[](0));
	//dump(rbm.get(), size);

	return size;



}

void ROSProc::notifyPublisherQueue(const char * topic, threadAction t)
{

	WHEREAMI

		if (MAPHAS(mPubThreads, topic))
		{
			mPubThreads[topic]->cmdQueue.push(t);
			notifyThread(mPubThreads, topic); //wake him up in case he is sleeping on the mutex
			return;
		}
		else
		{
			RDB("\tcommandThead called with command:%d for topic:%s but thread does not exist which services this topic in publishers, trying subscribers.", t, topic);
		}



}

void ROSProc::notifySubscriberQueue(const char * topic, threadAction t)
{
	if (MAPHAS(mSubThreads, topic))
	{
		mSubThreads[topic]->cmdQueue.push(t);
		notifyThread(mSubThreads, topic); //wake him up in case he is sleeping on the mutex
		return;
	}
	else
	{
		RDB("\tcommandThead called with command:%d for topic:%s but thread does not exist which services this topic in subscribers.", t, topic);
	}
}


void ROSProc::commandThread2(short pubsub, const char * topic, threadAction t)
{
	WHEREAMI

		if (pubsub == 0)
		{
			if (MAPHAS(mPubThreads, topic))
			{
				mPubThreads[topic]->cmdQueue.push(t);
				notifyThread(mPubThreads, topic); //wake him up in case he is sleeping on the mutex
				return;
			}
			else
			{
				RDB("\tcommandThead called with command:%d for topic:%s but thread does not exist which services this topic in publishers, trying subscribers.", t, topic);
			}
		}
		else if (pubsub == 1)
		{

			if (MAPHAS(mSubThreads, topic))
			{
				mSubThreads[topic]->cmdQueue.push(t);
				notifyThread(mSubThreads, topic); //wake him up in case he is sleeping on the mutex
				return;
			}
			else
			{
				RDB("\tcommandThead called with command:%d for topic:%s but thread does not exist which services this topic in subscribers.", t, topic);
			}
		}



}





void ROSProc::commandThread(const char * topic, threadAction t)
{
	WHEREAMI

		if (MAPHAS(mPubThreads, topic))
		{
			mPubThreads[topic]->cmdQueue.push(t);
			notifyThread(mPubThreads, topic); //wake him up in case he is sleeping on the mutex
			return;
		}
		else
		{
			RDB("\tcommandThead called with command:%d for topic:%s but thread does not exist which services this topic in publishers, trying subscribers.", t, topic);
		}


	if (MAPHAS(mSubThreads, topic))
	{
		mSubThreads[topic]->cmdQueue.push(t);
		notifyThread(mSubThreads, topic); //wake him up in case he is sleeping on the mutex
		return;
	}
	else
	{
		RDB("\tcommandThead called with command:%d for topic:%s but thread does not exist which services this topic in subscribers.", t, topic);
	}




}


int ROSProc::spinSubscriber(const char * topic,
	const char * MD5,
	const char * dataType,
	const char* msgDefinition,
	int loopRate,
	int qsize,
	bool latching)
{
	boost::mutex::scoped_lock lock(mSubQueueMutex);

	boost::thread * t;
	WHEREAMI
		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "**LINE:%d", __LINE__);	
		if (!mp_NodeHandle)
		{
			//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "**_BAD_LINE:%d", __LINE__);			

			ROS_FATAL("No nodehandle. It is likely roscore is not running. NOP.");
			return 0;

		}
	//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "**LINE:%d", __LINE__);			
	if (!createSubQueue(topic, qsize))
	{
		//__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "**LINE:%d", __LINE__);			

		RDB("\tSublisher queue already exists.  Will not recreate Queue. Leaving in place. ");
		return 0;

	}

	ROS_DEBUG_NAMED("interop",
		"\ttopic:%s, md5:%s, datatype:%s, definition:%s, looprate:%d",
		topic,
		MD5,
		dataType,
		msgDefinition,
		loopRate);//,
				  //latching);

	ROS_DEBUG_NAMED("interop",
		"\tcount of mInBuffer is %d and this topic has %d messages, threads on this topic:%d",
		mInBuffers.size(),
		mInBuffers[topic]->size(),
		mSubThreads.size());

	//	__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "*count of mInBuffer is % d and this topic has % d messages, threads on this topic :% d",
	/*	mInBuffers.size(),
	mInBuffers[topic]->size(),
	mSubThreads.size()
	);	*/

	std::string   _topic(topic), _MD5(MD5), _dataType(dataType), _msgDefinition(msgDefinition); //so as to pass by value to other thread
	t = new boost::thread(&ROSProc::ros_sub, this, _topic, _MD5, _dataType, _msgDefinition, loopRate, latching);

	boost::shared_ptr<boost::thread > st(t);

	ROS_DEBUG_NAMED("interop", "\tadding SUB thread for topic %s to publishing threads vector.", topic);

	boost::shared_ptr<threadHelper> sh(new threadHelper(st));
	mSubThreads[topic] = sh;


	return 0;




}

int ROSProc::spinPublisher(const char * topic,
	const char * MD5,
	const char * dataType,
	const char* msgDefinition,
	int loopRate,
	int qsize,
	bool latching)

{

	boost::thread * t;

	//	t = new boost::thread(pubProxyTest,  buff);
	//	t = new boost::thread(boost::bind(pubProxyTest, _1), buff);
	//	return 0;
	//end zone
	WHEREAMI

		if (!mp_NodeHandle)
		{
			ROS_FATAL("No nodehandle. It is likely roscore is not running. NOP.");
			return 0;

		}

	if (!createPubQueue(topic, qsize))
	{


		RDB("\tPublisher queue already exists.  Likely spinPublisher was called multiple times.");
		return 0;

	}

	ROS_DEBUG_NAMED("interop",
		"\ttopic:%s, md5:%s, datatype:%s, definition:%s, looprate:%d",
		topic,
		MD5,
		dataType,
		msgDefinition,
		loopRate);//,
				  //latching);
				  //ROS_DEBUG_NAMED("interop","\tstarting pub thread to watch for topic %s, md5:%s", topic, MD5);
				  //	void ros_pub(int argc, const char ** arv, const char * nodeName, const char * topic, const char * MD5, const char * dataType, const char* definition, int loopRate, bool latching);
	ROS_DEBUG_NAMED("interop",
		"\tcount of mOutBuffer is %d and this topic has %d messages, threads on this topic:%d",
		mOutBuffers.size(),
		mOutBuffers[topic]->size(),
		mPubThreads.size());




	//	_ROSCircQueue_shared cb_messages = mOutBuffers[topic];
	//_ROSBinMessage rb = cb_messages->operator[](0);
	//	ROS_DEBUG_NAMED("interop","popped a message, size is %d, thread exiting", bytesToInt(cb_messages->operator[](0).get()));
	//	cb_messages->pop_front();
	//	return 0; //above testing in this thread to see if corruption problem tween threads


	//if (MAPHAS(mPubThreads,topic))
	//{
	//	ROS_DEBUG_NAMED("interop","\tA publisher thread is already spun for the topic.", topic);
	//	return 0;
	//}

	//debug zone
	//	boost::bind(&ROSProc::ros_pub, this, _1, _2, _3, _4, _5, _6, _7).operator()(inh, topic, MD5, dataType, msgDefinition, loopRate, latching);
	//return 0;
	//end zone

	//t = new boost::thread(   boost::bind(&ROSProc::ros_pub, this, _1, _2, _3, _4, _5, _6, _7), 
	//										inh,topic, MD5, dataType, msgDefinition, loopRate, latching);
	std::string   _topic(topic), _MD5(MD5), _dataType(dataType), _msgDefinition(msgDefinition); //so as to pass by value to other thread
																								//t = new boost::thread(&ROSProc::ros_pub, this, inh, _topic, _MD5, _dataType, _msgDefinition, loopRate, latching);
	t = new boost::thread(&ROSProc::ros_pub, this, _topic, _MD5, _dataType, _msgDefinition, loopRate, latching);

	boost::shared_ptr<boost::thread > st(t);

	ROS_DEBUG_NAMED("interop", "\tadding publishing thread for topic %s to publishing threads vector.", topic);


	addThread(topic, st);

	/*ROS_DEBUG_NAMED("interop","putting thread to sleep for 2 seconds");
	boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
	ROS_DEBUG_NAMED("interop","thread awake");
	*/


	return 0;


}


bool ROSProc::changeLoopRate(const char * topic, int loop_rate)
{
	WHEREAMI

		boost::shared_ptr<threadHelper> p;


	//check and make sure this topic exists
	//and if so, find out which it is, pub or sub
	if (MAPHAS(mPubThreads, topic))
	{
		p = mPubThreads[topic];

	}
	else
		if (MAPHAS(mSubThreads, topic))
		{
			p = mSubThreads[topic];
		}
		else
		{
			RDB("\tTopic %s not found", topic);
			return false;

		}

	p->loop_rate = loop_rate; //tell this thread to operate at a different loop_rate
	commandThread(topic, threadAction::CHANGE_POLL_RATE);


	return true;
}


void ROSProc::storeProperty(const char * name, uint8_t * msg, int size)
{

	_ROSBinMessage ar(new uint8_t[size + 4]);//dont chop off leading 4, we need it later to deserialize
	intToBytes(size, ar.get());
	memcpy(ar.get() + 4, msg, size);

	try
	{
		mPropertyBag[name] = ar;
	}
	catch (...)
	{
		RDB("\tFailed to store property:%s", name);


	}

}

void ROSProc::getProperty(const char * name, uint8_t * msg, int * size)
{

	boost::unordered_map<std::string, _ROSBinMessage>::iterator it;

	it = mPropertyBag.find(name);

	if (it == mPropertyBag.end())
	{
		RDB("\tProperty Not Found:%s.", name);
		*size = 0;
		return;
	}
	else
	{
		_ROSBinMessage rb = it->second;
		*size = bytesToInt(rb.get());
		RDB("\tFound property:%s at size:%d", name, *size);
		memcpy(msg, rb.get() + 4, *size);

	}

}


#endif


#pragma pop_macro("check")

