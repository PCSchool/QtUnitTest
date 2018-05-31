#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <QObject>
#include <QFile>
#include <QWaitCondition>
#include <QMutex>
#include <condition_variable>
#include <QBuffer>
#include <QDir>
#include <QReadWriteLock>
#include <QReadLocker>
#include <windows.h>
#include <globals.h>
#include <QVector>

class BinaryReader : public QObject
{
    Q_OBJECT
public:
    //constructors
    BinaryReader();                                     //default constructor

    //methods
    void convertDoubleToBinary(double d);
    void setUserDir(QDir dir);

    //important for thread synchronization
    QWaitCondition bufferIsFull;            //true if buffer is full and ready to be written to file, false is buffer still is getting filled
    QWaitCondition bufferDoneWriteFile;     //true when the buffer is done being written into the file, false when the buffer still aint completely written to the file
    QMutex mutex;                           //QMutex mutex, can be used to lock or unlock certain parts of threads
    QArrayData tester;
    int numberFile, sizeFile;
    bool upNumberFile;
signals:
    void start();
    void finished();
    void error(QString error);
    void writeNewBufferToFile();
    void fileFull();
    void bufferFull(QByteArray array, QVector<TimePointer> vector);      //signal for binaryWriter, that the buffer
    void setDir(QDir dir);                  //setDirectory

public slots:
    void writeBufferToFile(QByteArray array, QVector<TimePointer> vector);   //add new data to buffer

private slots:

private:
    QFile file;
    QBuffer qbuffer;
    QByteArray qarray;
    QByteArray byteArray;
    QDir dir;                           //Directory where the recording will be stored, when entered recordDialog
    QMutexLocker* mutexLocker;          //QMutexLocker mutexLocker, can be used to lock or unlock certain
    QReadWriteLock* readWriteLocker;    //QReadWriteLocker readWriteLocker, can be used to

    int numUsedBytes;                   //amount of bytes used
    int dataSize;                       //dataSize
    int bufferSize;                     //bufferSize
};

#endif // BINARYREADER_H
