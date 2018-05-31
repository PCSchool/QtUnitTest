#ifndef EXCEPTIONINVALIDPARAMETERS_H
#define EXCEPTIONINVALIDPARAMETERS_H

#include <QException>

class ExceptionInvalidParameters: public QException
{
public:
    const QString error = "ExceptionInvalidParameters: the values of the parameters are incorrect or empty. Check the parameters to prevent this error from occuring again.";
    void raise() const {throw * this;}
    ExceptionInvalidParameters *clone() const {return new ExceptionInvalidParameters(*this);}
};

#endif // EXCEPTIONINVALIDPARAMETERS_H
