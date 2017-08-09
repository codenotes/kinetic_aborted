// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


#include <mutex>
#include <condition_variable>

#include "stdint.h"
//#include "targetver.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <ros/ros.h>
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
#include "../ROSProc.h"

#include <OaIdl.h> //for SAFEARRAY

//for TF
#include "tf2_msgs/TFMessage.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf/transform_broadcaster.h"
#include "dynamic_reconfigure/Config.h"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <rosbag/bag.h>
#include <rosbag/view.h>
#include "geometry_msgs/Pose.h"

#include "winsock2.h"
// TODO: reference additional headers your program requires here



// TODO: reference additional headers your program requires here




// TODO: reference additional headers your program requires here
