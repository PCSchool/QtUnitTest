
#include "recording.h"
#include <stdexcept>
#include <QDateTime>
#include <Exceptions/exceptioninvalidenumtype.h>
#include <Exceptions/exceptioninvalidparameters.h>

//default constructor;
Recording::Recording()
{

}

//constructor with parameters
Recording::Recording(int width, int height, int x, int y){
    if(width < 0 || height < 0 || x < 0 || y < 0 ){
        //throw exception
        throw ExceptionInvalidParameters();
    }
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
}

//methods
QString Recording::controlDir(QDir dir){
    //create new directory for new recording
    // directory name contains of recording_date_time
    // - date being the current date
    // - time being the current time of creating the recording
    QString date = QDateTime::currentDateTime().toString("dd-MM-yyyy");
    QString time = QDateTime::currentDateTime().toString("hh-mm-ss");
    QString path = "recording_" + date + "_" + time;
    QString fullPath = dir.path() + "/" + path;
    if(!QDir(path).exists()){
        dir.mkdir(path);
    }

    pathRecording = fullPath;
    return fullPath;
}

void Recording::changePosition(int x, int y){
    this->x = x;
    this->y = y;
}

void Recording::changeSize(int width, int height){
    if(width < 0 || height < 0){
        throw ExceptionInvalidParameters();
    }
    size.setHeight(height);
    size.setWidth(width);
}

void Recording::setProperties(double frequency, double amplitude, int yAxisMax, int yAxisMin, int xAxisMax, int xAxisMin, int interval, QString graph, QString sensor){
    this->frequency = frequency;
    this->amplitude = amplitude;
    this->yAxisMax = yAxisMax;
    this->yAxisMin = yAxisMin;
    this->xAxisMax = xAxisMax;
    this->xAxisMin = xAxisMin;
    this->interval = interval;
    this->sensorString = sensor;
    this->typeString = graph;
    this->sensor = selectSensor(sensor.toLocal8Bit().constData());
    this->type = selectTypes(graph.toLocal8Bit().constData());
}

Recording::Types Recording::selectTypes(std::string _s){
    transform(_s.begin(), _s.end(), _s.begin(), ::toupper);
    if(_s == "LINE") return line;
    else if(_s == "BAR") return bar;
    else if(_s == "HISTOGRAM") return histogram;
    else if(_s == "SCATTERPLOT") return scatter;
    throw ExceptionInvalidEnumType();
    return invalidtype;
}

Recording::Sensors Recording::selectSensor(std::string _s){
    transform(_s.begin(), _s.end(), _s.begin(), ::toupper);
    if(_s == "HEARTRATE") return heartrate;
    else if(_s == "ACCELEROMETER") return accelerometer;
    else if(_s == "MICROPHONE") return microphone;
    else if(_s == "SKINTEMPERATURE") return skintemperature;
    else if(_s == "LIGHTSENSOR") return lightsensor;
    throw ExceptionInvalidEnumType();
    return invalidsensor;
}

QString Recording::convertSensor(Sensors _s){
    if(_s == Recording::heartrate) return "HEARTRATE";
    else if(_s == Recording::accelerometer) return "ACCELEROMETER";
    else if(_s == Recording::microphone) return "MICROPHONE";
    else if(_s == Recording::skintemperature) return "SKINTEMPERATURE";
    else if(_s == Recording::lightsensor) return "LIGHTSENSOR";
    else if(_s == Recording::invalidsensor) return "INVALIDSENSOR";
    return "";
}

QString Recording::convertGraphType(Types _s){
    if(_s == Recording::line) return "LINE";
    else if(_s == Recording::bar) return "BAR";
    else if(_s == Recording::histogram) return "HISTOGRAM";
    else if(_s == Recording::scatter) return "SCATTERPLOT";
    else if(_s == Recording::invalidtype) return "INVALIDTYPE";
    return "";
}

double Recording::getFrequency(){
    return frequency;
}
double Recording::getAmplitude(){
    return amplitude;
}

int Recording::getYAxisMax(){
    return this->yAxisMax;
}

int Recording::getYAxisMin(){
    return this->yAxisMin;
}

int Recording::getXAxisMax(){
    return this->xAxisMax;
}

int Recording::getXAxisMin(){
    return this->xAxisMin;
}

QString Recording::getGraphType(){
    return this->typeString;
}

QString Recording::getSensor(){
    return this->sensorString;
}

int Recording::getInterval(){
    return this->interval;
}
