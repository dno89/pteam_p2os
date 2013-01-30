/* Auto-generated by genmsg_cpp for file /home/dano/projects/ros-fuerte-ws/pteam_p2os/srv/RobotControl.srv */
#ifndef PTEAM_P2OS_SERVICE_ROBOTCONTROL_H
#define PTEAM_P2OS_SERVICE_ROBOTCONTROL_H
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

#include "ros/service_traits.h"




namespace pteam_p2os
{
template <class ContainerAllocator>
struct RobotControlRequest_ {
  typedef RobotControlRequest_<ContainerAllocator> Type;

  RobotControlRequest_()
  : angular_speed(0.0)
  , linear_speed(0.0)
  {
  }

  RobotControlRequest_(const ContainerAllocator& _alloc)
  : angular_speed(0.0)
  , linear_speed(0.0)
  {
  }

  typedef float _angular_speed_type;
  float angular_speed;

  typedef float _linear_speed_type;
  float linear_speed;


  typedef boost::shared_ptr< ::pteam_p2os::RobotControlRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pteam_p2os::RobotControlRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct RobotControlRequest
typedef  ::pteam_p2os::RobotControlRequest_<std::allocator<void> > RobotControlRequest;

typedef boost::shared_ptr< ::pteam_p2os::RobotControlRequest> RobotControlRequestPtr;
typedef boost::shared_ptr< ::pteam_p2os::RobotControlRequest const> RobotControlRequestConstPtr;


template <class ContainerAllocator>
struct RobotControlResponse_ {
  typedef RobotControlResponse_<ContainerAllocator> Type;

  RobotControlResponse_()
  {
  }

  RobotControlResponse_(const ContainerAllocator& _alloc)
  {
  }


  typedef boost::shared_ptr< ::pteam_p2os::RobotControlResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pteam_p2os::RobotControlResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct RobotControlResponse
typedef  ::pteam_p2os::RobotControlResponse_<std::allocator<void> > RobotControlResponse;

typedef boost::shared_ptr< ::pteam_p2os::RobotControlResponse> RobotControlResponsePtr;
typedef boost::shared_ptr< ::pteam_p2os::RobotControlResponse const> RobotControlResponseConstPtr;

struct RobotControl
{

typedef RobotControlRequest Request;
typedef RobotControlResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct RobotControl
} // namespace pteam_p2os

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::pteam_p2os::RobotControlRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::pteam_p2os::RobotControlRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::pteam_p2os::RobotControlRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "2cc72ad6dc716a7d6153d5f2a1e7f7f3";
  }

  static const char* value(const  ::pteam_p2os::RobotControlRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x2cc72ad6dc716a7dULL;
  static const uint64_t static_value2 = 0x6153d5f2a1e7f7f3ULL;
};

template<class ContainerAllocator>
struct DataType< ::pteam_p2os::RobotControlRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "pteam_p2os/RobotControlRequest";
  }

  static const char* value(const  ::pteam_p2os::RobotControlRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::pteam_p2os::RobotControlRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float32 angular_speed\n\
float32 linear_speed\n\
\n\
";
  }

  static const char* value(const  ::pteam_p2os::RobotControlRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::pteam_p2os::RobotControlRequest_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::pteam_p2os::RobotControlResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::pteam_p2os::RobotControlResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::pteam_p2os::RobotControlResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const  ::pteam_p2os::RobotControlResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::pteam_p2os::RobotControlResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "pteam_p2os/RobotControlResponse";
  }

  static const char* value(const  ::pteam_p2os::RobotControlResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::pteam_p2os::RobotControlResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "\n\
\n\
";
  }

  static const char* value(const  ::pteam_p2os::RobotControlResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::pteam_p2os::RobotControlResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::pteam_p2os::RobotControlRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.angular_speed);
    stream.next(m.linear_speed);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct RobotControlRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::pteam_p2os::RobotControlResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct RobotControlResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<pteam_p2os::RobotControl> {
  static const char* value() 
  {
    return "2cc72ad6dc716a7d6153d5f2a1e7f7f3";
  }

  static const char* value(const pteam_p2os::RobotControl&) { return value(); } 
};

template<>
struct DataType<pteam_p2os::RobotControl> {
  static const char* value() 
  {
    return "pteam_p2os/RobotControl";
  }

  static const char* value(const pteam_p2os::RobotControl&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<pteam_p2os::RobotControlRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "2cc72ad6dc716a7d6153d5f2a1e7f7f3";
  }

  static const char* value(const pteam_p2os::RobotControlRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<pteam_p2os::RobotControlRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "pteam_p2os/RobotControl";
  }

  static const char* value(const pteam_p2os::RobotControlRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<pteam_p2os::RobotControlResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "2cc72ad6dc716a7d6153d5f2a1e7f7f3";
  }

  static const char* value(const pteam_p2os::RobotControlResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<pteam_p2os::RobotControlResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "pteam_p2os/RobotControl";
  }

  static const char* value(const pteam_p2os::RobotControlResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // PTEAM_P2OS_SERVICE_ROBOTCONTROL_H
