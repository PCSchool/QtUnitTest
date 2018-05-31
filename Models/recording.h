#ifndef RECORDING_H
#define RECORDING_H

#include <QDir>
#include <QSize>

class Recording{
  public:
    //enums
    enum Types{line = 0, bar, histogram, scatter, invalidtype};
    enum Sensors{heartrate = 0, accelerometer, microphone, skintemperature, lightsensor, invalidsensor};

    //constructors
    Recording();
    Recording(int width, int height, int x, int y);

    //methods
    void setProperties(double frequency, double amplitude, int yAxisMax, int yAxisMin, int xAxisMax,int xAxisMin, int interval, QString graph, QString sensor);
    void changePosition(int x, int y);
    void changeSize(int width, int height);
    QString convertSensor(Sensors _s);
    QString convertGraphType(Types _s);

    //getters
    int getYAxisMax();
    int getYAxisMin();
    int getXAxisMax();
    int getXAxisMin();
    QString getGraphType();
    QString getSensor();
    int getInterval();
    double getFrequency();
    double getAmplitude();

    //public fields
    QString pathRecording;
    QString controlDir(QDir dir);

  public slots:

  private:
    //methods
    static Recording::Sensors selectSensor(std::string _s);
    static Recording::Types selectTypes(std::string _s);

    //field
    QSize size;
    //position & size of graph

    int width, height, x, y;

    //properties of graph
    double frequency, amplitude;
    int yAxisMin, yAxisMax, xAxisMax, xAxisMin, counter;
    Types type;
    Sensors sensor;
    int secOnDisplay, interval;
    QString pauze, typeString, sensorString;



  signals:
    void newCounter(int counter);
};

#endif // RECORDING_H
