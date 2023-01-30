#include "MainApplication.hpp"
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ros::init(argc, argv, "pi");
    MainApplication mainApp;
    return a.exec();
}
