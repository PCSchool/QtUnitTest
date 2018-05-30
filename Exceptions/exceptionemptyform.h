#ifndef EXCEPTIONEMPTYFORM_H
#define EXCEPTIONEMPTYFORM_H

#include <QException>

class ExceptionEmptyForm : public QException
{
public:
    const QString error = "ExceptionnEmptyForm: Not all required fields for the form have been filled in.";
    void raise() const {throw * this;}
    ExceptionEmptyForm *clone() const {return new ExceptionEmptyForm(*this);}
};

#endif // EXCEPTIONEMPTYFORM_H
