#ifndef WEB_VIDEO_SERVER_H_
#define WEB_VIDEO_SERVER_H_

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <vector>
#include "web_video_server/image_streamer.h"
#include "async_web_server_cpp/http_server.hpp"
#include "async_web_server_cpp/http_request.hpp"
#include "async_web_server_cpp/http_connection.hpp"

#define ROS_HAS_STEADYTIMER (ROS_VERSION_MINIMUM(1, 13, 1) || ((ROS_VERSION_MINOR == 12) && (ROS_VERSION_PATCH >= 8)))

namespace web_video_server
{

/**
 * @class WebVideoServer
 * @brief
 */
class WebVideoServer
{
public:
  /**
   * @brief  Constructor
   * @return
   */
  WebVideoServer(ros::NodeHandle &nh, ros::NodeHandle &private_nh);

  /**
   * @brief  Destructor - Cleans up
   */
  virtual ~WebVideoServer();

  /**
   * @brief  Starts the server and spins
   */
  void spin();

  bool handle_stream(const async_web_server_cpp::HttpRequest &request,
                     async_web_server_cpp::HttpConnectionPtr connection, const char* begin, const char* end);

  bool handle_stream_viewer(const async_web_server_cpp::HttpRequest &request,
                            async_web_server_cpp::HttpConnectionPtr connection, const char* begin, const char* end);

  bool handle_snapshot(const async_web_server_cpp::HttpRequest &request,
                       async_web_server_cpp::HttpConnectionPtr connection, const char* begin, const char* end);

  bool handle_list_streams(const async_web_server_cpp::HttpRequest &request,
                           async_web_server_cpp::HttpConnectionPtr connection, const char* begin, const char* end);

private:
  void restreamFrames(std::chrono::duration<double> max_age);
  void cleanup_inactive_streams();

  ros::NodeHandle nh_;
#if ROS_HAS_STEADYTIMER || defined USE_STEADY_TIMER
  ros::SteadyTimer cleanup_timer_;
#else
  ros::Timer cleanup_timer_;
#endif
  int ros_threads_;
  double publish_rate_;
  int port_;
  std::string address_;
  boost::shared_ptr<async_web_server_cpp::HttpServer> server_;
  async_web_server_cpp::HttpRequestHandlerGroup handler_group_;

  std::vector<boost::shared_ptr<ImageStreamer> > image_subscribers_;
  std::map<std::string, boost::shared_ptr<ImageStreamerType> > stream_types_;
  boost::mutex subscriber_mutex_;
};

}

#endif
