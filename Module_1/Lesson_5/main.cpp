#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QVector>

struct DataPoint {
    float temperature;
    float regulator;
};

QVector<DataPoint> readCSV(const QString& filePath);
void calculateOvershoot(const QVector<DataPoint>& dataPoints, float setpoint);
int countTrendReversals(const QVector<DataPoint>& dataPoints);
QVector<int> findTrendReversals(const QVector<DataPoint>& dataPoints);
int findTimeToSetpoint(const QVector<DataPoint>& dataPoints, const QVector<int>& reversalIndices, float tolerance = 3.0f);




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Путь к CSV-файлу
    QString filePath = "data.csv";

    // Читаем данные из CSV-файла
    QVector<DataPoint> dataPoints = readCSV(filePath);

    // Выводим прочитанные данные
    qDebug() << "Read data:";
    for (const auto& point : dataPoints) {
        qDebug() << "Temperature:" << point.temperature
                 << "| Regulator:" << point.regulator;
    }

    // Уставка (значение регулятора)
    float setpoint = 55.0f;

    qDebug() << "************************************************\n";
    // Определяем максимальное перерегулирование
    calculateOvershoot(dataPoints, setpoint);
    qDebug() << "\n************************************************\n";

    // Определяем количество разворотов тренда
    int reversals = countTrendReversals(dataPoints);
    qDebug() << "Number of trend reversals:" << reversals;
    qDebug() << "\n************************************************\n";

    // Находим точки разворота
    QVector<int> reversalIndices = findTrendReversals(dataPoints);
    qDebug() << "Pivot point indices:" << reversalIndices;

    // Определяем время выхода на уставку
    int timeToSetpoint = findTimeToSetpoint(dataPoints, reversalIndices);
    if (timeToSetpoint != -1) {
        qDebug() << "\n************************************************\n";
        qDebug() << "Time to reach set point (index):" << timeToSetpoint;
        qDebug() << "\n************************************************\n";
        qDebug() << "Temperature at this moment:" << dataPoints[timeToSetpoint].temperature;
        qDebug() << "\n************************************************\n";
    } else {
        qDebug() << "Output to set point not reached.";
        qDebug() << "\n************************************************\n";
    }
    return a.exec();
}

// Функция для чтения CSV файла
QVector<DataPoint> readCSV(const QString& filePath) {
    QVector<DataPoint> dataPoints;
    QFile file(filePath);

    // Открываем файл на чтение
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);        

        // Пропускаем заголовок (первую строку)
        in.readLine();

        // Читаем файл построчно
        while (!in.atEnd()) {
            QString line = in.readLine();  // Читаем строку
            QStringList fields = line.split(";");  // Разбиваем строку на поля

            // Проверяем, что строка содержит 2 поля
            if (fields.size() == 2) {
                DataPoint point;
                point.temperature = fields[0].trimmed().toFloat();  // Температура
                point.regulator = fields[1].trimmed().toFloat();       // Регулятор
                dataPoints.append(point);  // Добавляем в вектор
            }
        }

        file.close();
    } else {
        qDebug() << "Error opening file: " << file.errorString();
    }


    return dataPoints;
}

// Функция для определения максимального выбега
void calculateOvershoot(const QVector<DataPoint>& dataPoints, float setpoint) {
    bool overshootDetected = false;
    float overshootTemperature = 0.0f;
    float maxOvershoot = 0.0f;
    float maxUndershoot = 0.0f;

    for (const auto& point : dataPoints) {
        if (!overshootDetected && point.temperature > setpoint) {
            // Фиксируем момент первого превышения уставки
            overshootDetected = true;
            overshootTemperature = point.temperature;
            qDebug() << "First set point exceeded: Temperature =" << overshootTemperature;
        }

        if (overshootDetected) {
            // Вычисляем отклонения от уставки
            float deviation = point.temperature - setpoint;

            // Находим максимальное отклонение в плюс (перерегулирование)
            if (deviation > maxOvershoot) {
                maxOvershoot = deviation;
            }

            // Находим максимальное отклонение в минус (недорегулирование)
            if (deviation < maxUndershoot) {
                maxUndershoot = deviation;
            }
        }
    }

    if (overshootDetected) {
        qDebug() << "Maximum overshoot (plus):" << maxOvershoot;
        qDebug() << "Maximum underregulation (minus):" << maxUndershoot;
    } else {
        qDebug() << "No overshoot detected.";
    }
}

// Функция для определения количества разворотов тренда
int countTrendReversals(const QVector<DataPoint>& dataPoints) {
    if (dataPoints.size() < 2) {
        return 0;  // Недостаточно данных для определения тренда
    }

    int reversals = 0;
    bool wasIncreasing = false;  // Предыдущее направление (рост или падение)
    bool isInitialized = false;  // Флаг для инициализации направления

    for (int i = 1; i < dataPoints.size(); ++i) {
        float prevTemp = dataPoints[i - 1].temperature;
        float currTemp = dataPoints[i].temperature;

        if (currTemp > prevTemp) {
            // Температура растёт
            if (isInitialized && !wasIncreasing) {
                reversals++;  // Разворот с падения на рост
            }
            wasIncreasing = true;
            isInitialized = true;
        } else if (currTemp < prevTemp) {
            // Температура падает
            if (isInitialized && wasIncreasing) {
                reversals++;  // Разворот с роста на падение
            }
            wasIncreasing = false;
            isInitialized = true;
        }
        // Если температура не изменилась, направление не меняется
    }

    return reversals;
}

// Функция для определения количества разворотов тренда
QVector<int> findTrendReversals(const QVector<DataPoint>& dataPoints) {
    QVector<int> reversalIndices;  // Индексы точек разворота
    if (dataPoints.size() < 2) {
        return reversalIndices;  // Недостаточно данных для определения тренда
    }

    bool wasIncreasing = false;  // Предыдущее направление (рост или падение)
    bool isInitialized = false;  // Флаг для инициализации направления

    for (int i = 1; i < dataPoints.size(); ++i) {
        float prevTemp = dataPoints[i - 1].temperature;
        float currTemp = dataPoints[i].temperature;

        if (currTemp > prevTemp) {
            // Температура растёт
            if (isInitialized && !wasIncreasing) {
                reversalIndices.append(i - 1);  // Разворот с падения на рост
            }
            wasIncreasing = true;
            isInitialized = true;
        } else if (currTemp < prevTemp) {
            // Температура падает
            if (isInitialized && wasIncreasing) {
                reversalIndices.append(i - 1);  // Разворот с роста на падение
            }
            wasIncreasing = false;
            isInitialized = true;
        }
        // Если температура не изменилась, направление не меняется
    }

    return reversalIndices;
}

// Функция для определения времени выхода на уставку
int findTimeToSetpoint(const QVector<DataPoint>& dataPoints, const QVector<int>& reversalIndices, float tolerance) {
    if (reversalIndices.size() < 2) {
        return -1;  // Недостаточно точек разворота
    }

    for (int i = 1; i < reversalIndices.size(); ++i) {
        int upperIndex = reversalIndices[i - 1];  // Верхняя точка (пик)
        int lowerIndex = reversalIndices[i];      // Нижняя точка (впадина)

        float upperTemp = dataPoints[upperIndex].temperature;
        float lowerTemp = dataPoints[lowerIndex].temperature;

        // Разница между верхней и нижней точками
        float difference = qAbs(upperTemp - lowerTemp);

        if (difference < tolerance) {
            // Нашли момент, когда разница меньше 3 градусов
            return lowerIndex;  // Возвращаем индекс нижней точки
        }
    }

    return -1;
}
