#include<Wire.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;
WidgetMap myMap(V0);
WidgetLED led4(V4); 

unsigned int move_index = 1; 

char auth[] = "Paste_your_Authentication_Key_here";              
char ssid[] = "Enter_Wifi_SSID_Here";                                      
char pass[] = "Enter_Wifi_Password_Here";    

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Wire.requestFrom(2,30);
  String string,string1,string2,string3,string4,string5,string6;
  do
  {
    char c = Wire.read();
    string = string+c;
    string1 = string.substring(0,8);
    string2 = string.substring(9,17);
    string4 = string.substring(18,21);
    string5 = string.substring(22,25);
    string6 = string.substring(26,27);
    string3 = string.substring(28);
  } while (Wire.available());

  char buf1[10];
  char buf2[10];
  char buf3[10];
  char buf4[10];
  char buf5[10];
  char buf6[10];
  Serial.println(string);
  string1.toCharArray(buf1, 10);
  long lati = atol(buf1);
  Serial.println((lati*0.000001),6);
  string2.toCharArray(buf2, 10);
  long longi = atol(buf2);
  Serial.println((longi*0.000001),6);
  string3.toCharArray(buf3, 10);
  int Speed = atoi(buf3);
  int count = atoi(buf6);
  Serial.println(Speed);
  Blynk.virtualWrite(V1, String((lati*0.000001), 6));   
  Blynk.virtualWrite(V2, String((longi*0.000001), 6));
  myMap.location(move_index, (lati*0.000001), (longi*0.000001), "GPS_Location");
  Blynk.virtualWrite(V5, String(count));
  Blynk.virtualWrite(V3, String(Speed));

  string4.toCharArray(buf4, 10);
  string5.toCharArray(buf5, 10);
  string6.toCharArray(buf6,10);
  int Xaxis = atoi(buf4);
  int Yaxis = atoi(buf5);
  
  Serial.print("X-axis :");
  Serial.println(Xaxis);
  Serial.print("Y-axis :");
  Serial.println(Yaxis);
  Serial.println();

  if (Xaxis<=270 || Yaxis<=270 || Xaxis>=390 || Yaxis>=390)
  {
    led4.on();
    delay(1000);
    led4.off();
    delay(1000);
  }
  else
  {
    led4.off();
  }
  
}