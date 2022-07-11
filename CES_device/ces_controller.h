#ifndef CES_CONTROLLER_H
#define CES_CONTROLLER_H

class CES_Controller
{

public:
  CES_Controller();
  ~CES_Controller();
  //power_state --> powered_on
  void  set_power_state(bool);
  bool  get_power_state();

  //battery charge
  void  set_battery_charge(int);
  int   get_battery_charge();

  //frequency
  void  set_frequency(float);
  float get_frequency();

  //current
  void  set_current(int);
  int   get_current();

  //treatment --> treatment_time
  void  set_treatment_time(int);
  int   get_treatment_time();

  //inactive time
  void  set_inactive_time(int);
  int   get_inactive_time();

  //contact state -> electrode_skin_contact
  void  set_contact_state(bool);
  bool  get_contact_state();

  //fault state
  void  set_fault_state(bool);
  bool  get_fault_state();

  //lock state --> settings_locked
  void  set_lock_state(bool);
  bool  get_lock_state();

  //record state
  void  set_record_state(bool);
  bool  get_record_state();

  void  shutdown();

protected:

private:
  //initialized as             -->
  bool  settings_locked;           //false
  bool  internal_fault;            //false
  bool  electrode_skin_contact;    //false
  bool  powered_on;                //false
  bool  record;                    //false
  int   treatment_time;            //0
  int   inactive_time;             //1800 = 30 mins
  int   current;                   //0
  float frequency;                 //0.5f
  int   battery_charge;            //100
};

#endif // CES_CONTROLLER_H
