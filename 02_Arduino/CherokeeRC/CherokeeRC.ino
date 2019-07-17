
/**************************************************
 * Cherokee 4DW platform RC protocol PPM  
 * 
 * Version:   1.0
 * Author:    Andres Lopez (Argentina) 
*  Date:      July 2019
 * License:   MIT v2.0
 **************************************************/
 
// Conduction Mode 
#define MODE     0  // TODO>> 0: two RC joystick, 1: one RC joystick

// pins Cherokee motors
#define pM1_EN   4   
#define pM1_PWM  5  
#define pM2_PWM  6
#define pM2_EN   7   

// pins Channels RC
#define pCH1   22   
#define pCH2   24  
#define pCH3   26   
#define pCH4   28   
#define pCH5   30   
#define pCH6   32   

#include "src/Cherokee4WD.h"
#include "src/RCdecoder.h"

volatile int throttle;
volatile int direction;


//Intances def
Cherokee4WD truck;
RCdecoder rc;


/************************
 *        SETUP
 ***********************/
void setup ()
{
    Serial.begin (115200);
    truck.begin(pM1_EN, pM1_PWM, pM2_PWM, pM2_EN);
    rc.begin(pCH1, pCH2, pCH3, pCH4, pCH5, pCH6);

} // end setup


/************************
 *        LOOP
 ***********************/
void loop (){


      // On Off Truck from CH5 state
      if (!rc.stateChannel(pCH5)) {
          truck.stopMotors();
          return;
      }

      // PPM miliseconds   
      direction = rc.readChannel(pCH4);
      throttle = rc.readChannel(pCH3);

      // map speed and direction
      direction = rc.map_RCtimer(direction, 0, 256);
      throttle = rc.map_RCtimer(throttle, 0, 256);

      // move the DC motors from RC signal
      truck.move_RCtoDC(direction, throttle);


} // end loop
