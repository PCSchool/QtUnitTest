#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <models/patient.h>
#include <models/device.h>
#include <models/user.h>
#include <vector>
#include <QLinkedList>

class System
{
public:
    //constructor
    System();
    Patient *selectedPatient;

    //methods
    bool hasPatient;  //returns true if a patient is selected, false otherwise
    bool hasDevice;   //return true if a device is selected, false otherwise
    bool hasDir;      //return true if a directory is selected, false otherwise

    void addDevice(Device device);
    QLinkedList<Device> getDevices();
    void removeDevice(Device device);

    //getters / setters for properties
    QDir getDir();
    void setDir(QString path);
    Patient* getPatient();
    void setPatient(Patient* patient);
    Device getDevice();
    void setDevice(const Device device);
    QDir getPatientDir();
    void setPatientDir(QDir dir);



public slots:
    void removePatient(QString path);
signals:

private:
    //fields
    QDir dir;  // base directory of the sleep signal demonstrator
    QDir patientDir;
    User user;
    QLinkedList<Device> devices;
    Device selectedDevice;
};

#endif // SYSTEM_H
