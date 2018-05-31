#ifndef EXCEPTIONINVALIDCONSTRUCTOR_H
#define EXCEPTIONINVALIDCONSTRUCTOR_H

#include <QException>

class ExceptionInvalidConstructor : public QException
{
public:
    const QString error = "ExceptionInvalidConstructor: the values of the parameters given allong the constructor are incorrect.";
    void raise() const {throw * this;}
    ExceptionInvalidConstructor *clone() const {return new ExceptionInvalidConstructor(*this);}
};

#endif // EXCEPTIONINVALIDCONSTRUCTOR_H
