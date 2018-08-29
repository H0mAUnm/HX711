#include "HX711.h"

HX711 loadcell;

void setup() {
  Serial.begin(2000000);

  // HX711.DOUT  - pin #A1
  // HX711.PD_SCK - pin #A0
  loadcell.begin(A1, A0);
  loadcell.set_scale(2280.f);

}


void loop() {
//  loadcell.read_LPF();
//  Serial.print(loadcell.value_Raw);
//  Serial.print(",");
//  Serial.println(loadcell.value_LPF);

  Serial.println(loadcell.get_in_units());
}

