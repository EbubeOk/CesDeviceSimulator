#ifndef CES_TIMER_H
#define CES_TIMER_H

#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QMainWindow>

class CES_Timer
{
public:
  CES_Timer();
  ~CES_Timer();
  void start_countdown();
  void stop_countdown();
  void start_inactivity_timeout();
  void stop_inactivity_timeout();
  void record_event(QString);


  QTimer* get_battery_timer();
  QTimer* get_time_timer();
  QTimer* get_inactivity_timer();
  void start_battery_timer();
  void stop_battery_timer();
private:
  QTimer *timer;
  QTimer *inactivityTimer;
  QTimer *batteryTimer;
};

#endif // CES_TIMER_H
