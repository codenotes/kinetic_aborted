#if PLATFORM_ANDROID
#include <android/log.h>
#endif 


#define MAX_ROS_MESSAGE_SIZE 1813722
//tls specific stuff



//possible experimental alternative
//for TLS on android using thread_specific_ptr from boost

#pragma message("TLS Android Warning Experimental")


class ThreadBufferHolder
{
public:
	uint8_t msgbuf[MAX_ROS_MESSAGE_SIZE];

	uint8_t * operator*()
	{
		return msgbuf;
	}
};



#if defined(PLATFORM_WINDOWS) || defined(WIN32)
extern thread_local uint8_t * msgbuf ;
//extern uint8_t * msgbuf;
#elif PLATFORM_ANDROID

//shouldn't need anything for android, we are going to 
//try using the class
//extern uint8_t * msgbuf;
extern boost::thread_specific_ptr<ThreadBufferHolder> msgbuf;
#endif

#pragma warning(disable: 4996)


namespace rosinterop
{

	class interUtil
	{
	public:

		static bool initSimple(const char * nodeName)
		{
			return ROSInitSimple(nodeName);

		}

		static void killPub(const char * topic)
		{
			notifyPublisherQueue(topic, 0);
		}

		static void killSub(const char * topic)
		{
			notifySubscriberQueue(topic, 0);
		}



		template <class T>
		static void spinSub(char * topic, int loopRate, int qsize, bool latching)
		{
			std::string s1, s2, s3;

			s1 = ros::message_traits::MD5Sum< T>::value();
			s2 = ros::message_traits::DataType<T>::value();
			s3 = ros::message_traits::Definition<T>::value();
			spinSubscriber(topic, s1.c_str(), s2.c_str(), s3.c_str(), loopRate, qsize, latching);




		}


		template <class T>
		static void spinPub(char * topic, int loopRate, int qsize, bool latching)
		{

			std::string s1, s2, s3;

			s1 = ros::message_traits::MD5Sum< T>::value();
			s2 = ros::message_traits::DataType<T>::value();
			s3 = ros::message_traits::Definition<T>::value();
			spinPublisher(topic, s1.c_str(), s2.c_str(), s3.c_str(), loopRate, qsize, latching);


		}

		template <class T>
		static bool getMsg(const char * topic, T& msg)
		{

			//uint8_t temp[SIZE];
#if PLATFORM_WINDOWS		
			if (!msgbuf)
				msgbuf = new uint8_t[MAX_ROS_MESSAGE_SIZE];
#else

			if (!msgbuf.get())
			{
				__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "@@NOMSGBUFLINE:%d", __LINE__);
				msgbuf.reset(new ThreadBufferHolder());
			}

#endif

			//uint8_t * temp = new uint8_t[MAX_ROS_MESSAGE_SIZE];

			long size;
#if PLATFORM_WINDOWS

			//if (getMessage(topic, temp, &size))
			if (getMessage(topic, msgbuf, &size))
			{
				//ros::serialization::deserializeMessage<T>(temp, msg);
				ros::serialization::IStream stream(msgbuf, size);
				ros::serialization::deserialize(stream, msg);

				return true;
			}
			else
			{

				return false;

			}
		}
#elif PLATFORM_ANDROID

			if (getMessage(topic, **msgbuf, &size))
			{
				//				__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "@@AFTERGETMESSAGE:(%s) size:%d LINE:%d", topic, size, __LINE__);
								//ros::serialization::deserializeMessage<T>(temp, msg);
				ros::serialization::IStream stream(**msgbuf, size);
				ros::serialization::deserialize(stream, msg);

				return true;
			}
			else
			{

				__android_log_print(ANDROID_LOG_ERROR, "AndroidTalker", "@@GETMESSAGEFALSE:%d topic:%s", __LINE__, topic);
				return false;

			}
	}


#endif 

		template <class T>
		static void pubMsg(char * topic, T msg)
		{

			try {
				ros::SerializedMessage m = ros::serialization::serializeMessage<T>(msg);
				pubMessage(topic, m.buf.get(), m.num_bytes);
			}
			catch (std::exception &e)
			{
#if PLATFORM_WINDOWS
				MessageBoxA(0, "!", e.what(), MB_OK);
#endif
			}

		}



		template <class T>
		static bool getMsgBag(const char * bagFile, const char * topic, T& msg)
		{


		}




		};
	}
	;
}

