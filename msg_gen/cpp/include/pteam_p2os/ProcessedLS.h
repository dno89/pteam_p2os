/* Auto-generated by genmsg_cpp for file /home/francesca/fuerte_workspace/competition/pteam_p2os/msg/ProcessedLS.msg */
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
#include "sensor_msgs/LaserScan.h"

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

  typedef  ::sensor_msgs::LaserScan_<ContainerAllocator>  _data_type;
   ::sensor_msgs::LaserScan_<ContainerAllocator>  data;


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
    return "2061fba751b50e7a91d1c4c774250599";
  }

  static const char* value(const  ::pteam_p2os::ProcessedLS_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x2061fba751b50e7aULL;
  static const uint64_t static_value2 = 0x91d1c4c774250599ULL;
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
sensor_msgs/LaserScan data\n\
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
================================================================================\n\
MSG: sensor_msgs/LaserScan\n\
# Single scan from a planar laser range-finder\n\
#\n\
# If you have another ranging device with different behavior (e.g. a sonar\n\
# array), please find or create a different message, since applications\n\
# will make fairly laser-specific assumptions about this data\n\
\n\
Header header            # timestamp in the header is the acquisition time of \n\
                         # the first ray in the scan.\n\
                         #\n\
                         # in frame frame_id, angles are measured around \n\
                         # the positive Z axis (counterclockwise, if Z is up)\n\
                         # with zero angle being forward along the x axis\n\
                         \n\
float32 angle_min        # start angle of the scan [rad]\n\
float32 angle_max        # end angle of the scan [rad]\n\
float32 angle_increment  # angular distance between measurements [rad]\n\
\n\
float32 time_increment   # time between measurements [seconds] - if your scanner\n\
                         # is moving, this will be used in interpolating position\n\
                         # of 3d points\n\
float32 scan_time        # time between scans [seconds]\n\
\n\
float32 range_min        # minimum range value [m]\n\
float32 range_max        # maximum range value [m]\n\
\n\
float32[] ranges         # range data [m] (Note: values < range_min or > range_max should be discarded)\n\
float32[] intensities    # intensity data [device-specific units].  If your\n\
                         # device does not provide intensities, please leave\n\
                         # the array empty.\n\
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
s << std::endl;
    Printer< ::sensor_msgs::LaserScan_<ContainerAllocator> >::stream(s, indent + "  ", v.data);
  }
};


} // namespace message_operations
} // namespace ros

#endif // PTEAM_P2OS_MESSAGE_PROCESSEDLS_H

