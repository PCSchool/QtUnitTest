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

