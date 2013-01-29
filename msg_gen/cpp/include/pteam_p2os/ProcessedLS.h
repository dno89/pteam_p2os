/* Auto-generated by genmsg_cpp for file /home/dano/projects/ros-fuerte-ws/pteam_p2os/msg/ProcessedLS.msg */
#ifndef PTEAM_P2OS_MESSAGE_PROCESSEDLS_H
#define PTEAM_P2OS_MESSAGE_PROCESSEDLS_H
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

#include "std_msgs/Header.h"

namespace pteam_p2os
{
template <class ContainerAllocator>
struct ProcessedLS_ {
  typedef ProcessedLS_<ContainerAllocator> Type;

  ProcessedLS_()
  : header()
  , data()
  {
  }

  ProcessedLS_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , data(_alloc)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _data_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  data;


  typedef boost::shared_ptr< ::pteam_p2os::ProcessedLS_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pteam_p2os::ProcessedLS_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct ProcessedLS
typedef  ::pteam_p2os::ProcessedLS_<std::allocator<void> > ProcessedLS;

typedef boost::shared_ptr< ::pteam_p2os::ProcessedLS> ProcessedLSPtr;
typedef boost::shared_ptr< ::pteam_p2os::ProcessedLS const> ProcessedLSConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::pteam_p2os::ProcessedLS_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::pteam_p2os::ProcessedLS_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace pteam_p2os

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::pteam_p2os::ProcessedLS_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::pteam_p2os::ProcessedLS_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::pteam_p2os::ProcessedLS_<ContainerAllocator> > {
  static const char* value() 
  {
    return "c99a9440709e4d4a9716d55b8270d5e7";
  }

  static const char* value(const  ::pteam_p2os::ProcessedLS_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xc99a9440709e4d4aULL;
  static const uint64_t static_value2 = 0x9716d55b8270d5e7ULL;
};

template<class ContainerAllocator>
struct DataType< ::pteam_p2os::ProcessedLS_<ContainerAllocator> > {
  static const char* value() 
  {
    return "pteam_p2os/ProcessedLS";
  }

  static const char* value(const  ::pteam_p2os::ProcessedLS_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::pteam_p2os::ProcessedLS_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Header header\n\
string data\n\
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
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
";
  }

  static const char* value(const  ::pteam_p2os::ProcessedLS_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::pteam_p2os::ProcessedLS_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::pteam_p2os::ProcessedLS_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::pteam_p2os::ProcessedLS_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.data);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct ProcessedLS_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::pteam_p2os::ProcessedLS_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::pteam_p2os::ProcessedLS_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "data: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.data);
  }
};


} // namespace message_operations
} // namespace ros

#endif // PTEAM_P2OS_MESSAGE_PROCESSEDLS_H

