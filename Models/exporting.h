#ifndef EXPORTING_H
#define EXPORTING_H

#include <QDir>

class Exporting : public QObject
{
    Q_OBJECT
public:
    //constructor
    explicit Exporting(QObject *parent = nullptr);

    //methods
    void cleanUserDir(QString newdir, QString path);
    void cleanExportDir(QString newdir, QString path);
    void cleanListbox();

    //getters/setters for properties
    void setUserDir(QDir dir);
    void setExportDir(QDir dir);
    QDir getUserDir();
    QDir getExportDir();

signals:
    updateReady(QDir userDir, QDir exportDir);
    readyToListBox(QStringList stringlist);

public slots:

private:
    QDir userDir;
    QDir exportDir;
};

#endif // EXPORTING_H
