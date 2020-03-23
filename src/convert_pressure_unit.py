#!/usr/bin/python
# We need the line above to run the command 'rosrun ...'
# or it will be confused how to run this file

# Publisher/ Subscriber tutorial
# Editer: Sean Lu
# Last modify: 9/22
# Changelog:
#   Version 1.0

import rospy # ROS Python Client API Library
from std_msgs.msg import Float64 # Message type we use

# Convert hPa to mmHg
# mmHg = 0.75066 * hPa
# Input: pressure in hPa
# Output: pressure in mmHg
def hPa2mmHg(hPa):
        mmHg_ = 0.75066 * hPa
	return mmHg_

# Callback for /sensor/pressure
# Get the pressure in hPa, convert 
# it to mmHg and print the information
def callback(msg):
	hPa = msg.data
	mmHg.data = hPa2mmHg(hPa)
	# Print information and publish
	rospy.loginfo("Pressure: %.2f mmHg", mmHg.data)
	pub.publish(mmHg)
	
# Intialize the node, publisher and subscriber
def main():
	rospy.init_node("convert_temp_unit_node", anonymous = False)
	# Message
	global mmHg
	mmHg = Float64()
	# Publisher
	global pub
	pub = rospy.Publisher("/sensor/pressure_mmHg", Float64, queue_size = 10)
	# Subscriber
	sub = rospy.Subscriber("/sensor/pressure", Float64, callback, queue_size = 10)
	
	rospy.spin()

if __name__ == "__main__":
	main()
