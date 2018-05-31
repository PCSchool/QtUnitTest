#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <QObject>
#include <QFile>
#include <QWaitCondition>
#include <QMutex>
#include <condition_variable>
#include <QBuffer>
#include <QDir>
#include <QReadWriteLock>
#include <windows.h>
#include <globals.h>
#include <QVector>

class BinaryWriter : public QObject
{
    Q_OBJECT
public:
    BinaryWriter();  //default constructor, set up values for most attributes

    void convertDoubleToBinary(double d);       //convertDoubleToBinary
    void setUserDir(QDir dir);                  //set directory where the recording files will be stored

    QBuffer qbuffer;
    QArrayData tester;                          //test QArrayData
    int numberFile;                             //default 0
    QVector<TimePointer> vector;

signals:
    void start();                               //start thread
    void finished();                            //finishes thread
    void error(QString error);                  //debugging error, to show whats wrong
    void writeNewBufferToFile();                //ready for new buffer to be written
    void fileFull();
    void bufferFull(QByteArray array, QVector<TimePointer> vector);
    void setDir(QDir dir);

public slots:
    //add new data to buffer
    void writeData(double xAxis, double yAxis);
    void readBuffer();

private slots:

private:
    TimePointer pointer;
    QByteArray qarray;
    QByteArray byteArray;
    QDir dir;                                   //directory used
    int numUsedBytes;
    int dataSize;
    int bufferSize;
};

#endif // BINARYWRITER_H
