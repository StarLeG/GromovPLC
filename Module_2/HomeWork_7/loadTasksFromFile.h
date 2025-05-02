#ifndef LOADTASKSFROMFILE_H
#define LOADTASKSFROMFILE_H

#include "main.h"
#include <QFile>
#include <QDataStream>

void loadTasksFromFile(QVector<Task>& tasks, const QString& filename);

#endif // LOADTASKSFROMFILE_H
