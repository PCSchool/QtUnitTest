#include <QtTest>
#include <QDateTime>
#include <Models/patient.h>
#include <Models/user.h>
#include <Models/device.h>
#include <Models/system.h>
#include <Models/binarypatient.h>
#include <Models/globals.h>
#include <QStandardPaths>

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

    void device_testCase1();
    void device_testCase2();

    void system_testCase1();

private:
    Patient* p1, p2;
    User* u1, u2;
    Device* d1, d2;

    char gender = 'f';
    QString name_, email_, zipcode_, housenr_, street_;
    QString path_, patientDir_, deviceDir_, systemDir_, currentDir_, devicename_, base_;
    QDate date_;
    int id_, phone_;
    double weight_, height_, bmi_;
    QDir thisDir;
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

    // /sleepDemonstrator replaced by 'unitTestingFiles'
    base_ = QString(QString(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()) + "/unitTestingFiles");
    thisDir = QDir(base_);
}

void UnitTesting::cleanupTestCase()
{

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
    //QVERIFY(Patient::validationFormCheck("", controlType::names) == false);

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
    //QVERIFY(Patient::validationFormCheck("", controlType::email) == false);
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

void UnitTesting::device_testCase1(){
    deviceDir_ = "/devicedir/";

    QVERIFY(Device::validationCheckExists(devicename_) == false);
    path_ = base_ + pathDevices;
    thisDir.mkpath(path_);
    d1 = new Device(devicename_, path_);

    QVERIFY(Device::validationCheckExists(devicename_) == true);
}

void UnitTesting::device_testCase2(){
    d1->setActive(true);
    QVERIFY(d1->getActive() == true);
    d1->setActive(false);
    QVERIFY(d1->getActive() == false);

    QVERIFY(d1->getDir().path() == path_);
    QVERIFY(d1->getName() == name_);

}

void UnitTesting::system_testCase1(){

}
QTEST_APPLESS_MAIN(UnitTesting)

#include "tst_unittesting.moc"
