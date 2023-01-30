#pragma once

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QTimer>
#include <sstream>

#include "ros/ros.h"
#include "nav_robot_pi/Trigger.h"
#include "nav_robot_pi/ContinuousMove.h"
#include "nav_robot_pi/GotoPreset.h"
#include "nav_robot_pi/GetPresets.h"
#include "nav_robot_pi/SetPreset.h"
#include "nav_robot_pi/SaveSnapshot.h"

#include "JOnvif.hpp"

class MainApplication : public QObject
{
public:
    explicit MainApplication(QObject *parent = nullptr);

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;

private:
    //! @brief Make ros node
    void makeNewNode();

    // ROS service callback functions ------------------------------------------
    bool ContinuousMove(nav_robot_pi::ContinuousMove::Request &req,
                        nav_robot_pi::ContinuousMove::Response &res);

    bool Stop(nav_robot_pi::Trigger::Request &req,
              nav_robot_pi::Trigger::Response &res);

    bool GotoPreset(nav_robot_pi::GotoPreset::Request &req,
                    nav_robot_pi::GotoPreset::Response &res);

    bool GetPresets(nav_robot_pi::GetPresets::Request &req,
                    nav_robot_pi::GetPresets::Response &res);

    bool SetPreset(nav_robot_pi::SetPreset::Request &req,
                   nav_robot_pi::SetPreset::Response &res);

    bool saveSnapshort(nav_robot_pi::SaveSnapshot::Request &req,
                       nav_robot_pi::SaveSnapshot::Response &res);
    // ROS service callback functions ------------------------------------------

    // Tiemr
    QBasicTimer btimer1ms_, btimer5s_;

    // ROS
    std::unique_ptr<ros::NodeHandle> node_; //!< node handle
    std::vector<ros::ServiceServer> srv_;   //!< service

    JOnvif onvif_;  //!< Onvif
};
