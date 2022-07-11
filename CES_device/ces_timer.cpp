#include "ces_timer.h"

CES_Timer::CES_Timer() : timer(new QTimer()), inactivityTimer(new QTimer()), batteryTimer(new QTimer())
{

}

CES_Timer::~CES_Timer()
{
  delete timer;
  delete inactivityTimer;
  delete batteryTimer;
}

void CES_Timer::start_countdown()
{
  timer->start(1000);
}

void CES_Timer::stop_countdown()
{
  timer->stop();
}

void CES_Timer::start_inactivity_timeout()
{
  inactivityTimer->start(1000);
}

void CES_Timer::stop_inactivity_timeout()
{
    inactivityTimer->stop();
}


void CES_Timer::record_event(QString e)
{
    QFile file("session_recording.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
      QTextStream out(&file);
      QTime time = QTime::currentTime();
      QString time_txt = time.toString("[hh:mm:ss]");

      out << time_txt << " - " << e <<"\n";

      file.close();
    }
}


QTimer* CES_Timer::get_battery_timer(){return batteryTimer;}

void CES_Timer::start_battery_timer()
{
    batteryTimer->start(1000*60);
}

void CES_Timer::stop_battery_timer()
{
    batteryTimer->stop();
}

QTimer* CES_Timer::get_time_timer(){return timer;}
QTimer* CES_Timer::get_inactivity_timer(){return inactivityTimer;}
