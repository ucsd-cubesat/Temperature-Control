
/********************************************************************/
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 


double Setpoint ; // will be the desired value
double Input; // Temperature
double Output ; //LED
double Celsius;
double error; 
int Valve; // 0 off, 1 on for serial monitor
 
void setup()
{
  Serial.begin(9600);   

  Setpoint = 24;  //Target temperature to maintain, in 'C
  error = 1;      // Valve turn on at setpoint+error, turn off at setpoint-error, in 'C


  Setpoint = Setpoint*16; // 16 per 1 C  (e.g. 25'C = 16*25 = 400, -51.1111'C = -818)
  error = error*16; // 16 per 1 C
  pinMode(3,OUTPUT);
}
 
void loop()
{
  sensors.requestTemperatures(); 
  Celsius = sensors.getTempCByIndex(0);
  Input = Celsius*16;
 
 if (Input > (Setpoint + error)){
  digitalWrite(3,HIGH);
  Valve = 1;
 }
 else if (Input < (Setpoint - error) && (Valve == 1)) {
  digitalWrite(3,LOW);
  Valve = 0;
  //delay(2000); // To avoid rapid turn on / turn off
 }  

  
  Serial.print("TEMP: ");
  Serial.print(Celsius);
  Serial.print(" Valve: ");
  Serial.print(Valve);
  Serial.print(" Setpoint + error: ");  
  Serial.println(Setpoint/16);
  Serial.println(Setpoint/16 + error/16);
  Serial.println(Setpoint/16 - error/16);

}
