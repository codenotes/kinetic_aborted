
#after loading msg_gen, try this styff
#working python
#>>> roslib.packages.get_pkg_dir('std_msgs')
#u'/opt/ros/kinetic/share/std_msgs'

#important environs
#ROS_ROOT=/opt/ros/kinetic/share/ros
#ROS_PACKAGE_PATH=/opt/ros/kinetic/share
#ROS_MASTER_URI=http://localhost:11311



roslib.msgs.set_verbose(True)
generate("C:\\ros\\kintetic\\ROSPyTesting\\gregtestmsg.msg")
