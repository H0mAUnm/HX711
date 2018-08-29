#ifndef HX711_h
#define HX711_h

#include "Arduino.h"

class HX711
{
  private:
    byte PD_SCK;	// Power Down and Serial Clock Input Pin
    byte DOUT;		// Serial Data Output Pin
    long OFFSET = 0;	// used for tare weight
    float SCALE = 1;	// used to return weight in grams, kg, ounces, whatever


  public:
    long value_LPF;
    long value_Raw;
  
    HX711(byte dout, byte pd_sck);
    HX711();
    void begin(byte dout, byte pd_sck);
    long read();
    long read_LPF();
    long read_average(byte times = 10);
    float get_in_units();
    void set_offset(long offset = 0);
    long get_offset();
    void tare(byte times = 15);
    void set_scale(float scale = 1.f);
    float get_scale();

};

#endif /* HX711_h */
