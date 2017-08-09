/* Auto-generated by genmsg_cpp for file C:\ros\kinetic\share\geometry_msgs\msg\Accel.msg */
#ifndef GEOMETRY_MSGS_MESSAGE_ACCEL_H
#define GEOMETRY_MSGS_MESSAGE_ACCEL_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Vector3.h"

UNREAL CLASS HEADER STUFF

namespace geometry_msgs
{
template <class ContainerAllocator>
struct Accel_ {
  typedef Accel_<ContainerAllocator> Type;

  Accel_()
  : linear()
  , angular()
  {
  }

  Accel_(const ContainerAllocator& _alloc)
  : linear(_alloc)
  , angular(_alloc)
  {
  }

  typedef  ::geometry_msgs::Vector3_<ContainerAllocator>  _linear_type;
   ::geometry_msgs::Vector3_<ContainerAllocator>  linear;

  typedef  ::geometry_msgs::Vector3_<ContainerAllocator>  _angular_type;
   ::geometry_msgs::Vector3_<ContainerAllocator>  angular;


  typedef boost::shared_ptr< ::geometry_msgs::Accel_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::geometry_msgs::Accel_<ContainerAllocator>  const> ConstPtr;
}; // struct Accel
typedef  ::geometry_msgs::Accel_<std::allocator<void> > Accel;

typedef boost::shared_ptr< ::geometry_msgs::Accel> AccelPtr;
typedef boost::shared_ptr< ::geometry_msgs::Accel const> AccelConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::geometry_msgs::Accel_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::geometry_msgs::Accel_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace geometry_msgs

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::geometry_msgs::Accel_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::geometry_msgs::Accel_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::geometry_msgs::Accel_<ContainerAllocator> > {
  static const char* value() 
  {
    return "9f195f881246fdfa2798d1d3eebca84a";
  }

  static const char* value(const  ::geometry_msgs::Accel_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x9f195f881246fdfaULL;
  static const uint64_t static_value2 = 0x2798d1d3eebca84aULL;
};

template<class ContainerAllocator>
struct DataType< ::geometry_msgs::Accel_<ContainerAllocator> > {
  static const char* value() 
  {
    return "geometry_msgs/Accel";
  }

  static const char* value(const  ::geometry_msgs::Accel_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::geometry_msgs::Accel_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# This expresses acceleration in free space broken into its linear and angular parts.\n\
Vector3  linear\n\
Vector3  angular\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
# It is only meant to represent a direction. Therefore, it does not\n\
# make sense to apply a translation to it (e.g., when applying a \n\
# generic rigid transformation to a Vector3, tf2 will only apply the\n\
# rotation). If you want your data to be translatable too, use the\n\
# geometry_msgs/Point message instead.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const  ::geometry_msgs::Accel_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::geometry_msgs::Accel_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::geometry_msgs::Accel_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.linear);
    stream.next(m.angular);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER
}; // struct Accel_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::geometry_msgs::Accel_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::geometry_msgs::Accel_<ContainerAllocator> & v) 
  {
    s << indent << "linear: ";
s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.linear);
    s << indent << "angular: ";
s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.angular);
  }
};


} // namespace message_operations
} // namespace ros

#endif // GEOMETRY_MSGS_MESSAGE_ACCEL_H

