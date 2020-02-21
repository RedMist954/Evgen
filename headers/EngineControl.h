#pragma once
#include "Arduino.h"
#include "GyverPID"

class E_control {
  public:

          double angleSpeed = 0;                                                 //угловая скорость колеса в ридан/с
          double distans = 0;                                                    //пройденное расстояние (считается по тикам, доверять не стоит) в м
          double linearSpeed = 0;                                                //линейная скорость в м/c

          explicit E_control(int new_CONTROL_PIN = 0, int new_GRIN_PIN = 0, unsigned long new_dt = 20000, bool new_mode = 1, double new_R = 0.041, double new_turnoverTick = 374);
          void scoreTickes();
          double angleSpeedCalc();
          double distansCalc();
          double linearSpeedCalc();
 	  void PWM_Control(double requestSpeed);				 //функция формирующая шим сигнал для достижения заданного значения угловой скорости

          GyverPID enginePID();
  	  long tickes = 0;   		                                         //тики энкодера

  private:

          int CONTROL_PIN;                                                	 //пин с которого осуществляется управление двигателем
          int GRIN_PIN;                                                          //пин второго энкодера (предполагается, что для прерывания используется зеленый провод), не вводить если не используется
          unsigned long _dt;                                                     //дельта времени через которую производится расчет скорости
          bool _mode;                                                            //0 - направление вращения колеса не учитывается, 1 - направление учитывается
          double R;                                                              //радиус колеса
          double turnoverTick;                                                   //количество тиков на оборот колеса
          unsigned long engineTimer = 0;                                         //служебная информация для нахождения делта времени
          long lastTickes = 0;                                                   //служебная информация для нахождения делта тиков за время дельта
};
