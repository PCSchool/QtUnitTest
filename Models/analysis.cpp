#include "analysis.h"
#include <globals.h>
#include <QDir>
#include <QDirIterator>

//constructor
Analysis::Analysis()
{

}

//methods
QVector<TimePointer> Analysis::readFile(QString path){
    QVector<TimePointer> vector;
    try{
        FILE * fp = fopen(path.toLocal8Bit().constData(), "rb");
        int next = 0;
        double x,y;
        char buffer[9];
        if(fp != NULL){
            int read = 0;
            while((read = fread(buffer, 1, 8, fp)) > 0){
                QByteArray test(buffer, 8);
                if(test.size() == 8){
                    if(next == 1){
                        memcpy(&y, test, 8);
                        TimePointer tp;
                        tp.x = x;
                        tp.y = y;
                        vector.append(tp);
                        next = 0;
                    }else{
                        memcpy(&x, test, 8);
                        next++;
                    }
                }
            }
            fclose(fp);
        }
    } catch(...){
        qFatal("Error occured within method Analysis::readDir(QString path)");
    }
    return vector;
}

QVector<TimePointer> Analysis::readDir(QString path){
    setRecordingDir(QDir(path));
    setRecordingFilePath(path);

    QVector<TimePointer> vector;
    try{
        FILE * fp;
        int next = 0;
        double x,y;
        char buffer[9];
        if(!path.length() < 1){
            QDir dir(path);
            QDirIterator it(recordingDir, QDirIterator::NoIteratorFlags);

            while(it.hasNext()) {
                QString filename = it.next();
                QFile file(filename.toLocal8Bit().constData());
                file.open(QIODevice::ReadOnly);
                while(!file.atEnd()){
                    file.read(buffer, 8);
                    QByteArray save(buffer, 8);
                    memcpy(&x, save, 8);
                    std::cout << x << " - ";
                    int size = save.size();
                    QByteArray ss(buffer, 8);
                    if(save.size() == 8){
                        if(next == 0){
                            next++;
                            memcpy(&x, save, 8);
                            TimePointer tp;
                            tp.x = x;
                            tp.y = y;
                            vector.append(tp);
                        }else{
                            memcpy(&y, save, 8);
                            next = 0;
                        }
                    }
                    QByteArray sss(buffer, 8);
                }
                file.close();
            }
        }
    } catch(...){
        qFatal("Error occured within method Analysis::readDir(QString path)");
    }
    std::cout << endl << " final : " << vector.count();
    return vector;
}

void Analysis::convertMemcpy(){
    /*open file read constantly 16 bytes - 128 bits out
    std::ifstream fin("recording_2.bin", std::ios_base::in | std::ios_base::binary);
    if(!fin.is_open()){
        return;
    }
    //recording_0  <-- real recording file, contains 16KB, 16444 bytes
    //testerFile   <-- fake testing file contains 8 bytes
    //std::ifstream fin("recording_0.bin", std::ios_base::in | std::ios_base::binary);
    QFile file("recording_2.bin");

    if(!file.open(QIODevice::ReadOnly)){
        std::cout << "File couldnt be found nor opened.";
        return;
    }else{
        int counter = 0;
        QByteArray *array;
        char b[sizeof(array)];
        uint_fast16_t len;

        file.seek(0);
        QByteArray bytes = file.readAll();

        QDataStream dataStream(&file);
        dataStream.setByteOrder(QDataStream::LittleEndian);
        QVector<TimePointer> result;

        file.seek(0);
        size_t fileSize = fin.tellg();
        fin.seekg(0, ios::beg);

        std::vector<byte> vector(fileSize, 0);

        //.write(static_cast<char*>(static_cast<void*>(&data)), std::ios_base::app | std::ios::binary);
        //create  a <vector> to hold all the bytes in the file
        //fin.read(reinterpret_cast<char*>(&vector[0]), sizeof(fileSize));
        //fin.read(static_cast<char*>(static_cast<void*>(&vector[0])), sizeof(fileSize));

        //read the file
        char temp[fileSize];
        //fin.read(reinterpret_cast<char*>(&data[0]), sizeof(fileSize));
        fin.read(static_cast<char*>(static_cast<void*>(&vector[0])), sizeof(fileSize));

        TimePointer d1;
        d1.x = 0;
        d1.y = 0;

        fin.read(temp, 0-16);
        memcpy(&d1, temp, sizeof(TimePointer));
        std::cout << "test d1: " << d1.x << " - " << d1.y << " \n";

        fin.read(&temp[0-16], (16-32));
        memcpy(&d1, temp, sizeof(TimePointer));
        std::cout << "test d2: " << d1.x << " - " << d1.y << " \n";

        fin.read(&temp[32-48], (48-56));
        memcpy(&d1, temp, sizeof(TimePointer));
        std::cout << "test d3: " << d1.x << " - " << d1.y << " \n";
        //each character pointer on the system in 4-bytes long

        std::vector<byte> data(fileSize, 0);
        //read the file
        //fin.read(reinterpret_cast<char*>(&data[0]), sizeof(fileSize));
        fin.read(static_cast<char*>(static_cast<void*>(&data[0])), sizeof(fileSize));
        //Axis a;
        fin.read((char*)&len, 2);
        std::string str(len, '\o');
        //array = static_cast<QByteArray*>(&len);
        //array = reinterpret_cast<QByteArray*>(&len);
        array = static_cast<QByteArray*>(static_cast<void*>(&len));
        //loop in buffer

        std::cout << " Done reading  \n Bytes readed in file : " << counter << "\n fileSize file : " << fileSize << "\n data size : " << data.size() << endl;
        fin.close();
    }*/
}

void Analysis::addRecordingDirList(QString path){
    recordingPathList.append(path);
}

QList<QString> Analysis::getRecordingList(){
    return recordingPathList;
}

void Analysis::addPointerList(TimePointer pointer){
    pointerList.push_back(pointer);
}

QList<TimePointer> Analysis::getPointerList(){
    return pointerList;
}

void Analysis::clearPointerList(){
    pointerList.clear();
}

QVector<double> Analysis::getXaxis(){
    return this->Xaxis;
}

QVector<double> Analysis::getYaxis(){
    return this->yaxis;
}

void Analysis::addToVector(double x, double y){
     Xaxis.push_back(x);
     yaxis.push_back(y);
}

void Analysis::setRecordingDir(QDir dir){
    this->recordingDir = dir;
}

QDir Analysis::getRecordingDir(){
    return this->recordingDir;
}

void Analysis::setRecordingFilePath(QString filepath){
    recordingFilePath = filepath;
    recordingFile.setFileName(filepath);
}

QString Analysis::getRecordingFilePath(){
    return recordingFilePath;
}

