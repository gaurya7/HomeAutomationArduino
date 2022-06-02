#include <SoftwareSerial.h>
#include <Servo.h>
#include <String.h>

Servo myservo;
int pos = 0;
String lat = "52.6272690";
String lng = "-1.1526180";
SoftwareSerial sim800l(10, 11);// RX, TX
SoftwareSerial hc05(12, 13);// RX, TX
float sensorValue;
const int led = 22;
const int fan = 23; 
int buttonState = 0; 
float tempC; 
float tempCavg; 
int avgcount = 0;
String txt="";

char junk;
String inputString="";

void setup()
{
 
  pinMode(led, OUTPUT); 
  pinMode(fan, OUTPUT); 
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  //myservo.attach(7);
  sim800l.begin(9600);
  Serial.begin(9600);   
  hc05.begin(9600);
  delay(500);
  opendoor();
  closedoor();
  digitalWrite(led,LOW);
  //DialVoiceCall();
  //SendTextMessage();
  //sim800l.print("AT+CMGF=?\r"); // Set the shield to SMS mode
  sim800l.println();
  sim800l.println("ATI\r");
  sim800l.println();
  sim800l.println("AT+GSN\r");
  sim800l.println();
  sim800l.println("AT+GMM\r");
  sim800l.println();
  sim800l.println("AT+CMGF=1\r");
  sim800l.println();
  sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
  Serial.println("All Messages Deleted");
  sim800l.println();
  //sim800l.print("AT+CMGL=\"ALL\"\r");
  //sim800l.println();
  //sim800l.println("AT+CMGR=1,0\r");
  //sim800l.println();
  
  //myservo.write(0);
}
 
void loop()
{
  //Serial.println(pos);
  //myservo.write(pos);
  sim800l.println("AT+CMGR=1,0\r");
  sim800l.println();
  delay(100);

 

    //SendTextMessage(); 
  if(hc05.available())
  {
    while(hc05.available())
    {
      char inChar = (char)hc05.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    
    Serial.println(inputString);
    while (hc05.available() > 0)  
    { 
      junk = hc05.read() ; 
    }
    if(inputString == "a")
    {         //in case of 'a' turn the LED on
      digitalWrite(led,HIGH);
      Serial.println("Light Turned On");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }
    else if(inputString == "b")
    {   //incase of 'b' turn the LED on
      digitalWrite(led,LOW);
      Serial.println("Light Turned Off");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }
    else if(inputString == "c")
    {   //incase of 'a' turn the LED off
      digitalWrite(fan,HIGH);
      Serial.println("Fan Turned On");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }
    else if(inputString == "d")
    {   //incase of 'b' turn the LED off
      digitalWrite(fan,LOW);
      Serial.println("Fan Turned Off");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }
    else if(inputString == "e")
    {   //incase of 'b' turn the LED off
      opendoor();
      Serial.println("Opened Door");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }
    else if(inputString == "f")
    {   //incase of 'b' turn the LED off
      closedoor();
      Serial.println("Closed Door");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }
    else if(inputString == "g")
    {   //incase of 'b' turn the LED off
      //ac on
    }
    else if(inputString == "h")
    {   //incase of 'b' turn the LED off
      //ac off
    }
    else if(inputString == "i")
    {   //incase of 'b' turn the LED off
      //temp inc
    }
    else if(inputString == "j")
    {   //incase of 'b' turn the LED off
      //temp dec
    }
    inputString = "";
  }
 
  while (sim800l.available())
  { 
    //txt=txt+char(sim800l.read());
    //Serial.write(char(sim800l.read())); 
    txt.concat(char(sim800l.read()));
    //Serial.println(txt);
  }

  if(!sim800l.available())
  {
    
    //while (txt.indexOf("+CMGL", startIndex) != -1) 
    //{
    //  startIndex = txt.indexOf("+CMGL", startIndex) + 5;
    //  cmgl += 1;
    //}
    //Serial.println(cmgl);
    //Serial.println("SIM 800 Unavailable");
    //Serial.println(txt);
    int l1on = txt.indexOf("Light On");
    //Serial.println(z);
    if(l1on>=1)
    {
      l1on=-1;
      txt="";
      digitalWrite(led,HIGH);
      Serial.println("Lights Turned On");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }
    int l1off = txt.indexOf("Light Off");
    //Serial.println(z);
    if(l1off>=1)
    {
      l1off=-1;
      txt="";
      digitalWrite(led,LOW);
      Serial.println("Light Turned Off");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }

    int od = txt.indexOf("Open Door");
    //Serial.println(z);
    if(od>=1)
    {
      od=-1;
      txt="";
      opendoor();
      Serial.println("Opened Door");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }

    int cd = txt.indexOf("Close Door");
    //Serial.println(z);
    if(cd>=1)
    {
      cd=-1;
      txt="";
      closedoor();
      Serial.println("Closed Door");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }

    int fon = txt.indexOf("Fan On");
    //Serial.println(z);
    if(fon>=1)
    {
      fon=-1;
      txt="";
      digitalWrite(fan,HIGH);
      Serial.println("Fan Turned On");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }

    int foff = txt.indexOf("Fan Off");
    //Serial.println(z);
    if(foff>=1)
    {
      foff=-1;
      txt="";
      digitalWrite(fan,LOW);
      Serial.println("Fan Turned Off");
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }

    /*if(txt="")
    {
      sim800l.print("AT+CMGDA=\"DEL ALL\"\r");
      Serial.println("All Messages Deleted");
      sim800l.println();
    }*/
    //delay(1000);
  }
  
}
 
void SendTextMessage()
{
  Serial.println("Sending Text...");
  sim800l.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
 
  sim800l.print("AT+CMGS=\"+919029791995\"\r");  
  delay(200);
//  sim800l.print("http://maps.google.com/?q=");
//  sim800l.print(lat);
//  sim800l.print(",");
//  sim800l.print(lng);
  sim800l.print("Auduino GSM Test");
  sim800l.print(tempCavg);
  sim800l.print(" degrees C");
  sim800l.print("\r"); //the content of the message
  delay(500);
  sim800l.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  sim800l.println();
  Serial.println("Text Sent.");
   delay(500);
    tempCavg = 0;
    avgcount = 0;
}
 
void DialVoiceCall()
{
  sim800l.println("AT");//dial the number, must include country code
  sim800l.println("ATD+919029791995");//dial the number, must include country code
  delay(100);
  sim800l.println();
}

void opendoor()
{
  myservo.attach(7);
  for (pos = 0; pos < 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  
  }
  myservo.detach();
}

void closedoor()
{
  myservo.attach(7);
  for (pos = 90; pos > 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

