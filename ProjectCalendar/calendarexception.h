#ifndef CALENDAREXCEPTION_H
#define CALENDAREXCEPTION_H
#include <QString>
#include <QMessageBox>

using namespace std;

/**
 * @class CalendarException
 * @brief Exceptions utilisés dans ce projet
 */
class CalendarException{
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


#endif // CALENDAREXCEPTION_H
