# Sensing and Intelligent Systems : LAB1
1. publisher and subscriber practice in ROS
2. transformation matrix practice in rviz

## Publisher and Subscriber
```
$ git clone https://github.com/ChengChengYang1997/ros_topic_practice.git
$ cd ros_topic_practice/bag/
$ roscore
$ rosbag play temp_pressure_2018-09-21-01-05-38.bag -l
$ rosrun ros_toc_practice convert_pressure_unit.py
```

## Transformation matrix
```
$ git clone https://github.com/ChengChengYang1997/ros_topic_practice.git
$ cd ros_topic_practice/rviz/
$ roscore
$ rosrun ros_topic_practice transform
$ rviz -d tf.rviz
$ rosrun tf tf_echo /B /F
```
