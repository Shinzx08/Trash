#include <Ultrasonic.h>
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif


Ultrasonic ultrasonic1(3,2);
Ultrasonic ultrasonic2(7,6);
Ultrasonic ultrasonic3(9,8);

float uno, dos, tres;

String str_cm1, str_cm2, str_cm3;
String str_out;
//RH_ASK driver;
RH_ASK driver(2000, 4, 5, 0); // ESP8266 or ESP32: do not use pin 11 or 2
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 


void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);    // Debugging only
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
  ;
#endif
}

void loop()
{
 uno = ultrasonic1.read(CM);
  str_cm1 = String(uno);
  dos = ultrasonic2.read(CM);
   str_cm2 = String(dos);
  tres = ultrasonic3.read(CM);
      str_cm3 = String(tres);

str_out = str_cm1 + "," + str_cm2 + "," + str_cm3;
  
  const char *msg = str_out.c_str();

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(500);
}
