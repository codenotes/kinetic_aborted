;; Auto-generated. Do not edit!


(when (boundp 'geometry_msgs::Pose2D)
  (if (not (find-package "GEOMETRY_MSGS"))
    (make-package "GEOMETRY_MSGS"))
  (shadow 'Pose2D (find-package "GEOMETRY_MSGS")))
(unless (find-package "GEOMETRY_MSGS::POSE2D")
  (make-package "GEOMETRY_MSGS::POSE2D"))

(in-package "ROS")
;;//! \htmlinclude Pose2D.msg.html


(defclass geometry_msgs::Pose2D
  :super ros::object
  :slots (_x _y _theta ))

(defmethod geometry_msgs::Pose2D
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:theta __theta) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _theta (float __theta))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:serialization-length
   ()
   (+
    ;; float64 _x
    8
    ;; float64 _y
    8
    ;; float64 _theta
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x
       (sys::poke _x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y
       (sys::poke _y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x
     (setq _x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y
     (setq _y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _theta
     (setq _theta (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get geometry_msgs::Pose2D :md5sum-) "938fa65709584ad8e77d238529be13b8")
(setf (get geometry_msgs::Pose2D :datatype-) "geometry_msgs/Pose2D")
(setf (get geometry_msgs::Pose2D :definition-)
      "# This expresses a position and orientation on a 2D manifold.

float64 x
float64 y
float64 theta
")



(provide :geometry_msgs/Pose2D "938fa65709584ad8e77d238529be13b8")


