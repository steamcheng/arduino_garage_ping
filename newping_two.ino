/*  Test program for parking assist lights.  This uses two HC-SR04 ultrasonic
*   distanse sensors to make ranging tests on car position and then lights up
*   a series of LEDs to provide feedback to the driver.
*
*   Created by: Davis Whittaker
*   Created on: 1 Oct 2016
*   Last Modified: 3 Oct 2016
*
*   3 Oct 2016 - Added flashing red lights for distances less than 8"
               - Removed use of pins to control power to the sensors
*/

#include <NewPing.h>

#define TRIGGER_PIN  2   // Arduino pin tied to trigger pin on 1st ultrasonic sensor.
#define ECHO_PIN     3   // Arduino pin tied to echo pin on 1st ultrasonic sensor.

#define TRIGGER_PIN2  7   // Arduino pin tied to trigger pin on 2nd ultrasonic sensor.
#define ECHO_PIN2     8   // Arduino pin tied to echo pin on 2nd ultrasonic sensor.

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int redpin = 10;
int yellowpin = 11;
int greenpin = 12;
int ping1;
int ping2;
int distance;
// int d;
//void flashred(int);

NewPing sonar1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
  pinMode(redpin, OUTPUT);      // Red LED
  pinMode(yellowpin, OUTPUT);   // GND ping
  pinMode(greenpin, OUTPUT);    // GND ping
  
  digitalWrite(redpin, LOW);
  digitalWrite(yellowpin, LOW);  
  digitalWrite(greenpin, LOW);    
}

void loop() {
  delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  ping1 = sonar1.ping_in();
  ping2 = sonar2.ping_in();
  distance = (ping1 + ping2)/2;
  Serial.print("Ping1: ");
  Serial.print(ping1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("in    ");  
  Serial.print("Ping2: ");
  Serial.print(ping1);   
  Serial.print("in    ");
  Serial.print("Avg: ");
  Serial.print(distance);   
  Serial.println("in");  

  if (distance > 24 || distance == 0) {
    digitalWrite(greenpin, LOW);
    digitalWrite(yellowpin, LOW);     
    digitalWrite(redpin, LOW);
  }
  
  if (distance > 18 && distance < 24) {
    digitalWrite(greenpin, HIGH);
    digitalWrite(yellowpin, LOW);     
    digitalWrite(redpin, LOW);
  }

  if (distance > 12 && distance <= 18) {
    digitalWrite(greenpin, HIGH);
    digitalWrite(yellowpin, HIGH);
    digitalWrite(redpin, LOW);  
  }  
  
  if (distance > 9 && distance <= 12) {
    digitalWrite(greenpin, LOW);
    digitalWrite(yellowpin, HIGH);
    digitalWrite(redpin, HIGH);  
  }    
  
if (distance <= 9 && distance != 0) {
   digitalWrite(greenpin, LOW);
   digitalWrite(yellowpin, LOW);
   digitalWrite(redpin, HIGH);     
   }
   
   if (distance <= 8 && distance > 6 && distance != 0) {
   flashred(250);     
   }
   
   if (distance <= 6 && distance != 0) {
   flashred(125);     
   }   

} // End main loop

void flashred(int d){
  digitalWrite(redpin, HIGH);
  delay(d);
  digitalWrite(redpin, LOW);    
} // End flashred()

