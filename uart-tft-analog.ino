#include <SoftwareSerial.h>
//2015-09-funguje
//defa *** 1M 


const int rx=1; //2 na TX
const int tx=0; //1 spojeno s RX
int sensorPin = 3;
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue1 = 0;  
int sensorValue2 = 0;   
int sensorValue3 = 0;
int sensorValue4 = 0;

SoftwareSerial mySerial(rx,tx);
int i=0;
char buf[12];
int cnt=0;

int gzero,gdiv,gmult, h1, gdelay;
int gtimediv = 10;

void setup() 
{ 
pinMode(rx,INPUT);
pinMode(tx,OUTPUT);
mySerial.begin(9600);

gzero = 300;
gdiv = 2;  //10
gmult = 64;
gdelay = 6000;

mySerial.println("C");
delay(3000); 
mySerial.println("C");
delay(5000);
mySerial.println("C");
mySerial.println("Qvoltmeter 12V - graf*");
delay(1000); 


//mySerial.println("h30");
mySerial.println("h220");

mySerial.println("W7");
mySerial.println("v60");
mySerial.println("v120");
delay(100);
mySerial.println("v180");
mySerial.println("v240");
delay(100);
mySerial.println("v300");


for (int hv=10; hv<15; hv++)
{
  mySerial.println("h");
  h1 = num2gr(hv);
  mySerial.println(h1);
  delay(100);}

mySerial.println("W2");
mySerial.println("v144");
mySerial.println("v288");
mySerial.print("R9Qoctopusengine.org*");
mySerial.print("R0");

mySerial.print("h");
h1 = num2gr(12);
mySerial.println(h1);
delay(100);




mySerial.println("W1");


} 

void loop() 
{  
sensorValue1 = analogRead(sensorPin);
delay(10);
sensorValue2 = analogRead(sensorPin);
delay(10);
sensorValue3 = analogRead(sensorPin);
delay(10);
sensorValue4 = analogRead(sensorPin);

sensorValue = (sensorValue1 +sensorValue2+sensorValue3 +sensorValue4)/4;
float voltage = sensorValue * (5.0 / 1023.0);
//mySerial.println(voltage);  

delay(100); 
  
/*
mySerial.println(buf[i]);   
if (int(buf[i])==13 || int(buf[i])==10 )
  { //If Carriage return has been reached
  mySerial.println(buf);
  for(int x=0;x<=10;x++){buf[x]=' ';}
  i=0; //start over again
  } //if enter
  i++; 
} //If mySerial.available
*/

cnt++;
//mySerial.println("C");
mySerial.print("Q");
mySerial.print(cnt);
mySerial.print(": ");
mySerial.print(voltage);
float voltage12 =  voltage*2.85;
mySerial.print("V ---> ");
mySerial.print(voltage12);

mySerial.print("V*");
mySerial.println("W7");
delay(100); 
mySerial.print("P");
mySerial.print(cnt/gtimediv);
mySerial.print(",");
int gr = num2gr(voltage12);
mySerial.print(gr);

mySerial.println("W2");
delay(100); 
mySerial.print("P");
mySerial.print(cnt/gtimediv/10);
mySerial.print(",");
gr = num2gr(voltage12);
mySerial.print(gr);


delay(gdelay-250); 


}//LOOP

//--------------------------
int num2gr(float num) {
  float gf = gzero-(float(num-6 )/gdiv)*gmult;
  int gr = int(gf);
  return gr;
} 




