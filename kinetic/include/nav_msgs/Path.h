// Generated by gencpp from file nav_msgs/Path.msg
// DO NOT EDIT!


#ifndef NAV_MSGS_MESSAGE_PATH_H
#define NAV_MSGS_MESSAGE_PATH_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/PoseStamped.h>

namespace nav_msgs
{
template <class ContainerAllocator>
struct Path_
{
  typedef Path_<ContainerAllocator> Type;

  Path_()
    : header()
    , poses()  {
    }
  Path_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , poses(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::geometry_msgs::PoseStamped_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::other >  _poses_type;
  _poses_type poses;




  typedef boost::shared_ptr< ::nav_msgs::Path_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::nav_msgs::Path_<ContainerAllocator> const> ConstPtr;

}; // struct Path_

typedef ::nav_msgs::Path_<std::allocator<void> > Path;

typedef boost::shared_ptr< ::nav_msgs::Path > PathPtr;
typedef boost::shared_ptr< ::nav_msgs::Path const> PathConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::nav_msgs::Path_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::nav_msgs::Path_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace nav_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'nav_msgs': ['/tmp/binarydeb/ros-kinetic-nav-msgs-1.12.5/msg', '/tmp/binarydeb/ros-kinetic-nav-msgs-1.12.5/obj-x86_64-linux-gnu/devel/share/nav_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::nav_msgs::Path_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::nav_msgs::Path_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nav_msgs::Path_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::nav_msgs::Path_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nav_msgs::Path_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::nav_msgs::Path_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::nav_msgs::Path_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6227e2b7e9cce15051f669a5e197bbf7";
  }

  static const char* value(const ::nav_msgs::Path_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6227e2b7e9cce150ULL;
  static const uint64_t static_value2 = 0x51f669a5e197bbf7ULL;
};

template<class ContainerAllocator>
struct DataType< ::nav_msgs::Path_<ContainerAllocator> >
{
  static const char* value()
  {
    return "nav_msgs/Path";
  }

  static const char* value(const ::nav_msgs::Path_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::nav_msgs::Path_<ContainerAllocator> >
{
  static const char* value()
  {
    return "#An array of poses that represents a Path for a robot to follow\n\
Header header\n\
geometry_msgs/PoseStamped[] poses\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/PoseStamped\n\
# A Pose with reference coordinate frame and timestamp\n\
Header header\n\
Pose pose\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::nav_msgs::Path_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::nav_msgs::Path_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.poses);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Path_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::nav_msgs::Path_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::nav_msgs::Path_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "poses[]" << std::endl;
    for (size_t i = 0; i < v.poses.size(); ++i)
    {
      s << indent << "  poses[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::stream(s, indent + "    ", v.poses[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // NAV_MSGS_MESSAGE_PATH_H
