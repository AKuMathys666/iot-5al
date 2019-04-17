// Adafruit_DHT library
#include "DHT.h"

// Declaration input pin
#define DHTPIN 5 //Temperature+Humidity//

// Initialisation capteur
#define DHTTYPE DHT11   // DHT 11
#define Digital_polution A0 //polution
DHT dht(DHTPIN, DHTTYPE);

const int but_pin = D5;

void setup() {
  pinMode(but_pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
 
  // demare les mesures
  dht.begin();
}

void loop() {
  buttonToggleLed();
  delay(100);
  if (digitalRead(LED_BUILTIN) != 1) {
    //humidity
    float h = dht.readHumidity();
    //temperature
    float t = dht.readTemperature();
    //pollution//Digital_polution/10 > 75 = aie
    float p = analogRead (Digital_polution)/10;
     
    // affiché qu'il y a une erreur si une des valeur n'est pas présente
    if (isnan(h) || isnan(t)) {
      Serial.println("Error while reading the sensor");
      return;
    }

    //Serial.print("Humidity(%): ");
    Serial.print(h);
    Serial.print(" ");
    
    //Serial.print("temperature(C): ");
    Serial.print(t);  
    Serial.print(" ");
    
    //Serial.print("polution: ");
    Serial.println(p);
  } 
}

void buttonToggleLed() {
  static bool old_but_state = 0;
  if (digitalRead(but_pin) == 0 && old_but_state == 1) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(200);
  }

  //Serial.println(digitalRead(but_pin));
  old_but_state = digitalRead(but_pin);
}
