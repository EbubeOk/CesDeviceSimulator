#include "ces_device.h"
#include "ui_ces_device.h"

CES_Device::CES_Device(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CES_Device)
{
    ui->setupUi(this);
    timer = new CES_Timer();
    control = new CES_Controller();

    //initial UI setup
    ui->lcdNumber->display("00:00");
    ui->frequencyDisplay->setText(QString::number(control->get_frequency()));
    ui->batteryDisplay->setText(QString::number(control->get_battery_charge()));

    //timer setup
    connect(timer->get_battery_timer(), SIGNAL(timeout()), this, SLOT(decrement_battery()));
    timer->start_battery_timer();
    connect(timer->get_time_timer(), SIGNAL(timeout()), this, SLOT(decrement_time()));
    connect(timer->get_inactivity_timer(), SIGNAL(timeout()), this, SLOT(inactive_timeout()));
    timer->start_inactivity_timeout();
}

CES_Device::~CES_Device()
{
    delete ui;
    delete timer;
    delete control;
}

void CES_Device::show_countdown()
{
    QString str = QString::asprintf("%02d:%02d", chosenTime / 60, chosenTime % 60);
    ui->lcdNumber->display(str);
}

//NUMERIC BATTERY - CAN BE MODIFIED
void CES_Device::show_battery_charge()
{
    if(control->get_battery_charge() <= 5)
    {
        //DISPLAY WARNING
        QString str;
        str = "%1       %2";
        ui->batteryDisplay->setText(str.arg("WARNING - LOW BATTERY", QString::number(control->get_battery_charge())));
    }
    else
    {
        ui->batteryDisplay->setText(QString::number(control->get_battery_charge()));
    }
}

void CES_Device::show_frequency()
{
    float freq = control->get_frequency();
    if (freq == 0.5)
        freq = 77;
    else if (freq == 77)
        freq = 100;
    else if (freq == 100)
        freq = 0.5;
    control->set_frequency(freq);
    ui->frequencyDisplay->setText(QString::number(freq));
    //---recording
    if(control->get_record_state())
    {
      QString str;
      str = "Frequency set to: %1";
      timer->record_event(str.arg(QString::number(control->get_frequency())));
    }
}


void CES_Device::show_current()
{
    ui->progressBar->setValue(control->get_current() / 50);
}


// arrow up
void CES_Device::on_upButton_clicked()
{
    int curr = control->get_current();
    if (curr >= 500)
    {
      return;
    }
    control->set_current(curr + 100);

    ui->progressBar->setValue(control->get_current() / 50);

    //---recording
    if(control->get_record_state())
    {
      QString str;
      str = "Current set to: %1";
      timer->record_event(str.arg(QString::number(control->get_current())));
    }
}

// arrow down
void CES_Device::on_downButton_clicked()
{
    int curr = control->get_current();
    if (curr <= 0)
    {
      return;
    }
    control->set_current(curr - 100);

    ui->progressBar->setValue(control->get_current() / 50);

    //---recording
    if(control->get_record_state())
    {
      QString str;
      str = "Current set to: %1";
      timer->record_event(str.arg(QString::number(control->get_current())));
    }
}


void CES_Device::on_timerButton_clicked()
{
    if(!control->get_power_state() && control->get_lock_state())
    {
      return;
    }
    timer->stop_countdown();
    switch (chosenTime)
    {
       case TWENTYMIN:
         chosenTime = FOURTYMIN;
         break;
       case FOURTYMIN:
         chosenTime = SIXTYMIN;
         break;
       case SIXTYMIN:
         chosenTime = TWENTYMIN;
         break;
       default:
         chosenTime = TWENTYMIN;
         break;
     }
     show_countdown();
     timer->start_countdown();
     control->set_treatment_time(chosenTime);

     //---recording
     if(control->get_record_state())
     {
       QString str;
       str = "Timer set to: %1:%2";
       timer->record_event(str.arg(QString::asprintf("%02d", chosenTime / 60), QString::asprintf("%02d", chosenTime % 60)));
     }
}


// Change freq
void CES_Device::on_freqButton_clicked()
{
    show_frequency();
}


void CES_Device::on_lockButton_clicked()
{
    if(!control->get_power_state())
    {
      return;
    }
    control->set_lock_state(!control->get_lock_state());
}




void CES_Device::  set_record_style(bool s)
{
    if(s == true){
        ui->recordButton->setStyleSheet("QPushButton {\
                                          background-color:red;\
                                          color: white; \
                                          border: 3px solid black;\
                                          border-width: 3px;\
                                          border-radius: 10px;\
                                          min-width:1em;\
                                          padding: 6px;\
                                          }");
    }
    else{
        ui->recordButton->setStyleSheet("QPushButton {\
                                          background-color:rgb(168, 52, 50);\
                                          color: white; \
                                          border: 3px solid black;\
                                          border-width: 3px;\
                                          border-radius: 10px;\
                                          min-width:1em;\
                                          padding: 6px;\
                                          }");
    }
}


void CES_Device::buttons_state(bool val)
{
   ui->upButton->setEnabled(val);
   ui->downButton->setEnabled(val);
   ui->lockButton->setEnabled(val);
   ui->freqButton->setEnabled(val);
   ui->timerButton->setEnabled(val);
}

void CES_Device::on_recordButton_clicked()
{
    if(!control->get_power_state() || control->get_lock_state())
    {
      return;
    }
    control->set_record_state(!control->get_record_state());
    bool state = control->get_record_state();

   if(control->get_power_state() == true){
    set_record_style(state);}

   //---recording
   if(control->get_record_state())
   {
     QString str;
     str = "Treatment recording started. Frequency: %1 - Current: %2  - Time left: %3:%4";
     timer->record_event(str.arg(QString::number(control->get_frequency()), QString::number(control->get_current()),
                                   QString::asprintf("%02d", chosenTime / 60), QString::asprintf("%02d", chosenTime % 60)));
   }
   else
   {
     timer->record_event("User has ended recording session");
   }
}

void CES_Device::power_off()
{
    ui->offDisplay->setVisible(true);
    buttons_state(false);
    control->set_record_state(!control->get_record_state());
    timer->stop_countdown();
    set_record_style(false);
    control->shutdown();
    ui->lcdNumber->display("00:00");
    ui->frequencyDisplay->setText("");
    show_current();
}

void CES_Device::power_on()
{
    ui->offDisplay->setVisible(false);
    buttons_state(true);
}


void CES_Device::on_powerButton_clicked()
{
    if(control->get_fault_state() || control->get_battery_charge() <= 2)
    {
        return;
    }
    //---recording
    else if(control->get_power_state() && control->get_record_state())
    {
      timer->record_event("User powered off the device.");
    }
    control->set_power_state(!control->get_power_state());
    bool state = control->get_power_state();

    if(state == true){power_on();}
    else{power_off();}
    timer->start_countdown();
    control->set_lock_state(false);
    ui->frequencyDisplay->setText(QString::number(control->get_frequency()));
}

void CES_Device::decrement_battery()
{
  if(!control->get_power_state())
  {
      return;
  }
  if(control->get_battery_charge() > 2)
  {
    control->set_battery_charge(control->get_battery_charge() -1);
    this->show_battery_charge();
  }
  else
  {
    timer->record_event("Device shut off at 2% battery.");
    control->shutdown();
    timer->stop_battery_timer();
    this->power_off();
  }
}

void CES_Device::decrement_time()
{
  control->set_contact_state(ui->onskinCheckBox->isChecked());
  if (control->get_current() >= 700)
  {
      control->set_fault_state(!control->get_fault_state());
      //---recording
      if(control->get_record_state())
      {
        timer->record_event("Device has terminated due to faulty current.");
      }
      control->shutdown();
      this->power_off();
      return;
  }

  //powered on, time left, skin contact
  if(control->get_power_state() && control->get_treatment_time() > 0 && control->get_contact_state())
  {
    control->set_treatment_time(control->get_treatment_time() - 1);
    chosenTime = control->get_treatment_time();
    this->show_countdown();
    //---recording
    if(control->get_record_state()  && control->get_treatment_time() == 0)
    {
      timer->record_event("Treatment complete, timer ended.");
    }
  }
  else if(!control->get_power_state())
  {
     timer->stop_countdown();
  }
}

//SHUTDOWN AFTER 30MIN INACTIVE
void CES_Device::inactive_timeout()
{
  //powered on, inactive time, no skin contact
  if(control->get_power_state() && control->get_inactive_time() > 0 && !control->get_contact_state())
  {
    control->set_inactive_time(control->get_inactive_time() -1);
  }
  else if(control->get_inactive_time() == 0)
  {
    timer->record_event("Device shut off due to inactivity.");
    control->shutdown();
    this->power_off();
  }
  else
  {
    control->set_inactive_time(THIRTYMIN);
  }
}

