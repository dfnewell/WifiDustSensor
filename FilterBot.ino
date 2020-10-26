/*
  EchoBot

  This example shows how to program a Telegram Bot
  that echoes your messages.

  For a step-by-step tutorial visit:
  https://create.arduino.cc/projecthub/Arduino_Genuino/telegram-bot-library-ced4d4

  In oreder to make the bot more reliable in the long run we suggest using a watchdog
  The Adafruit_SleepyDog is a handy library that will reset the board if something goes wrong

  Updated 29 May 2016
  by Tommaso Laterza
  Updated 13 February 2018
  by Tommaso Laterza

  This example code is in the public domain.

*/

#include "arduino_secrets.h"
#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h> 
#include <Adafruit_SleepyDog.h>
#define ANALOG_VOLTAGE 3.3 // analog top of range         

const int ledPin = 5;                                            //drive the led of sensor
const int dustPin = A0;                                            //analog input

unsigned long time_now;
float density, voltage;
bool trigger;

// Initialize Wifi connection to the router
char ssid[] = SECRET_SSID;             // your network SSID (name)
char pass[] = SECRET_PASS;           // your network key

// Initialize Telegram BOT
const char BotToken[] = SECRET_BOT_TOKEN;
const char MessageID[] = SECRET_MESSAGE_ID;

WiFiSSLClient client;
TelegramBot bot (BotToken, client);

int Filter(int m)
{
  static int flag_first = 0, _buff[10], sum;
  const int _buff_max = 10;
  int i;
  
  if(flag_first == 0)
  {
    flag_first = 1;

    for(i = 0, sum = 0; i < _buff_max; i++)
    {
      _buff[i] = m;
      sum += _buff[i];
    }
    return m;
  }
  else
  {
    sum -= _buff[0];
    for(i = 0; i < (_buff_max - 1); i++)
    {
      _buff[i] = _buff[i + 1];
    }
    _buff[9] = m;
    sum += _buff[9];
    
    i = sum / 10.0;
    return i;
  }
}

void setup() {

  time_now = 0;
  Serial.begin(115200);
  delay(100);
  pinMode(ledPin, OUTPUT);
  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");

  bot.begin();
  //Watchdog.enable(10000); // Timer set to 10 sec;
}

void loop() {
  digitalWrite(ledPin,LOW);
  delayMicroseconds(280);
  voltage = analogRead(dustPin);
  delay(1);
  digitalWrite(ledPin,HIGH);
  voltage = Filter(voltage);
/*if(micros()-time_now > period1)
  {
  digitalWrite(iled,HIGH);
  Serial.println("On");
  if ((micros()%period1)-time_now > period2)
     { 
      adcvalue = analogRead(vout);
      digitalWrite(iled,LOW);
      Serial.println("Off");
      time_now = micros();*/
  voltage = (voltage / 1023.0) * ANALOG_VOLTAGE;
  density = 1000*0.18*voltage;
  Serial.print("Voltage = ");
  Serial.print(voltage);
  Serial.print(",\tDust Density = ");
  Serial.print(density);
  Serial.println(" ug/m3");
  delay(1000);
//Watchdog.reset(); //if function is not called in 10 sec, the board will reset itself
if (density > 115 && !trigger)
  {
    bot.sendMessage(MessageID, "It's dusty! Turn on the filter.");
    trigger = 1;
  }
if (millis()-time_now == 120000)
  {
    trigger = 0;
    time_now = millis();
  }
  delay(1000);
}
