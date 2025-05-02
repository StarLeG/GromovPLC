#ifndef SAVETASKSTOFILE_H
#define SAVETASKSTOFILE_H

#include "main.h"
#include <QFile>

void saveTasksToFile(const QVector<Task>& tasks, const QString filename);

#endif // SAVETASKSTOFILE_H
