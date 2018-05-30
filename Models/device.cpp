#include "device.h"
#include <QStandardPaths>
#include <globals.h>

//default constructor
Device::Device()
{

}

//constructor with parameters
Device::Device(QString name, QString location){
    this->name = name;
    this->path = location;
    this->dir.setPath(location);
    this->active = false;

    QDir dir(QString(QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()) + pathDevices + name)); //QString::number(id)

    dir.mkpath(QString(QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()) + pathDevices + name));
}

bool Device::validationCheckExists(QString path){
    if(QDir(QString(QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()) + pathDevices + path)).exists()){
        return true;
    }
    return false;
}

//methods

//getters / setters for properties
void Device::setActive(bool activity){
    this->active = activity;
}

bool Device::getActive(){
    return active;
}

QString Device::getName(){
    return name;
}

QDir Device::getDir(){
    return dir;
}
