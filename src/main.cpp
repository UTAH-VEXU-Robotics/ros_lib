#include "main.h"
#include "ros_lib/rosserial_vex_v5/examples/helloworld.h"

#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/String.h"

void initialize() {}
void autonomous() {}
void disabled() {}
void competition_initialize() {}

void opcontrol() {
    // debug logging
    // make a node handle object, string message, and publisher for that message.
    ros::NodeHandle  nh;
    std_msgs::String str_msg;
    ros::Publisher chatter("chatter\0", &str_msg);

    // set up rosserial, and prepare to publish the chatter message 
    nh.initNode();
    nh.advertise(chatter);

    // message data variable.
    char* msg = (char*) malloc(20 * sizeof(char));

    while (true) {
    	// send a message about the time!
    	sprintf(msg, "[%d] Hello there!!", (int) pros::c::millis());
		str_msg.data = msg;
		chatter.publish( &str_msg );
		nh.spinOnce();
		delay(20);
    }
}
