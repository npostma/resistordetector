#include "resistortypes.h"
#include "pitches.h"
#include "morse.h"
 
#define NUM_MEASURE_POINTS 4

int raw = 0;           
float Vin = 5.0;
float Vout = 0;        
float R2 = 0;          
float buffer = 0;    

float R_MEASURE[NUM_MEASURE_POINTS] = 
{
    100,      // A0
    1000,     // A1
    10000,    // A2
    100000    // A3
};

void setup()
{
  Serial.begin(9600);             

}

void loop()
{
    int detected_pin = -1;
    
    for(int i = 0; i < NUM_MEASURE_POINTS; i++) {
      R2 = measure(R_MEASURE[i], i);
      if(R2 != -1) {
        detected_pin = i;
        break;
      }
    }
    
    if(detected_pin == -1) {
        Serial.println("Ongeldige meting. Probeer een ander berijk");
        delay(200);
        return;
    }
       
    long R2_type;      
    float current_tolerance;    
    int num_found = 0;
    for(int i = 0; i < NUM_TOLARANCE_TYPES; i++) {
        int num = 0;
        current_tolerance = tolerance_types[i];
        R2_type = findResistor(current_tolerance, num);
        if(num != 0) {
            num_found = num;
            break;
        }
    }
    
    if(num_found == 0) {
      Serial.println("Weerstand kon niet bepaald worden");
      return;
    }

    Serial.print("On pin:");           
    Serial.print(detected_pin);         
    Serial.println(":");      
    
    Serial.print("\tVoltage: ");      
    Serial.println(Vout);      
    
    Serial.print("\tR2: ");           
    Serial.print(R2);               
    Serial.println(" Ohm");
    
    Serial.print("\tR2 type: ");            
    Serial.print(" [");      
    Serial.print(R2_type);  
    Serial.print("]");      
    Serial.println(" Ohm");
    
    Serial.print("\tTolerantie: ");           
    Serial.print(current_tolerance);     
    Serial.println("%");
    
    Serial.print("\tZekerheid: ");           
    Serial.print(100 / num_found);     
    Serial.println("%");
    
    
    long number = R2_type;
    int number_buffer[15] = { 0 };
    
    int counter = 0;
    
    // Nummer ophakken in losse cijfers.
    // En omdraaien zodat het in de goede volgorde afgespeeld kan worden
    while (number > 0)
    {
        int digit = number%10;
        number /= 10;
        
        number_buffer[counter]  = digit;
        counter++;
    }
    for(int i = counter-1; i >= 0; i--) {
      play(number_buffer[i]);
    }

    delay(1000);
  
}

long findResistor(float tolerance, int &num_found) {
  long R2_type_value = 0;
    for(int i = 0; i < NUM_RESISTORS_TYPES; i++) {
        long diff = resistor_types_tenth[i] - (R2 * 10);
        
        long th = ((float)resistor_types_tenth[i]  *  tolerance);
            
        // Type bepalen
        if(diff > -th && diff < th) {
            R2_type_value = resistor_types_tenth[i] / 10;
            num_found++;
        }
    } 
    return R2_type_value;
}

float measure(int r, int pin) 
{
  raw = analogRead(pin);    
  
  Vout = (5.0 / 1023.0) * raw;    // Bereken de voltage van de voltage verdeler
  
  if(Vout == 5) {
      return -1;
  }
  
  buffer = (Vin / Vout) - 1;
  return (r / buffer);
}

void play(int number) {
    // iterate over the notes of the melody:    
    for (int note_index = 0; note_index < NUMBER_LENGTH; note_index++) {
    
        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int note_duration = 1000 / number_durations[number][note_index];
        
        tone(8, NOTE_C6, note_duration);
    
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = note_duration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        Serial.println(digitalRead(8));
        noTone(8);
    }
    delay(250);
}
