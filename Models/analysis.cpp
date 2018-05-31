#include "analysis.h"
#include <globals.h>
#include <QDir>
#include <QDirIterator>
#include <exceptions/exceptioninvalidparameters.h>

//constructor
Analysis::Analysis()
{

}

//methods
QVector<TimePointer> Analysis::readFile(QString path){
    if(path.isEmpty()){
        throw ExceptionInvalidParameters();
    }
    QVector<TimePointer> vector;
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
    return vector;
}

QVector<TimePointer> Analysis::readDir(QString path){
    if(path.isEmpty()){
        throw ExceptionInvalidParameters();
    }
    setRecordingDir(QDir(path));
    setRecordingFilePath(path);

    QVector<TimePointer> vector;
    TimePointer tp;
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
                //int size = save.size();
                QByteArray ss(buffer, 8);
                if(save.size() == 8){
                    if(next == 1){
                        next++;
                        memcpy(&x, save, 8);
                        tp.x = x;
                    }else{
                        memcpy(&y, save, 8);
                        tp.y = y;
                        vector.append(tp);
                        next = 0;
                    }
                }
                QByteArray sss(buffer, 8);
            }
            file.close();
        }
    }
    std::cout << endl << " final : " << vector.count();
    return vector;
}

void Analysis::addRecordingDirList(QString path){
    if(path.isEmpty()){
        throw ExceptionInvalidParameters();
    }
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
    if(dir.path().isEmpty()){throw ExceptionInvalidParameters();}
    this->recordingDir = dir;
}

QDir Analysis::getRecordingDir(){
    return this->recordingDir;
}

void Analysis::setRecordingFilePath(QString filepath){
    if(filepath.isEmpty()){throw ExceptionInvalidParameters();}
    recordingFilePath = filepath;
    recordingFile.setFileName(filepath);
}

QString Analysis::getRecordingFilePath(){
    return recordingFilePath;
}

