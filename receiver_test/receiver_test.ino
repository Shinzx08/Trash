#include <ServoTimer2.h>

#include <RH_ASK.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>


ServoTimer2 myservo;


LiquidCrystal_I2C lcd(0x27,16,2);

RH_ASK driver;


const int IR = 4;
const int buzzer = 5;
const int LED = 13;
 const int PIR = 8;
float level1, level2, level3;
int display1, display2, display3;
float  quotient1,  quotient2,  quotient3;
int max = 120;
String str_cm1, str_cm2, str_cm3;
String str_out;
const int OPEN = 1500;
const int CLOSE = 750;
const int SERVO = 9;
#define BUFSIZE 9


void setup()
{
    Serial.begin(9600); 
    if (!driver.init()) {
         lcd.print("no radio");
    } 
    myservo.attach(9);
         lcd.init(); 
   lcd.backlight();
}


void loop()
{

if(digitalRead(PIR) == HIGH){
      myservo.write(1500);
     tone(buzzer, 500);
     delay(100);
     noTone(buzzer);
    }
if(digitalRead(PIR) == LOW){
      myservo.write(750);
     tone(buzzer, 500);
     delay(100);
     noTone(buzzer);
 }
 if(digitalRead(IR) == HIGH){
      myservo.write(750);
     tone(buzzer, 500);
     digitalWrite(LED, HIGH);
     delay(100);
     noTone(buzzer);
       digitalWrite(LED, LOW);
 }
    
    uint8_t buf[BUFSIZE];
    uint8_t buflen = sizeof(buf);

    buflen = BUFSIZE;
    if (driver.recv(buf, &buflen)) 
    str_out = String((char*)buf);

   for (int i = 0; i < str_out.length(); i++){
    if (str_out.substring(i, i+1) == ","){
      str_cm1 = str_out.substring(0, i);
       str_cm2 = str_out.substring(i+1);
        str_cm3 = str_out.substring(1,i);
        break;
        delay(100);
      }
    }

    level1 = str_cm1.toFloat();
        level2 = str_cm2.toFloat();
            level3 = str_cm3.toFloat();

  quotient1 = level1 / max;
  display1 = quotient1 * max;
  quotient2 = level2 / max;
  display2 = quotient2 * max;
  quotient3 = level3 / max;
  display3 = quotient3 * max;
  
    
     lcd.setCursor(0, 1);
    lcd.print("PAPER ");
    lcd.print(display1);
    lcd.print(" %       ");
    delay(1000);
    lcd.clear();
       lcd.setCursor(0, 1);
    lcd.print("PLASTIC ");
    lcd.print(display2);
    lcd.print(" %       ");
    delay(1000);
    lcd.clear();
       lcd.setCursor(0, 1);
    lcd.print("METAL ");
    lcd.print(display3);
    lcd.print(" %       ");
    delay(1000);
    lcd.clear();
    }
