#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

// define 3x3 matrix R1~R5
tf::Matrix3x3 R1(0.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
tf::Matrix3x3	R2(0.0, 1.0, 0.0, 0.0, 0.0, -1.0, -1.0, 0.0, 0.0);
tf::Matrix3x3	R3(0.75, -0.2165, 0.625, 0.433, 0.875, -0.2165, -0.5, 0.433, 0.75);
tf::Matrix3x3	R4(0.0, -0.866, 0.5, 0.5, 0.433, 0.75, -0.866, 0.25, 0.433);
tf::Matrix3x3	R5(0.5, -0.1464, 0.8536, 0.5, 0.8536, -0.1464, -0.7071, 0.5, 0.5);

// define 3x1 vector p1~p5
tf::Vector3	p1(-0.3, 0.4, 0.5);
tf::Vector3	p2(0.6, 0.8, 0);
tf::Vector3	p3(0.3, 0.3, 0.3);
tf::Vector3	p4(0.6, 0.4, 0);
tf::Vector3	p5(0.1, 0.2, 0.3);

void broadcastTF(const ros::TimerEvent& timer_event){

  tf::Transform T1, T2, T3, T4, T5, A_B, B_C, C_D, C_E, E_F;
  tf::Quaternion q;

  // T1: B -> A
  // T2: A -> C
  // T3: E -> D
  // T4: C -> D
  // T5: A -> F
  T1.setOrigin(p1); R1.getRotation(q); T1.setRotation(q);
  T2.setOrigin(p2); R2.getRotation(q); T2.setRotation(q);
  T3.setOrigin(p3); R3.getRotation(q); T3.setRotation(q);
  T4.setOrigin(p4); R4.getRotation(q); T4.setRotation(q);
  T5.setOrigin(p5); R5.getRotation(q); T5.setRotation(q);

  // set transform tree form A to F
  A_B = T1.inverse();
  B_C = T1*T2;
  C_D = T4;
  C_E = T4*(T3.inverse());
  E_F = T3*(T4.inverse())*(T2.inverse())*T5;

  static tf::TransformBroadcaster br;
  br.sendTransform(tf::StampedTransform(A_B, ros::Time::now(), "A", "B"));
  br.sendTransform(tf::StampedTransform(B_C, ros::Time::now(), "B", "C"));
  br.sendTransform(tf::StampedTransform(C_D, ros::Time::now(), "C", "D"));
  br.sendTransform(tf::StampedTransform(C_E, ros::Time::now(), "C", "E"));
  br.sendTransform(tf::StampedTransform(E_F, ros::Time::now(), "E", "F"));
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "assignment2_node");
  ros::NodeHandle nh;
  ros::Timer timer = nh.createTimer(ros::Duration(0.5), broadcastTF);
  while (ros::ok()) {ros::spinOnce();} 
  return 0;
}
