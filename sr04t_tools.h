#include "MedianFilterLib.h"

float gv_dist;

int trigger = 5;
int echo = 4;

MedianFilter<float> medianFilter(30);


void init_sr04t() {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void get_sr04t() {
  long dauer = 0;
  long entfernung = 0;

  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer / 2) / 29.1;


  if (entfernung >= 200 || entfernung <= 0)
  {
    //   "Kein Messwert"
    entfernung = 250;
  }

  Serial.println(entfernung);
 // gv_dist = entfernung * -1;
  
  float median = medianFilter.AddValue(entfernung);
  Serial.println(median);
  gv_dist = median * -1;



}
