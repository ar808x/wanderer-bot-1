/*****************************************************************************************
 Copyright (C) 2020 Arjun Srinivasan Ambalam,Rajeshwar N.S
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
******************************************************************************************/

/**
 *  @copyright MIT License 2020 Arjun Srinivasan Ambalam,Rajeshwar N.S
 *  @file    Navigatebot.hpp
 *  @author  Arjun Srinivasan Ambalam
 *  @author  Rajeshwar N.S
 *  @date    12/07/2020
 *  @version 1.0
 *
 *  @brief Final Project - wanderer-bot (Search and collect objects)
 *
 *  @section DESCRIPTION
 *  To test Navigation of robot
 */


#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <gtest/gtest.h>
#include "../include/Navigatebot.hpp"


/**
 * @def TEST(TestNavigatebot, testTwistRobot)
 * @brief To check if the robot is able to twist on given topic
 */
TEST(TestNavigatebot, testTwistRobot) {
geometry_msgs::Twist msg;
msg.linear.x = 0.0;
msg.linear.y = 0.0;
msg.linear.z = 0.0;
msg.angular.x = 0.0;
msg.angular.y = 0.0;
msg.angular.z = 0.0;
//  initialise the test object
Navigatebot testN = Navigatebot();

ros::NodeHandle nh;
//  Create a publisher on the topic
ros::Publisher pub =
nh.advertise<geometry_msgs::Twist>
("/cmd_vel", 5);

//  run publisher and check publisher and subscriber
ros::WallDuration(5.0).sleep();
ros::spinOnce();
EXPECT_EQ(0, pub.getNumSubscribers());

//  run subscriber and check publisher and subscriber
ros::Subscriber sub =
nh.subscribe("/cmd_vel", 5,
             &Navigatebot::twistRobot, &testN);

for (int i = 0; i < 10; i++) {
  pub.publish(msg);
  ros::WallDuration(0.1).sleep();
  ros::spinOnce();
}

//  Should return 1 as there is one publisher
EXPECT_EQ(1, sub.getNumPublishers());
//  Should return 1 as there is one subscriber
EXPECT_EQ(1, pub.getNumSubscribers());
}

TEST(TestNavigatebot, testStart) {
    geometry_msgs::Twist msg;
    msg.linear.x = 0.0;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;
    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = 0.0;
    Navigatebot testN = Navigatebot();

    ros::NodeHandle nh;
    ros::Publisher pub =
    nh.advertise<geometry_msgs::Twist>
    ("/cmd_vel", 5, &testN);

    //  run fake publisher and subscriber
    ros::WallDuration(5.0).sleep();
    ros::spinOnce();
    EXPECT_EQ(0, pub.getNumSubscribers());

    int res = 0;
    testN.flag = true;
    EXPECT_EQ(0, testN.start(false));
}

/**
 *  @brief  Main Function for running tests for Navigate Robot Class
 *  @param  int argc, char argv
 *  @return int
 */
int main(int argc, char** argv) {
    ros::init(argc, argv, "testNavigator");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
