#include "system.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <stdlib.h>

using namespace std;

System::System()
{
    hasDevice = false;
    hasPatient = false;
    hasDir = false;

    QString path = QString(QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()) + pathBase);
    QDir makedir(path);
    if(!makedir.exists()){
        makedir.mkpath(path);
        makedir.mkpath(path+ "/devices/");
        makedir.mkpath(path + "/patients/");
    }
    this->setDir(path);
    this->setPatientDir(QDir(path + "/patients/"));
}

//methods
void System::addDevice(Device device){
    devices << device;
}

void System::removeDevice(Device device){
    QLinkedList<Device>::iterator i;
    for (i = devices.begin(); i != devices.end(); i++){}

}

QLinkedList<Device> System::getDevices(){
    return this->devices;
}

//getters / setters voor properties
void System::setPatientDir(QDir dir){
    this->patientDir  = dir;
}

QDir System::getPatientDir(){
    return this->patientDir;
}

QDir System::getDir(){
    return dir;
}
void System::setDir(const QString path){
    this->dir.setPath(path);
    hasDir = true;
}

Patient* System::getPatient(){
    return selectedPatient;
}
void System::setPatient(Patient* patient){
    selectedPatient = patient;
    hasPatient = true;
}

Device System::getDevice(){
    return selectedDevice;
}

void System::setDevice(Device device){
    selectedDevice = device;
    hasDevice = true;
}

void System::removePatient(QString path){
    QDir removeDir(path);
    if(hasPatient){
        if(selectedPatient->userDir.path() != path){
            removeDir.removeRecursively();
        }else{
            std::cout << endl << "Error: cant remove current active patient.";
        }
    }else{
        removeDir.removeRecursively();
    }
}
