/*  Test program for parking assist lights.  This uses two HC-SR04 ultrasonic
*   distance sensors to make ranging tests on car position and then lights up
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

#define redpin 10
#define yellowpin  11
#define greenpin  12

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int ping1;     // Holds distance returned by sensor 1
int ping2;     // Holds distance returned by sensor 2
int distance;  // Holds average distance reported by both sensors

NewPing sonar1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);  
  
  pinMode(redpin, OUTPUT);      // Red LED
  pinMode(yellowpin, OUTPUT);   // GND ping
  pinMode(greenpin, OUTPUT);    // GND ping
  
  digitalWrite(redpin, LOW);
  digitalWrite(yellowpin, LOW);  
  digitalWrite(greenpin, LOW);    
}

void loop() {
  delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  ping1 = sonar1.ping_in();  // Get sensor 1 distance
  ping2 = sonar2.ping_in();  // Get sensor 2 distance
  distance = (ping1 + ping2)/2;  // Calculate average distance
  /* Now some serial output for troubleshooting */
  Serial.print("Ping1: ");
  Serial.print(ping1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("in    ");  
  Serial.print("Ping2: ");
  Serial.print(ping1);   
  Serial.print("in    ");
  Serial.print("Avg: ");
  Serial.print(distance);   
  Serial.println("in");  
  /* End of serial troubleshooting data section.  */

  /* Check if sensor is timed out */
  if (distance == 0){
    resetSensors();
  }

  /* Check distance in several ranges and turn on appropriate lights. */
  if (distance > 36 || distance == 0) {
    digitalWrite(greenpin, LOW);
    digitalWrite(yellowpin, LOW);     
    digitalWrite(redpin, LOW);
  }
  
  if (distance > 24 && distance < 36) {
    digitalWrite(greenpin, HIGH);
    digitalWrite(yellowpin, LOW);     
    digitalWrite(redpin, LOW);
  }

  if (distance > 18 && distance <= 24) {
    digitalWrite(greenpin, HIGH);
    digitalWrite(yellowpin, HIGH);
    digitalWrite(redpin, LOW);  
  }  
  
  if (distance > 12 && distance <= 18) {
    digitalWrite(greenpin, LOW);
    digitalWrite(yellowpin, HIGH);
    digitalWrite(redpin, HIGH);  
  }    
  
if (distance <= 12 && distance != 0) {
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

/* Function to flash red light if too close. */
void flashred(int d){
  digitalWrite(redpin, HIGH);
  delay(d);
  digitalWrite(redpin, LOW);    
} // End flashred()

/* Function to reset sensors if hung up. */
void resetSensors(void){
  pinMode(ECHO_PIN, OUTPUT);
  pinMode(ECHO_PIN2, OUTPUT);  
  digitalWrite(ECHO_PIN, LOW);
  digitalWrite(ECHO_PIN2, LOW);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ECHO_PIN2, INPUT); 
  
}

