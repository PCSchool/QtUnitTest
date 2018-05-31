#include <QtTest>
#include <QDateTime>
#include <Models/patient.h>
#include <Models/user.h>
#include <Models/device.h>
#include <Models/system.h>
#include <Models/binarypatient.h>
#include <Models/globals.h>
#include <QStandardPaths>
#include <Exceptions/exceptionemptyform.h>
#include <Exceptions/exceptioninvalidenumtype.h>
#include <Exceptions/exceptioninvalidconstructor.h>
#include <Exceptions/exceptioninvalidparameters.h>
#include <Models/recording.h>
#include <Models/analysis.h>
#include <Models/graph.h>
#include <Models/exporting.h>

// add necessary includes here

class UnitTesting : public QObject
{
    Q_OBJECT

public:
    UnitTesting();
    ~UnitTesting();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void user_testCase1();
    void user_testCase2();

    void patient_testCase1();
    void patient_testCase2();
    void patient_testCase3();
    void patient_testCase4();
    void patient_testCase5();
    void patient_testCase6();
    void patient_testCase7();

    void device_testCase1();
    void device_testCase2();

    void system_testCase1();
    void system_testCase2();

    void recording_testCase1();
    void recording_testCase2(double freq, double amplitude, int yAxisMin, int yAxisMax, int xAxisMin, int xAxisMax, int interval, QString typeString, QString sensorString);

    void analysis_testCase1();
    void analysis_testCase2();

    void graph_testCase1();
    void graph_testCase2();

    void exporting_testCase1();
    void exporting_testCase2();

    void Exception_testCase2();
    void Exception_testCase1();

private:
    Patient* p1, p2;
    User* u1, u2;
    Device* d1, d2;
    System* s1;
    Recording* r1;
    Analysis* a1;
    Graph* g1;
    Exporting* e1;


    char gender = 'f';
    QString name_, email_, zipcode_, housenr_, street_, fileRecordingPath_, fileRecordingDir_;
    QString path_, patientDir_, deviceDir_, systemDir_, currentDir_, devicename_, base_, exportname_;
    QDate date_;
    int id_, phone_, count_;
    double weight_, height_, bmi_;
    QDir thisDir;
    QList<TimePointer> tpList;

};

UnitTesting::UnitTesting()
{
    initTestCase();

    user_testCase1();
    user_testCase2();

    patient_testCase1();
    patient_testCase2();
    patient_testCase3();
    patient_testCase4();
    patient_testCase5();
    patient_testCase6();
    patient_testCase7();

    //recording_testCase1();
    //recording_testCase2();

    //analysis_testCase1();
    //analysis_testCase2();
}

UnitTesting::~UnitTesting()
{

}

void UnitTesting::initTestCase()
{
    name_ = "John K";
    email_ = "JohnK@email.com";
    street_ = "Herenlaan";
    housenr_ = "12a";
    zipcode_ = "1682JK";
    date_ = QDate::currentDate();
    id_ = 12;
    weight_ = 87.5;
    height_ = 187.2;
    phone_ = 122313112;
    bmi_ = weight_ / ((height_/100) * (height_/100));
    devicename_ = "onera_01";
    exportname_ = "onera_100";

    // /sleepDemonstrator replaced by 'unitTestingFiles'
    base_ = QString(QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()) + "/unitTestingFiles");
    thisDir = QDir(base_);

    // special recording file
     fileRecordingPath_ = "recording_0.bin";
     fileRecordingDir_ = QDir::currentPath() + "/recording";
}

void UnitTesting::cleanupTestCase()
{
    QString notremove = (QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()));
    if(thisDir.path() != notremove){
        thisDir.removeRecursively();
    }
}

void UnitTesting::user_testCase1(){

}

void UnitTesting::user_testCase2(){

}

void UnitTesting::patient_testCase1(){
    QVERIFY(Patient::validationFormCheck("Jan Klaassen!", controlType::names) == false);
    QVERIFY(Patient::validationFormCheck("Jan Klaa&#ssen", controlType::names) == false);
    QVERIFY(Patient::validationFormCheck("Jan Klaa__ssen!", controlType::names) == false);
    QVERIFY(Patient::validationFormCheck("Jan Klaassen12", controlType::names) == false);

    QVERIFY(Patient::validationFormCheck("Jan Klaassen", controlType::names) == true);
    QVERIFY(Patient::validationFormCheck(name_, controlType::names) == true);

    QVERIFY(Patient::validationFormCheck("Hendriklaan!@", controlType::names) == false);
    QVERIFY(Patient::validationFormCheck("Hendriklaan!", controlType::names) == false);
    QVERIFY(Patient::validationFormCheck("Hendrik55laan", controlType::names) == false);
    QVERIFY(Patient::validationFormCheck("Hendriklaan101", controlType::names) == false);

    QVERIFY(Patient::validationFormCheck("Hendriklaan", controlType::names) == true);
    QVERIFY(Patient::validationFormCheck(street_, controlType::names) == true);
}

void UnitTesting::patient_testCase2(){
    QVERIFY(Patient::validationFormCheck("JKSpider@email.com ~", controlType::email) == false);
    QVERIFY(Patient::validationFormCheck("JKSpider@emailcom", controlType::email) == false);
    QVERIFY(Patient::validationFormCheck("JKSpideremail.com", controlType::email) == false);
    QVERIFY(Patient::validationFormCheck("JKSpideremailco,", controlType::email) == false);
    QVERIFY(Patient::validationFormCheck("JKSpider@@email.com", controlType::email) == false);
    QVERIFY(Patient::validationFormCheck("JKSpider@email@!@#!com", controlType::email) == false);
    QVERIFY(Patient::validationFormCheck("JKSpider123email.com", controlType::email) == false);

    QVERIFY(Patient::validationFormCheck("JKSpider@email.com", controlType::email) == true);
    QVERIFY(Patient::validationFormCheck(email_, controlType::email) == true);
}

void UnitTesting::patient_testCase3(){
    QVERIFY(Patient::validationFormCheck("AAAAAA", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("121212", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("AAAAA1", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("A21212", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("12AAAA", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("JKO212", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("12AAPA", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("1@#JKLM", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("JKLAPM89", controlType::zipcodes) == false);
    QVERIFY(Patient::validationFormCheck("JKO31", controlType::zipcodes) == false);

    QVERIFY(Patient::validationFormCheck("2819JA", controlType::zipcodes) == true);
    QVERIFY(Patient::validationFormCheck(zipcode_, controlType::zipcodes) == true);
}

void UnitTesting::patient_testCase4(){
    QVERIFY(Patient::validationFormCheck("1231238888!", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck("123-1231211", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck("1231abc1231", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck("1_!231adke3", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck("0471231233)", controlType::number) == false);

    QVERIFY(Patient::validationFormCheck("06421891239", controlType::number) == true);
    QVERIFY(Patient::validationFormCheck(QString::number(phone_), controlType::number) == true);
}

void UnitTesting::patient_testCase5(){
    QVERIFY(Patient::validationFormCheck("11000zz", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck("abc1", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck("a112", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck("11000#^", controlType::number) == false);

    QVERIFY(Patient::validationFormCheck("11000z", controlType::number) == false);
    QVERIFY(Patient::validationFormCheck(housenr_, controlType::number) == false);
}

void UnitTesting::patient_testCase6(){
    p1 = new Patient(false, id_, email_, 'f', street_, housenr_, zipcode_, phone_, name_, date_, weight_, height_);

    QVERIFY(p1->getId() == id_);
    QVERIFY(p1->getEmail() == email_);

    QVERIFY(p1->getGender() == "female");
    QVERIFY(p1->getStreet() == street_);
    QVERIFY(p1->getHousenr() == housenr_);
    QVERIFY(p1->getZipcode() == zipcode_);
    QVERIFY(p1->getHomePhone() == phone_);
    QVERIFY(p1->getName() == name_);
    QVERIFY(p1->getBirthDate() == date_);
    QVERIFY(p1->getHeight() == height_);
    QVERIFY(p1->getWeight() == weight_);
    QVERIFY(p1->getBMI() == bmi_);

    p1 = new Patient(false, id_, email_, 'm', street_, housenr_, zipcode_, phone_, name_, date_, weight_, height_ );
    QVERIFY(p1->getGender() == "male");
    p1 = new Patient(false, id_, email_, 'o', street_, housenr_, zipcode_, phone_, name_, date_, weight_, height_ );
    QVERIFY(p1->getGender() == "unknown");
}

void UnitTesting::patient_testCase7(){
    try{
        QVERIFY(Patient::validationFormCheck("", controlType::names) == false);
    }catch(ExceptionEmptyForm &e){

    }
}

void UnitTesting::device_testCase1(){
    deviceDir_ = "/devicedir/";

    QVERIFY(Device::validationCheckExists(devicename_) == false);
    path_ = base_ + pathDevices;
    thisDir.mkpath(path_);
    d1 = new Device(devicename_, path_);

    QVERIFY(Device::validationCheckExists(devicename_) == true);
}

void UnitTesting::device_testCase2(){
    d1 = new Device(devicename_, path_);
    d1->setActive(true);
    QVERIFY(d1->getActive() == true);
    d1->setActive(false);
    QVERIFY(d1->getActive() == false);

    QVERIFY(d1->getDir().path()+"/" == path_);
    QVERIFY(d1->getName() == devicename_);

    QString notremove = (QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()));
    if(thisDir.path() != notremove){
        thisDir.removeRecursively();
    }
}

void UnitTesting::system_testCase1(){
    QString path = base_;
    bool check = QDir(base_).exists();
    QVERIFY(base_ == false);

    s1 = new System();

    check = QDir(path).exists();
    QVERIFY(check == true);
}

void UnitTesting::system_testCase2(){

    QVERIFY(s1->hasDevice == false);
    QVERIFY(s1->hasPatient == false);

    s1->addDevice(*d1);
    s1->setDevice(*d1);
    s1->setPatient(p1);
    s1->setPatientDir(thisDir);
    s1->setDir(thisDir.path());

    QVERIFY(s1->getDevice().getName() == d1->getName());
    QVERIFY(s1->getDir().path() == thisDir.path());
    QVERIFY(s1->getPatient()->getName() == p1->getName());
    QVERIFY(s1->getPatientDir().path() == thisDir.path());
    QVERIFY(s1->getDevices().count() == 1);
}

void UnitTesting::recording_testCase1(){
    double freq = 10.0;
    double amplitude = 10.9;
    int yAxisMin = 0;
    int yAXisMax = 15;
    int xAxisMin = -10;
    int xAxisMax = 20;
    int interval = 22;
    Recording::Sensors sensor = Recording::Sensors::microphone;
    Recording::Types type = Recording::Types::scatter;
    QString sensorString = r1->convertSensor(sensor);
    QString typeString = r1->convertGraphType(type);

    r1 = new Recording();

    r1 = new Recording(500, 500, 40, 10);

    //test enum Sensors{heartrate = 0, accelerometer, microphone, skintemperature, lightsensor, invalidsensor};
    sensor = Recording::Sensors::accelerometer;
    sensorString = r1->convertSensor(sensor);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    sensor = Recording::Sensors::heartrate;
    sensorString = r1->convertSensor(sensor);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    sensor = Recording::Sensors::microphone;
    sensorString = r1->convertSensor(sensor);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    sensor = Recording::Sensors::skintemperature;
    sensorString = r1->convertSensor(sensor);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    sensor = Recording::Sensors::lightsensor;
    sensorString = r1->convertSensor(sensor);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    //enum Types{line = 0, bar, histogram, scatter, invalidtype};
    type = Recording::Types::line;
    typeString = r1->convertGraphType(type);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    type = Recording::Types::bar;
    typeString = r1->convertGraphType(type);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    type = Recording::Types::histogram;
    typeString = r1->convertGraphType(type);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    type = Recording::Types::scatter;
    typeString = r1->convertGraphType(type);
    recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);

    // invalid enum types
    QVERIFY_EXCEPTION_THROWN(sensor = Recording::Sensors::invalidsensor;
            sensorString = r1->convertSensor(sensor);
            recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString)
        , ExceptionInvalidEnumType);

    QVERIFY_EXCEPTION_THROWN(type = Recording::Types::invalidtype;
            typeString = r1->convertGraphType(type);
            recording_testCase2(freq, amplitude, yAXisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString), ExceptionInvalidEnumType);

}

void UnitTesting::recording_testCase2(double freq, double amplitude, int yAxisMin, int yAxisMax, int xAxisMin, int xAxisMax, int interval, QString typeString, QString sensorString){
    r1->setProperties(freq, amplitude, yAxisMax, yAxisMin, xAxisMax, xAxisMin, interval, typeString, sensorString);
    QVERIFY(r1->getAmplitude() == amplitude);
    QVERIFY(r1->getFrequency() == freq);
    QVERIFY(r1->getGraphType() == typeString);
    QVERIFY(r1->getSensor() == sensorString);
    QVERIFY(r1->getInterval() == interval);
    QVERIFY(r1->getXAxisMax() == xAxisMax);
    QVERIFY(r1->getXAxisMin() == xAxisMin);
    QVERIFY(r1->getYAxisMax() == yAxisMax);
    QVERIFY(r1->getYAxisMin() == yAxisMin);
}

void UnitTesting::analysis_testCase1(){
    a1 = new Analysis();
    QVERIFY(a1 != NULL);

    //if recording file cant be found, skip this test for it needs the recording file to function !
    if(!fileRecordingPath_.isEmpty()){
        QFile file(fileRecordingPath_);
        fileRecordingPath_ = QDir::currentPath() + "/" + fileRecordingPath_;
        QVector<TimePointer> vector = a1->readFile(fileRecordingPath_);

        for(int i = 0; i < vector.count(); i++){
            vector[i].x;
            vector[i].y;
            TimePointer tp;
            tp.x = vector[i].x;
            tp.y = vector[i].y;
            tpList.append(tp);
        }
        count_ = vector.count();
    }
}

void UnitTesting::analysis_testCase2(){
    a1 = new Analysis();
    QVERIFY(a1 != NULL);

    int countFile = count_;

    //if recording file cant be found, skip this test for it needs the recording file to function !
    if(!fileRecordingPath_.isEmpty()){
        QVector<TimePointer> vector = a1->readFile(fileRecordingDir_);

        for(int i = 0; i < vector.count(); i++){
            vector[i].x;
            vector[i].y;
            TimePointer tp;
            tp.x = vector[i].x;
            tp.y = vector[i].y;
            tpList.append(tp);
        }
    }

    QVERIFY(countFile == count_);
}

void UnitTesting::graph_testCase1(){
    g1 = new Graph();
    TimePointer tp;

    QVERIFY(g1->getVector().count() == 0);
    double y, x;
    for(x = 0; x < 5; x++){
        y = x + 1;
        tp.x = x;
        tp.y = y;
        g1->addPoints(tp);
    }
    QVERIFY(g1->getVector().count() == 5);

    for(x = 0; x < 21; x++){
        y = x + 1;
        tp.x = x;
        tp.y = y;
        g1->addPoints(tp);
    }
    QVERIFY(g1->getVector().count() == 26);

    g1->resetVector();
    QVERIFY(g1->getVector().count() == 0);

    QVector<TimePointer> vectorNew;
    for(x = 0; x < 7; x++){
        y = x + 1;
        tp.x = x;
        tp.y = y;
        vectorNew.append(tp);
    }

    QVERIFY(g1->getVector().count() == 0);
    QVERIFY(vectorNew.count() == 7);
    g1->newVector(vectorNew);
    QVERIFY(g1->getVector().count() == 7);

}

void UnitTesting::graph_testCase2(){
    QVector<TimePointer> vector;
    TimePointer tp;

    QVERIFY_EXCEPTION_THROWN(g1->addToVector(vector), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(g1->newVector(vector), ExceptionInvalidParameters);
}

void UnitTesting::exporting_testCase1(){
    e1 = new Exporting();
    QDir dir(QDir);
    e1->setExportDir(thisDir);
    e1->setObjectName(exportname_);
    e1->setUserDir(thisDir);

    QVERIFY(e1->getUserDir().path() == thisDir.path());
    QVERIFY(e1->getExportDir().path() == thisDir.path());
}

void UnitTesting::exporting_testCase2(){
    QVERIFY_EXCEPTION_THROWN(e1->cleanUserDir("", "C:/Documents"), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(e1->cleanUserDir("C:/Documents", ""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(e1->setObjectName(""), ExceptionEmptyForm);
}

void UnitTesting::Exception_testCase1(){
    QDir ddir("");
    //analysis
    QVERIFY_EXCEPTION_THROWN(a1->readFile(""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(a1->readDir(""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(a1->addRecordingDirList(""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(a1->setRecordingFilePath(""), ExceptionInvalidParameters);

    //device
    QVERIFY_EXCEPTION_THROWN(Device(devicename_, ""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Device("", "/documents/"), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Device::validationCheckExists(""), ExceptionInvalidParameters);

    //exporting
    QVERIFY_EXCEPTION_THROWN(e1->cleanExportDir("", "path"), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(e1->cleanExportDir("dir", ""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(e1->setExportDir(ddir), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(e1->setUserDir(ddir), ExceptionInvalidParameters);


    //graph
    QVector<TimePointer> vector;
    QVERIFY_EXCEPTION_THROWN(g1->newVector(vector), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(g1->addToVector(vector), ExceptionInvalidParameters);

    //patient
    QVERIFY_EXCEPTION_THROWN(p1->writeToNote(""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, -10, email_, gender, street_, housenr_, zipcode_, phone_, name_, date_, weight_, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, "", gender, street_, housenr_, zipcode_, phone_, name_, date_, weight_, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, email_, gender, "", housenr_, zipcode_, phone_, name_, date_, weight_, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, email_, gender, street_, "", zipcode_, phone_, name_, date_, weight_, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, email_, gender, street_, housenr_, "", phone_, name_, date_, weight_, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, email_, gender, street_, housenr_, zipcode_, -10, name_, date_, weight_, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, email_, gender, street_, housenr_, zipcode_, phone_, "", date_, weight_, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, email_, gender, street_, housenr_, zipcode_, phone_, name_, date_, -10, height_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Patient(false, id_, email_, gender, street_, housenr_, zipcode_, phone_, name_, date_, weight_, -10), ExceptionInvalidParameters);

    //recording
    QVERIFY_EXCEPTION_THROWN(r1->changeSize(-10, 10), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(r1->changeSize(10, -10), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Recording(-10, 10, 10, 10), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Recording(10, -10, 10, 10), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Recording(10, 10, -10, 10), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(Recording(10, 10, 10, -10), ExceptionInvalidParameters);

    //system
    QVERIFY_EXCEPTION_THROWN(s1->removePatient(""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(s1->setDir(""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(s1->setPatientDir(ddir), ExceptionInvalidParameters);

    //user
    QVERIFY_EXCEPTION_THROWN(User(12, ""), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(-10, "email"), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(-10, email_, gender, street_, housenr_, zipcode_, phone_, name_, date_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(id_, "", gender, street_, housenr_, zipcode_, phone_, name_, date_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(id_, email_, gender, "", housenr_, zipcode_, phone_, name_, date_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(id_, email_, gender, street_, "", zipcode_, phone_, name_, date_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(id_, email_, gender, street_, housenr_, "", phone_, name_, date_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(id_, email_, gender, street_, housenr_, zipcode_, -10123123123, name_, date_), ExceptionInvalidParameters);
    QVERIFY_EXCEPTION_THROWN(User(id_, email_, gender, street_, housenr_, zipcode_, phone_, "", date_), ExceptionInvalidParameters);
}

void UnitTesting::Exception_testCase2(){

}

QTEST_APPLESS_MAIN(UnitTesting)

#include "tst_unittesting.moc"
