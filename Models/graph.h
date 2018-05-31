#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QVector>
#include <globals.h>

class Graph
{
public:
    Graph();
    void addPoints(TimePointer point);
    void addToVector(QVector<TimePointer> newPoints);
    void newVector(QVector<TimePointer> points);
    QVector<TimePointer> getVector();
    void resetVector();

private:
    QVector<TimePointer> points;

};

#endif // GRAPH_H
