#ifndef BINARYPATIENT_H
#define BINARYPATIENT_H

class BinaryPatient{
public:
    int id;
    char email[40];
    char name[40];
    char gender;
    char street[120];
    char housenr[4];
    char zipcode[7];
    int homePhone;
    char birthDate[12];
    double height;
    double weight;
};

#endif // BINARYPATIENT_H
