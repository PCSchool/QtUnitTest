#include "binaryreader.h"
#include <QFile>
#include <iostream>
#include <fstream>
#include <ostream>
#include <streambuf>
#include <QDataStream>
#include <QtDebug>
#include <stdint.h>
#include <cstdlib>
#include <bitset>
#include <QWaitCondition>
#include <stdio.h>
#include <QBuffer>
#include <QDir>
#include <mutex>
#include <condition_variable>
#include <globals.h>
#include <windows.h>
#include <QVector>

using namespace std;

BinaryReader::BinaryReader()
{
    numberFile = 0;
    sizeFile = 0;
    upNumberFile = false;
    dataSize = 1024;
    bufferSize = 1024;
    numUsedBytes = 1;
    QByteArray* array = new QByteArray[bufferSize];
    qbuffer.setBuffer(array);
}

void BinaryReader::setUserDir(QDir dir){
    //should be used for binarywriter as directory where the file should be stored
    this->dir = dir;
}

//write buffer to binary file
void BinaryReader::writeBufferToFile(QByteArray array, QVector<TimePointer> vector){

    std::string path = dir.path().toLocal8Bit().constData();
    path = path + "/recording_" + std::to_string(numberFile) + ".bin";
    QString pathnow = QString::fromStdString(path);

    EnterCriticalSection(&shared_buffer_lock);
    QFile file(pathnow);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QDataStream out(&file);
    sizeFile = file.size();
    out.setVersion(QDataStream::Qt_5_10);
    out.setByteOrder(QDataStream::LittleEndian);

    for(int i = 0; i < vector.count(); ++i){
        out << (double)vector[i].x;
        out << (double)vector[i].y;
    }
    file.close();
    LeaveCriticalSection(&shared_buffer_lock);

    if(sizeFile > maxBinFileSize){  //400 test with multiple files
        sizeFile = 0;
        numberFile++;
    }
}
