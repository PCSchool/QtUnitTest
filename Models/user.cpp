#include "user.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <QDir>
#include <QStandardPaths>
#include <Exceptions/exceptioninvalidparameters.h>

//constructor 1 default
User::User(){
}

//constructor 2
User::User(int id, QString email){
    if(email.isEmpty()){throw ExceptionInvalidParameters();}
    if(id < 0){throw ExceptionInvalidParameters();}
    this->id = id;
    this->email = email;
}

//constructor 3
User::User(int id, QString email, char gender, QString street, QString housenr, QString zipcode, int homePhone, QString name, QDate date){
    if(id < 0 || homePhone < 0){
        throw ExceptionInvalidParameters();
    }
    if(email.isEmpty() || street.isEmpty() || housenr.isEmpty() || zipcode.isEmpty() || name.isEmpty()){
        throw ExceptionInvalidParameters();
    }
    this->id = id;
    this->name = name;
    this->gender = gender;
    this->street = street;
    this->housenr = housenr;
    this->zipcode = zipcode;
    this->homePhone = homePhone;
    this->email = email;
    this->date = date;
}

//getters / setters for properties
int User::getId() {
    return id;
}

QString User::getName() {
    return name;
}
QString User::getGender(){
    //possible genders: m = male, f = female, o = unknown
    QString returnthis = "";
    switch(this->gender){
        case 'm': returnthis = "male";
            break;
        case 'f': returnthis = "female";
            break;
        default: returnthis = "unknown";
            break;
    }
    return returnthis;
}
QString User::getStreet(){return this->street;
                         }
QString User::getHousenr(){
    return this->housenr;
}
QString User::getZipcode(){
    return this->zipcode;
}
int User::getHomePhone(){
    return this->homePhone;
}
QString User::getEmail(){
    return this->email;
}
QDate User::getBirthDate(){
    return date;
}
