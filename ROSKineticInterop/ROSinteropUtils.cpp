#include <ros/ros.h>
#include <rosclientinterop/ROSClientInteropPrototypes.h>
#include "ROSinteropUtils.h"

thread_local uint8_t * msgbuf =NULL ;