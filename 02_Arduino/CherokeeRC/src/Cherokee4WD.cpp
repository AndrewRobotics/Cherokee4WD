/*********************************************
 * Cherokee4WD Hardware definition
 * Author: 	Andres Lopez
 * Version:	1.0 (july 2019)
 * License: 	MIT v2.0
 *********************************************/

#define   M1              0       // Motor 1
#define   M2              1       // Motor 2
#define   TOLERANCE       50      // 

#include  "Cherokee4WD.h"

//Constructor
Cherokee4WD::Cherokee4WD(){}

//APIs
void Cherokee4WD::begin(int M1_EN, int M1_PWM, int M2_PWM, int M2_EN)
{
    _M1_EN = M1_EN;
    _M1_PWM = M1_PWM;
    _M2_PWM = M2_PWM;
    _M2_EN = M2_EN;

    pinMode(_M1_EN, OUTPUT);        // output pins def
    pinMode(_M1_PWM, OUTPUT);
    pinMode(_M2_PWM, OUTPUT);
    pinMode(_M2_EN, OUTPUT);
}


/**********************************************************************
 * move from Radio control signal (servo motor-PPM) to DC motors (PWM)
**********************************************************************/
void Cherokee4WD::move_RCtoDC(int direction, int throttle)
{
    // M1 Motor
    // cólculo de la velocidad y dirección segun ancho del PPM del RC
    _speed = 2*(throttle-(128-direction))-256;
    //_speed = 2*(throttle-dirirection);
    updateMotorSpeed(M1, _speed);

    // M2 Motor
    _speed = 2*(throttle+(128-direction))-256;
    //_speed = 2*(throttle+dirirection)-512;
    updateMotorSpeed(M2, _speed);
}


/**********************************************************************
 * Update PWM signal for each truck's DC motor
**********************************************************************/
void Cherokee4WD::updateMotorSpeed(int motor, int speed)
{
  // Filtro de vibración en stop y filtro de rango valido -255 < speed < 255
  _speed = abs(_speed) < TOLERANCE ? 0 : _speed;
  _speed = ((_speed < -255) ? -255 : ((_speed > 255) ? 255 : _speed));


  // depend of speed sign:
  // move forward
  if (_speed >= 0){
      if (motor == M1) {
        digitalWrite(_M1_EN, LOW);
      }else{
        digitalWrite(_M2_EN, LOW);
      }
  }

  // move backward
  if (_speed < 0){
      if (motor == M1) {
        digitalWrite(_M1_EN, HIGH);
      }else{
         digitalWrite(_M2_EN, HIGH);
      }
  }

  // update PWMs signal depend of motor select
  if (motor == M1) {
        analogWrite(_M1_PWM, abs(_speed));
      }else{
        analogWrite(_M2_PWM, abs(_speed));
      }

} // end updateMotorSpeed


/**********************************************************************
 * Stop all motors
**********************************************************************/
void Cherokee4WD::stopMotors()
{
  digitalWrite(_M1_EN,LOW);
  digitalWrite(_M1_PWM,LOW);
  digitalWrite(_M2_PWM,LOW);
  digitalWrite(_M2_EN,LOW);
}
