#include "ces_controller.h"

CES_Controller::CES_Controller() : settings_locked(false), internal_fault(false), electrode_skin_contact(false),
                                   powered_on(false), record(false), treatment_time(0), inactive_time(1800), current(0), frequency(0.5f),
                                   battery_charge(100)
{ }

CES_Controller::~CES_Controller(){ }

void  CES_Controller::set_power_state(bool ps)  {powered_on=ps;}
bool  CES_Controller::get_power_state()         {return powered_on;}

void  CES_Controller::set_battery_charge(int bc){battery_charge = bc;}
int   CES_Controller::get_battery_charge()      {return battery_charge;}

void  CES_Controller::set_frequency(float f)    {frequency = f;}
float CES_Controller::get_frequency()           {return frequency;}

void  CES_Controller::set_current(int c)        {current = c;}
int   CES_Controller::get_current()             {return current;}

void  CES_Controller::set_treatment_time(int t) {treatment_time = t;}
int   CES_Controller::get_treatment_time()      {return treatment_time;}

void  CES_Controller::set_inactive_time(int t) {inactive_time = t;}
int   CES_Controller::get_inactive_time()      {return inactive_time;}

void  CES_Controller::set_contact_state(bool cs){electrode_skin_contact = cs;}
bool  CES_Controller::get_contact_state()       {return electrode_skin_contact;}

void  CES_Controller::set_fault_state(bool fs)  {internal_fault = fs;}
bool  CES_Controller::get_fault_state()          {return internal_fault;}

void  CES_Controller::set_lock_state(bool ls)   {settings_locked = ls;}
bool  CES_Controller::get_lock_state()          {return settings_locked;}


void  CES_Controller::set_record_state(bool rec)  {record = rec;}
bool  CES_Controller::get_record_state()          {return record;}


void  CES_Controller::shutdown(){
  powered_on = false;
  frequency  = 0.5f;
  current    = 0;
  electrode_skin_contact = false;
  settings_locked = false;
  treatment_time = 0;
}
