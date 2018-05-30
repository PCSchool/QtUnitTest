#ifndef PATIENT_H
#define PATIENT_H

#include <models/user.h>
#include <QDir>
#include <QFile>
#include <globals.h>
//#include <models/recording.h>
#include <vector>


class Patient : public User
{
public:
    //constructor
    Patient();
    Patient(bool exist, int id, QString email, char gender, QString street, QString housenr, QString zipcode, int homePhone, QString name, QDate date, double weight, double height);

    //methods
    void changeProfile(QString newInfo, QString variable);
    void writeToNote(QString addToNote);
    bool writeProfileToBinary();

    //enum controlType{email, number, names, zipcodes, phone, housenr};
    static bool validationFormCheck(QString control, controlType type);

    QString pathNotes;
    QString pathPersonalInfo;
    QDir userDir;
    QDir recordingDir;

    //getters / setters
    bool getPresent();
    void setPresent(bool present);
    double getWeight();
    double getHeight();
    double getBMI();
    QString getPathNotes();
    QString getPathPersonalInfo();
    QDir getUserDir();
    QDir getRecordingDir();

private:
    //methods
    void calculateBMI(double weight, double height);
    bool createDirectory();
    void addRecording();

    //fields
    double weight;
    double height;
    double bmi;
    QDir directory;
    bool present;

signals:
    emptyFormError(QString error);
};

#endif // PATIENT_H
