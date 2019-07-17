/*********************************************
 * Cherokee4WD Hardware definition
 * Author: 	Andres Lopez
 * Version:	1.0 (july 2019)
 * License: 	MIT v2.0
 *********************************************/

#ifndef _Cherokee4WD_h
#define _Cherokee4WD_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


class Cherokee4WD
{
  public:   Cherokee4WD();                    // Constructor
            void begin(int M1_EN=4, int M1_PWM=5, int M2_PWM=6, int M2_EN=7);
            void move_RCtoDC(int direction, int throttle);
            void updateMotorSpeed(int motor, int speed);
            void stopMotors();

  private:
            int _M1_EN; int _M1_PWM;
            int _M2_EN; int _M2_PWM;
            int _speed=0;
  
};

#endif // end _Cherokee4WD_h
