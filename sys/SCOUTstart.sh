#!/bin/bash
export DISPLAY=:0.0
source /opt/ros/noetic/setup.bash
source ~/scout_ws/devel/setup.bash
echo $(date -d "+1 minute" +%H,%M) > /home/mclab/scout_ws/sys/times.csv
read taskstatus < /home/mclab/scout_ws/sys/Taskstatus.txt
if [ "$taskstatus" == "0" ]; then
  echo "1" > /home/mclab/scout_ws/sys/Taskstatus.txt
  cd scout_ws
  echo "gui run"+" " +$(date +%H:%M:%S) >> testgui.txt
  /home/mclab/scout_ws/devel/lib/scout_gui/scout_gui
else
  echo "Previous Task is running"
fi
