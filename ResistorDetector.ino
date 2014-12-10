#include "resistortypes.h"

int analogPin = 0;     // Pin waar de voltage verdeler uitlezen

int raw = 0;           
int Vin = 5;

float Vout = 0;        
float R1 = 100;        
float R2 = 0;          
float buffer = 0;      


void setup()
{
  Serial.begin(9600);             

}

void loop()
{
  raw = analogRead(analogPin);    
  
  Vout = (5.0 / 1023.0) * raw;    // Bereken de voltage van de voltage verdeler
  
  buffer = (Vin / Vout) - 1;
  R2 = (R1 / buffer);
  
  int R2_type = 0;
  for(int i = 0; i < 45; i++) {
    int diff = resistor_types_tenth[i] - (R2 * 10);
    
    // Threashold is 10% van het type. Standaard gouden ring. TODO: variabel maken omdat er ook weerstanden zijn met preciecie van 1%, 2%, 5%, 20% 
    int th = resistor_types_tenth[i]  * 0.1;
    // Type bepalen
    if(diff > -th && diff < th) {
        R2_type = resistor_types_tenth[i] / 10;
    }
  } 
  
  Serial.print("Voltage: ");      //
  Serial.println(Vout);           // Outputs the information
  Serial.print("R2: ");           //
  Serial.print(R2);               //
  Serial.println("Ohm");
  Serial.print("R2 type: ");      //
  Serial.print(R2_type);          //
  Serial.println("Ohm");
  delay(1000);
}
