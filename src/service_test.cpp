#include "nav2_costmap_2d/clear_costmap_service.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  rclcpp::Rate r(0.5);
  while(rclcpp::ok()) {
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("clear_costmap_client");
    auto client = node->create_client<nav2_msgs::srv::ClearEntireCostmap>("/global_costmap/clear_entirely_global_costmap");
    auto request = std::make_shared<nav2_msgs::srv::ClearEntireCostmap::Request>();

    for (int i = 0; i < 1; i++) {      
      if (!rclcpp::ok()) {
	RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
	return 0;
      }
      if (client->wait_for_service(5.0s)){
	auto result = client->async_send_request(request);
	// Wait for the result.
	if (rclcpp::spin_until_future_complete(node, result, 5.0s) ==
	    rclcpp::executor::FutureReturnCode::SUCCESS)
	{
	  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "%d Successed", i);
	} else {
	  RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "%d Failed", i);
	}
      } else {
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "%d service not available.", i);
      }
      
    }
    r.sleep();
    
  }

  rclcpp::shutdown();
  return 0;
}
