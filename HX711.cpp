#include <Arduino.h>
#include "HX711.h"

HX711::HX711(byte dout, byte pd_sck) {
  begin(dout, pd_sck);
}

HX711::HX711() {
}

void HX711::begin(byte dout, byte pd_sck) {
  PD_SCK = pd_sck;
  DOUT = dout;

  pinMode(PD_SCK, OUTPUT);
  pinMode(DOUT, INPUT);

  value_Raw = read();
  value_LPF = value_Raw;
  tare();
}

long HX711::read() {
  byte data[3];

  // wait until there is data on DOUT
  while (digitalRead(DOUT))
    ;

  // read the 24 bits from DOUT
  // starting with the most significant bit
  for (int j = 2; j >= 0; j--)
  {
    for (char i = 7; i >= 0; i--)
    {
      digitalWrite(PD_SCK, HIGH);
      bitWrite(data[j], i, digitalRead(DOUT));
      digitalWrite(PD_SCK, LOW);
    }
  }

  // set DOUT of the chip back to high
  digitalWrite(PD_SCK, HIGH);
  digitalWrite(PD_SCK, LOW);

  // the hx711 sends 0x80 for MIN value
  // in this case we set data to 0
  data[2] ^= 0x80;

  value_Raw = ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8)
              | (uint32_t) data[0];
  return value_Raw;
}

long HX711::read_LPF() {
  value_Raw = read();
  value_LPF = 0.65 * value_LPF + 0.35 * value_Raw;
  return value_LPF;
}

long HX711::read_average(byte times) {
  long sum = 0;
  for (byte i = 0; i < times; i++) sum += read();
  return sum / times;
}

float HX711::get_in_units() {
  long val = read_LPF() - OFFSET;
  return (float) val / SCALE;
}

void HX711::set_offset(long offset) {
  OFFSET = offset;
}

long HX711::get_offset() {
  return OFFSET;
}

void HX711::tare(byte times) {
  double avg = read_average(times);
  set_offset(avg);
}

void HX711::set_scale(float scale) {
  SCALE = scale;
}

float HX711::get_scale() {
  return SCALE;
}
