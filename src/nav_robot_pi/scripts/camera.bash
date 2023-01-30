#!/bin/bash
rosservice call /pi/ContinuousMove -- 1 0 1 1000 
rosservice call /pi/ContinuousMove -- 0 -1 1 1000 

