#ifndef CES_DEVICE_H
#define CES_DEVICE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CES_Device; }
QT_END_NAMESPACE


#define FREQUENCY1   0.5f
#define FREQUENCY2 100.0f

/*
 * Time in seconds
*/
#define TWENTYMIN 1200
#define THIRTYMIN 1800
#define FOURTYMIN 2400
#define SIXTYMIN  3600



#include <ces_controller.h>
#include <ces_timer.h>

class CES_Device : public QMainWindow
{
    Q_OBJECT

public:
    CES_Device(QWidget *parent = nullptr);
    ~CES_Device();

    void show_countdown();
    void show_battery_charge();
    void show_current();
    void show_frequency();
    void show_lock_state();
    void turn_on_backlight();

private slots:
    void on_upButton_clicked();
    void on_downButton_clicked();
    void on_timerButton_clicked();
    void on_freqButton_clicked();
    void on_lockButton_clicked();
    void on_powerButton_clicked();
    void power_off();
    void power_on();
    void on_recordButton_clicked();
    void buttons_state(bool val);
    void set_record_style(bool s);


    //attached to battery timer
    void decrement_battery();
    //attached to time timer
    void decrement_time();
    //attached to inactive timer
    void inactive_timeout();

private:
    Ui::CES_Device *ui;
    CES_Timer *timer;
    CES_Controller *control;

    int chosenTime = 0;
};
#endif // CES_DEVICE_H
