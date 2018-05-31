#include "exporting.h"
#include <QDir>
#include <QDirIterator>
#include <Exceptions/exceptioninvalidparameters.h>

//constructors
Exporting::Exporting(QObject *parent) : QObject(parent)
{

}

//methods
void Exporting::cleanUserDir(QString newdir, QString path){
    if(newdir.isEmpty() || path.isEmpty()){
        throw ExceptionInvalidParameters();
    }
    std::string x = path.toLocal8Bit().constData();
    std::size_t _s = x.find_last_of("/\\");
    int id = atoi(x.substr(_s+1).c_str());
    QDir patientDir(newdir + "/" + QString::number(id));
    if(patientDir.exists()){
        this->setUserDir(patientDir);
    }

    emit updateReady(userDir, exportDir);
}

//show userDirectory files in listbox lbListItems
// add filter QDIR::NoDotAndDotDot
void Exporting::cleanListbox(){
    QStringList results;
    QDirIterator iter(userDir,QDirIterator::Subdirectories);
    //QDirIterator iter(exporting.getUserDir(), QStringList() << "*.jpg", QDir::Files, QDirIterator::Subdirectories);
    while(iter.hasNext()){
        if(QDir::NoDotAndDotDot == 2){
            results << "QDir = 1";
        }
        results << iter.next();
    }
    emit readyToListBox(results);
}

void Exporting::cleanExportDir(QString newdir, QString path){
    if(newdir.isEmpty() || path.isEmpty()){
        throw ExceptionInvalidParameters();
    }
    std::string x = path.toLocal8Bit().constData();
    std::size_t _s = x.find_last_of("/\\");
    QDir exportDir(newdir+ "/" + QString(x.substr(_s+1).c_str()));

    if(exportDir.exists()){
        this->setExportDir(exportDir);
    }
    emit updateReady(userDir, exportDir);
}

//getters/setters
void Exporting::setUserDir(QDir dir){
    if(dir.path().isEmpty() ||  dir.path().length() < 4){
        throw ExceptionInvalidParameters();
    }
    this->userDir = dir;
}

void Exporting::setExportDir(QDir dir){
    if(dir.path().isEmpty() || dir.path().length() < 4){
        throw ExceptionInvalidParameters();
    }
    this->exportDir = dir;
}


QDir Exporting::getUserDir(){
    return userDir;
}


QDir Exporting::getExportDir(){
    return exportDir;
}
