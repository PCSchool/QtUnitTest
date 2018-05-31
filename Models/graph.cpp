#include "graph.h"
#include <Exceptions/exceptioninvalidparameters.h>

Graph::Graph()
{

}

void Graph::addPoints(TimePointer point){
    points.push_back(point);
}

void Graph::addToVector(QVector<TimePointer> newPoints){
    if(newPoints.isEmpty()){
        throw ExceptionInvalidParameters();
    }
    points.append(newPoints);
}

void Graph::newVector(QVector<TimePointer> points){
    if(points.isEmpty()){
        throw ExceptionInvalidParameters();
    }
    this->points.clear();
    this->points = points;
}

QVector<TimePointer> Graph::getVector(){
    return points;
}

void Graph::resetVector(){
    points.clear();
}
