#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial sim800l(16, 17); 

void setup() {
  delay(1000);

  Serial.begin(115200);
  delay(300);

  //Begin serial communication with Arduino and SIM800L
  sim800l.begin(115200);

  Serial.println("Initializing...");
  delay(1000);

  sim800l.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  sim800l.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  sim800l.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  sim800l.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}


void loop() {
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim800l.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(sim800l.available()) 
  {
    Serial.write(sim800l.read());//Forward what Software Serial received to Serial Port
  }
}