// From http://cs.smith.edu/dftwiki/index.php/Tutorial:_Arduino_and_XBee_Communication

/*
  Xbee1
  D. Thiebaut
  
  Makes Arduino send 1 character via XBee wireless to another XBee connected
  to a computer via a USB cable. 

  The circuit: 
  * RX is digital pin 2 (connect to TX of XBee)
  * TX is digital pin 3 (connect to RX of XBee)
 
  Based on a sketch created back in the mists of time by Tom Igoe
  itself based on Mikal Hart's example
 
*/

#include <SoftwareSerial.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

SoftwareSerial xbee(2, 3); // RX, TX
int  pingPong = 1;

//instance of thermometer 
DHT dht(DHTPIN, DHTTYPE);

// instance of barometer
Adafruit_BMP085 bmp;

void setup()  {
   //Serial.begin(57600);
   Serial.begin(9600);
   if (!bmp.begin()) {
     Serial.println("Could not find a valid BMP085 sensor, check wiring!");
     while (1) {}
   }
   Serial.println( "Arduino started sending DHT22 via XBee" );
   //turn on DHT
     dht.begin();
     
   // set the data rate for the SoftwareSerial port
   //xbee.begin( 19200 );
   xbee.begin( 9600 );
}

void loop()  {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
    // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
    } else {
      Serial.println("THERMOMETER START");
      Serial.println();
      Serial.print("Humidity: "); 
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(t);
      Serial.println(" *C");
      Serial.println();
      Serial.println("THERMOMETER END");
      Serial.println();
    }
    
    // code for barometer
    Serial.println("BAROMETER START");
    Serial.println();
    Serial.print("Barometer Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    Serial.println();
    Serial.println("BAROMETER END");
    Serial.println();
    
        // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    xbee.println("Failed to read from DHT");
    } else {
      xbee.println("THERMOMETER START");
      xbee.println();
      xbee.print("Humidity: "); 
      xbee.print(h);
      xbee.print(" %\t");
      xbee.print("Temperature: "); 
      xbee.print(t);
      xbee.println(" *C");
      xbee.println();
      xbee.println("THERMOMETER END");
      xbee.println();
    }
    
    // code for barometer
    xbee.println("BAROMETER START");
    xbee.println();
    xbee.print("Barometer Temperature = ");
    xbee.print(bmp.readTemperature());
    xbee.println(" *C");
    
    xbee.print("Pressure = ");
    xbee.print(bmp.readPressure());
    xbee.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    xbee.print("Altitude = ");
    xbee.print(bmp.readAltitude());
    xbee.println(" meters");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    xbee.print("Real altitude = ");
    xbee.print(bmp.readAltitude(101500));
    xbee.println(" meters");
    xbee.println();
    xbee.println("BAROMETER END");
    xbee.println();
  
  // send character via XBee to other XBee connected to Mac
  // via USB cable
  // xbee.print( c );
  
  //--- display the character just sent on console ---
  // Serial.println( c );
  
  //--- get the next letter in the alphabet, and reset to ---
  //--- 'A' once we have reached 'Z'. 
  // c = c + 1;
  // if ( c>'Z' ) 
  //     c = 'A';
  
  //--- switch LED on Arduino board every character sent---
  if ( pingPong == 0 )
    digitalWrite(12, LOW);
  else
    digitalWrite(12, HIGH);
  pingPong = 1 - pingPong;
  delay( 1000 );
}
