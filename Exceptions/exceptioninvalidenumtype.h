#ifndef EXCEPTIONINVALIDENUMTYPE_H
#define EXCEPTIONINVALIDENUMTYPE_H

#include <QException>

class ExceptionInvalidEnumType : public QException
{
public:
    const QString error = "ExceptionInvalidEnumType: the given type doesnt exists in the given enum.";
    void raise() const {throw * this;}
    ExceptionInvalidEnumType *clone() const {return new ExceptionInvalidEnumType(*this);}
};

#endif // EXCEPTIONINVALIDENUMTYPE_H
