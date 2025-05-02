#ifndef MAIN_H
#define MAIN_H

#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QDate>
#include <QTextStream>





struct Task{
    QString title; // Название задачи
    QDate date; // Дата выполнения
    int priority; // Приоритет (1 - высокий, 2 - средний, 3 - низкий)
};



#endif // MAIN_H
