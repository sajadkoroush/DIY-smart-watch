#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "SSD1306.h" 
#include <Adafruit_GFX.h>
#include "images.h"

const char* ssid = "kharazmi";
const char* password = "kharazmi12345678";
WiFiServer server(70);

IPAddress ips(192, 168, 1, 70);
IPAddress gate(192, 168, 1, 1);
IPAddress sub(255, 255, 255, 0);

SSD1306  display(0x3c, D4, D5);

String txt;
String txt2;
char c;
long int n = -1;
boolean k = false;
String txt_s;
char c_s;
long int n_s = -1;
long int IBI = 0;
long int BPM = 0;
IPAddress myIP;
String ip = "ip";
int r[] { 1 , 2 , 3 , 4 ,5 ,6 , 7 ,8 ,9,10,11,12,13,14,15}; 
int numx[] = {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };



const int WIDTH = 128;
const int HEIGHT = 64;
const int LENGTH = WIDTH;


void ser() {
  txt_s = "";
  n_s = -1;
}

void setup() {
  Serial.begin(115200);
  
   display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  WiFi.config(ips, gate, sub);
  WiFi.begin(ssid, password);
  
   display.clear();
  while (WiFi.status() != WL_CONNECTED) {
  for (int i = 0; i < 100; i++)
  {
    display.drawProgressBar(0, 32, 120, 10, i);
    display.drawString(30, 20, "CONNECTING");
    
    display.display();
    delay(20);
    if(WiFi.status() == WL_CONNECTED){
      break;
    }
  }
  }
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

// Display
// progress
  display.clear();
  for (int i = 0; i < 100; i++)
  {
    display.drawProgressBar(0, 32, 120, 10, i);
    display.drawString(30, 20, "LOADING...");
    display.display();
    delay(50);
  }
  display.clear();
  display.display();
  delay(500);
  display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  display.display();
  delay(3000);
  display.clear();

  myIP = WiFi.localIP();
  ip = myIP[0];
  ip += ".";
  ip += myIP[1];
  ip += ".";
  ip += myIP[2];
  ip += ".";
  ip += myIP[3];

  display.drawString(30, 20, ip);
  display.display();
  delay(3000);

  Serial.println("start");


  
}

void loop() {
  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  Serial.println("new Client");
  while (client.connected() == true) {
    while (Serial.available() > 0) {
      c_s = Serial.read();
      txt_s += c_s;
           n_s = c_s;
     //      delay(10);
    }
 
int v = sizeof(numx) /4;


  if (txt_s.indexOf("x") != -1)
  {
 txt = String(numx[0]) + " ," ;
txt += String(numx[1]) + " ," ;
txt += String(numx[2]) + " ," ;
 txt += String(numx[3]) + " ," ;
 txt += String(numx[4]) + " ," ;
txt += String(numx[5]) + " ," ;
txt += String(numx[6]) + " ," ;
 txt += String(numx[7]) + " ," ;
txt += String(numx[8]) + " ," ;
 txt += String(numx[9]) + " ," ;
 txt += String(numx[10]) + " ," ;
txt += String(numx[11]) + " ," ;
txt += String(numx[12]) + " ," ;
 txt += String(numx[13]) + " ," ;
 txt += String(numx[14]) + " ," ;

 
    client.println(txt);
    client.print(String(IBI) + "_WI ");
    client.print(String(BPM) + "_YB");
  ser();
  client.println("");
  }



while (Serial.available() > 0) {
      c_s = Serial.read();
      txt_s += c_s;
           n_s = c_s;
 //          delay(10);
    }
    
  if(txt_s.indexOf("_a") != -1){
      txt_s.replace("_a" , "");
    numx[0] = txt_s.toInt();
     txt_s.replace(String(numx[0]),"");
  }
if(txt_s.indexOf("_b") != -1){
  txt_s.replace("_b" , "");
    numx[1] = txt_s.toInt();
        txt_s.replace(String(numx[1]),"");
  }
if(txt_s.indexOf("_c") != -1){
    txt_s.replace("_c" , "");
    numx[2] = txt_s.toInt();
    txt_s.replace(String(numx[2]),"");
  }
  if(txt_s.indexOf("_d") != -1){
    txt_s.replace("_d" , "");
    numx[3] = txt_s.toInt();
    txt_s.replace(String(numx[3]),"");
  }
 if(txt_s.indexOf("_e") != -1){
    txt_s.replace("_e" , "");
    numx[4] = txt_s.toInt();
    txt_s.replace(String(numx[4]),"");
  }
  
if(txt_s.indexOf("_f") != -1){
    txt_s.replace("_f" , "");
    numx[5] = txt_s.toInt();
    txt_s.replace(String(numx[5]),"");
  }
if(txt_s.indexOf("_g") != -1){
    txt_s.replace("_g" , "");
    numx[6] = txt_s.toInt();
    txt_s.replace(String(numx[6]),"");
  }
  if(txt_s.indexOf("_h") != -1){
    txt_s.replace("_h" , "");
    numx[7] = txt_s.toInt();
    txt_s.replace(String(numx[7]),"");
  }
  if(txt_s.indexOf("_i") != -1){
    txt_s.replace("_i" , "");
    numx[8] = txt_s.toInt();
    txt_s.replace(String(numx[8]),"");
  }
  if(txt_s.indexOf("_j") != -1){
    txt_s.replace("_j" , "");
    numx[9] = txt_s.toInt();
    txt_s.replace(String(numx[9]),"");
  }
if(txt_s.indexOf("_k") != -1){
    txt_s.replace("_k" , "");
    numx[10] = txt_s.toInt();
    txt_s.replace(String(numx[10]),"");
  }
if(txt_s.indexOf("_l") != -1){
    txt_s.replace("_l" , "");
    numx[11] = txt_s.toInt();
    txt_s.replace(String(numx[11]),"");
  }
  if(txt_s.indexOf("_m") != -1){
    txt_s.replace("_m" , "");
    numx[12] = txt_s.toInt();
    txt_s.replace(String(numx[12]),"");
  }
if(txt_s.indexOf("_n") != -1){
    txt_s.replace("_n" , "");
    numx[13] = txt_s.toInt();
    txt_s.replace(String(numx[13]),"");
  }
  if(txt_s.indexOf("_o") != -1){
    txt_s.replace("_o" , "");
    numx[14] = txt_s.toInt();
    txt_s.replace(String(numx[14]),"");
  }
  if(txt_s.indexOf("_WI") != -1){
    txt_s.replace("_WI" , "");
    IBI = txt_s.toInt();
    txt_s.replace(String(IBI),"");
  }
  if(txt_s.indexOf("_YB") != -1){
    txt_s.replace("_YB" , "");
    BPM = txt_s.toInt();
    txt_s.replace(String(BPM),"");
  }
displays();



  }
}
void displays(){
       display.clear();
 display.drawLine(30, 12, 121, 12);
  display.drawLine(30, 38, 121, 38);

  display.drawString(30, 13, "BPM = ");
  display.drawString(76, 13, String(BPM));
  display.drawString(30, 25, " IBI = ");
  display.drawString(76, 25, String(IBI));

  display.drawString(30, 40, "System =");
  display.drawString(76, 40, " online");
r[0] = map(numx[0], 0, 1021, 0, 64);
r[1] = map(numx[1], 0, 1021, 0, 64);
r[2] = map(numx[2], 0, 1021, 0, 64);
r[3] = map(numx[3], 0, 1021, 0, 64);
r[4] = map(numx[4], 0, 1021, 0, 64);
r[5] = map(numx[5], 0, 1021, 0, 64);
r[6] = map(numx[6], 0, 1021, 0, 64);
r[7] = map(numx[7], 0, 1021, 0, 64);
r[8] = map(numx[8], 0, 1021, 0, 64);
r[9] = map(numx[9], 0, 1021, 0, 64);
r[10] = map(numx[10], 0, 1021, 0, 64);
r[11] = map(numx[11], 0, 1021, 0, 64);
r[12] = map(numx[12], 0, 1021, 0, 64);
r[13] = map(numx[13], 0, 1021, 0, 64);
r[14] = map(numx[14], 0, 1021, 0, 64);

  display.fillRect(1, 64 - r[0], 1, 64);
  display.fillRect(2, 64 - r[1], 1, 64);
  display.fillRect(3, 64 - r[2], 1, 64);
  display.fillRect(4, 64 - r[3], 1, 64);
  display.fillRect(5, 64 - r[4], 1, 64);
  display.fillRect(6, 64 - r[5], 1, 64);
  display.fillRect(7, 64 - r[6], 1, 64);
  display.fillRect(8, 64 - r[7], 1, 64);
  display.fillRect(9, 64 - r[8], 1, 64);
  display.fillRect(10, 64 - r[9], 1, 64);
  display.fillRect(11, 64 - r[10], 1, 64);
  display.fillRect(12, 64 - r[11], 1, 64);
  display.fillRect(13, 64 - r[12], 1, 64);
  display.fillRect(11, 64 - r[13], 1, 64);
  display.fillRect(15, 64 - r[14], 1, 64);

  display.display();
}

