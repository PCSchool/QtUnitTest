#ifndef DEVICE_H
#define DEVICE_H

#include <QDir>

class Device
{
public:
    //constructors
    Device();
    Device(QString name, QString location);

    //methods
    static bool validationCheckExists(QString path);

    //getters / setters
    void setActive(bool activity);
    bool getActive();
    QString getName();
    QDir getDir();

private:
    //methods

    //fields
    QString name;
    QString path;
    bool active;
    QDir dir;

};
#endif // DEVICE_H

