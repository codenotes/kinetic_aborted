// Generated by gencpp from file control_msgs/QueryCalibrationStateRequest.msg
// DO NOT EDIT!


#ifndef CONTROL_MSGS_MESSAGE_QUERYCALIBRATIONSTATEREQUEST_H
#define CONTROL_MSGS_MESSAGE_QUERYCALIBRATIONSTATEREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace control_msgs
{
template <class ContainerAllocator>
struct QueryCalibrationStateRequest_
{
  typedef QueryCalibrationStateRequest_<ContainerAllocator> Type;

  QueryCalibrationStateRequest_()
    {
    }
  QueryCalibrationStateRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }






  typedef boost::shared_ptr< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> const> ConstPtr;

}; // struct QueryCalibrationStateRequest_

typedef ::control_msgs::QueryCalibrationStateRequest_<std::allocator<void> > QueryCalibrationStateRequest;

typedef boost::shared_ptr< ::control_msgs::QueryCalibrationStateRequest > QueryCalibrationStateRequestPtr;
typedef boost::shared_ptr< ::control_msgs::QueryCalibrationStateRequest const> QueryCalibrationStateRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace control_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/kinetic/share/trajectory_msgs/cmake/../msg'], 'control_msgs': ['/tmp/binarydeb/ros-kinetic-control-msgs-1.4.0/obj-x86_64-linux-gnu/devel/share/control_msgs/msg', '/tmp/binarydeb/ros-kinetic-control-msgs-1.4.0/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "control_msgs/QueryCalibrationStateRequest";
  }

  static const char* value(const ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
";
  }

  static const char* value(const ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct QueryCalibrationStateRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::control_msgs::QueryCalibrationStateRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // CONTROL_MSGS_MESSAGE_QUERYCALIBRATIONSTATEREQUEST_H