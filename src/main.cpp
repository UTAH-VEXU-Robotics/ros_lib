#include "main.h"
#include "ros_lib/api.h"
#include "ros_lib/sensor_msgs/Joy.h"

#include <iostream>

void initialize() {}
void autonomous() {}
void disabled() {}
void competition_initialize() {}

void subCallback(const std_msgs::Bool& isBool){
    //do stuff here
    std::cout << "bool " << isBool.data << "\n";
}

void opcontrol() {
    // debug logging
    // make a node handle object, string message, and publisher for that message.
    ros::NodeHandle  nh;
    std_msgs::String str_msg;
    ros::Publisher chatter("chatter\0", &str_msg);

    // set up rosserial, and prepare to publish the chatter message 
    nh.initNode();
    nh.advertise(chatter);

    // set up a subscriber
    ros::Subscriber<std_msgs::Bool> sub("bool_msgs", &subCallback);
    nh.subscribe(sub);

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
