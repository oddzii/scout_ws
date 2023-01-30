#include "MainApplication.hpp"
#include <QCoreApplication>


MainApplication::MainApplication(QObject *parent)
    : QObject{parent}
{
    onvif_.init("http://192.168.50.101:8899/onvif/device_service");

    makeNewNode();

    btimer1ms_.start(1, Qt::PreciseTimer, this);
    btimer5s_.start(5000, this);
}

void MainApplication::timerEvent(QTimerEvent *event)
{
    if (btimer1ms_.timerId() == event->timerId()) {
        onvif_.update();

        if (!ros::ok()) { QCoreApplication::exit(0); }
        ros::spinOnce();
    }
    else if (btimer5s_.timerId() == event->timerId()) {
        if (!ros::master::check()) { makeNewNode(); }
    }
    else { QObject::timerEvent(event); }
}

void MainApplication::makeNewNode()
{
    srv_.clear();
    srv_.reserve(6);
    node_ = std::make_unique<ros::NodeHandle>();
    srv_.emplace_back(node_->advertiseService("pi/ContinuousMove", &MainApplication::ContinuousMove, this));
    srv_.emplace_back(node_->advertiseService("pi/Stop", &MainApplication::Stop, this));
    srv_.emplace_back(node_->advertiseService("pi/GotoPreset", &MainApplication::GotoPreset, this));
    srv_.emplace_back(node_->advertiseService("pi/GetPresets", &MainApplication::GetPresets, this));
    srv_.emplace_back(node_->advertiseService("pi/SetPreset", &MainApplication::SetPreset, this));
    srv_.emplace_back(node_->advertiseService("pi/SaveSnapshot", &MainApplication::saveSnapshort, this));
}

bool MainApplication::ContinuousMove(nav_robot_pi::ContinuousMove::Request &req,
                                     nav_robot_pi::ContinuousMove::Response &res)
{
    res.status = onvif_.ptz_.continuousMove(req.panSpeed, req.tiltSpeed, req.zoomSpeed);
    if (req.timeoutMs > 0)
        QTimer::singleShot(req.timeoutMs, this, [&]() { onvif_.ptz_.stop(); });
    return true;
}

bool MainApplication::Stop(nav_robot_pi::Trigger::Request &req, nav_robot_pi::Trigger::Response &res)
{
    (void)req;
    res.status = onvif_.ptz_.stop();
    return true;
}

bool MainApplication::GotoPreset(nav_robot_pi::GotoPreset::Request &req, nav_robot_pi::GotoPreset::Response &res)
{
    res.status = onvif_.ptz_.gotoPreset(std::to_string(req.token), req.panSpeed, req.tiltSpeed, req.zoomSpeed);
    return true;
}

bool MainApplication::GetPresets(nav_robot_pi::GetPresets::Request &req, nav_robot_pi::GetPresets::Response &res)
{
    (void)req;
    const auto presets = onvif_.ptz_.getPresets();
    res.token.reserve(presets.size());
    res.name.reserve(presets.size());
    for (auto preset : presets) {
        res.token.emplace_back(*preset->token);
        res.name.emplace_back(*preset->Name);
    }
    return true;
}

bool MainApplication::SetPreset(nav_robot_pi::SetPreset::Request &req, nav_robot_pi::SetPreset::Response &res)
{
    res.token = onvif_.ptz_.setPreset(std::to_string(req.token).c_str(), req.name.c_str());
    return true;
}

bool MainApplication::saveSnapshort(nav_robot_pi::SaveSnapshot::Request &req, nav_robot_pi::SaveSnapshot::Response &res)
{
    res.status = onvif_.saveSnapshot(std::string("nav_robot_pi/images/") + req.filename);
    return true;
}
