/*********************************************
 * Decoder PPM from RC 2.4GHz
 * Author: 	Andres Lopez
 * Version:	1.0 (july 2019)
 * License: 	MIT v2.0
 *********************************************/

 #include "RCdecoder.h"


 #define   IN_MIN              1100    // min pulse PPM[channel] in mills
 #define   IN_MAX              2000    // max pulse PPM[channel] in mills
 #define   TIMEOUT             4000    // timeout pulseIn


//Constructor
RCdecoder::RCdecoder(){}

//APIs
void RCdecoder::begin(int ch1, int ch2, int ch3, int ch4, int ch5, int ch6)
{
    if (ch1 > 0) pinMode(ch1, INPUT);
    if (ch2 > 0) pinMode(ch2, INPUT);
    if (ch3 > 0) pinMode(ch3, INPUT);
    if (ch4 > 0) pinMode(ch4, INPUT);
    if (ch5 > 0) pinMode(ch5, INPUT);
    if (ch6 > 0) pinMode(ch6, INPUT);
}


// read timing PPM channel
int RCdecoder::readChannel(int channel)
{
    if (pulseIn(channel, HIGH) > TIMEOUT); // syncro wait
    return  pulseIn(channel, HIGH);
}

// read timing PPM channel and return the logic state
bool RCdecoder::stateChannel(int channel)
{
    value = readChannel(channel);
    value = map_RCtimer(value, 0, 256);
    return value < 100 ? false : true;
}



// map signal to new range
long int RCdecoder::map_RCtimer(long int x, long int out_min, long int out_max)
{
  return (x - IN_MIN) * (out_max - out_min) / (IN_MAX - IN_MIN) + out_min;
}
