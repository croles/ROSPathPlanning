#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h" //Odometry data

//marker
visualization_msgs::Marker marker;

//Marker publisher
ros::Publisher marker_pub;

const float pickPosX = 4.0;
const float pickPosY = 0.75;
const float dropPosX = 11.0;
const float dropPosY = -1.5;
const float pickMargin = 0.3;
const float dropMargin = 0.4;


// The odom_callback function will be called each time a odom data is received
void odom_callback(const nav_msgs::Odometry::ConstPtr& odom_msg)
{
	ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", odom_msg->pose.pose.position.x, odom_msg->pose.pose.position.y, odom_msg->pose.pose.position.z);

	// DELETE marker in pickup
	if (odom_msg->pose.pose.position.x>= pickPosX - pickMargin && odom_msg->pose.pose.position.x<= pickPosX + pickMargin
		&& odom_msg->pose.pose.position.y>= pickPosY - pickMargin && odom_msg->pose.pose.position.y<= pickPosY + pickMargin)
	{
		marker.action = visualization_msgs::Marker::DELETE;
		marker_pub.publish(marker);
	}

	//show the marker in drop off zone
	if (odom_msg->pose.pose.position.x>= dropPosX - dropMargin && odom_msg->pose.pose.position.x<= dropPosX + dropMargin
		&& odom_msg->pose.pose.position.y>= dropPosY - dropMargin && odom_msg->pose.pose.position.y<= dropPosY + dropMargin)
	{
		marker.action = visualization_msgs::Marker::ADD;
		marker.pose.position.x = dropPosX;
    	marker.pose.position.y = dropPosY;
		marker_pub.publish(marker); 
		ROS_INFO("Marker published in drop off");
	}
}


int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers");
	ros::NodeHandle n;
	ros::Rate r(1);

	//Marker publisher creation
	marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	//Odom suscriber
	ros::Subscriber odom_subscriber = n.subscribe("odom", 1000, odom_callback);

	// Set our initial shape type to be a sphere
	uint32_t shape = visualization_msgs::Marker::SPHERE;

    
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickPosX;
    marker.pose.position.y = pickPosY;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker); //show the marker in pick up zone
	ROS_INFO("Marker published");
	
	ros::spin();
}
