#include <cy_serdebug.h>
#include <cy_serial.h>

const char *gc_hostname = "d1msr04t";

#include "cy_wifi.h"
#include "cy_ota.h"
#include "cy_mqtt.h"
#include <Ticker.h>
#include "cy_weather.h"
#include "sr04t_tools.h"

const char* mqtt_pubtopic = "ATSH28/AUSSEN/WATERLEVEL/1/value";

Ticker senstick;
boolean gv_senstick;

void do_senstick() {
  gv_senstick = true;
}

void setup() {
  cy_serial::start(__FILE__);

  wifi_init(gc_hostname);

  init_ota(gv_clientname);

  init_mqtt(gv_clientname);

  delay(1000);
  check_mqtt();
  delay(1000);

  init_sr04t();

  do_sensor();
  send_pub_vals();
  gv_senstick = false;
  senstick.attach(60, do_senstick);
}

void loop()
{

  if (gv_senstick == true) {
    do_sensor();

    send_pub_vals();

    gv_senstick = false;
  }

  check_ota();

  check_mqtt();

  delay(500);

}


void do_sensor() {

  get_sr04t();

}

void send_pub_vals() {
  send_val(3, gv_dist);

  char buffer[10];
  dtostrf(gv_dist, 0, 1, buffer);
  client.publish(mqtt_pubtopic, buffer, true);
}

