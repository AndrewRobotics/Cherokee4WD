/*********************************************
 * Decoder PPM from RC 2.4GHz
 * Author: 	Andres Lopez
 * Version:	1.0 (july 2019)
 * License: 	MIT v2.0
 *********************************************/

#ifndef _RCdecoder_h
#define _RCdecoder_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


class RCdecoder
{
  public:   RCdecoder();      // Constructor
            void begin(int ch1=0, int ch2=0, int ch3=0, int ch4=0, int ch5=0, int ch6=0);
            int readChannel(int Channel);
            long int map_RCtimer(long int x, long int out_min, long int out_max);
            bool stateChannel(int channel);
  private:
            int pinChannel[6];
            int value;

};

#endif // _RCdecoder_h
