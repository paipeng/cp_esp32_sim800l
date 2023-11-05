
#if 1
// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM800      // Modem is SIM800
#define TINY_GSM_RX_BUFFER   1024  // Set RX buffer to 1Kb
#include <TinyGsmClient.h>
// SIM card PIN (leave empty, if not defined)
const char simPIN[]   = "";

// Your phone number to send SMS: + (plus sign) and country code, for Portugal +351, followed by phone number
// SMS_TARGET Example for Portugal +351XXXXXXXXX
#define SMS_TARGET  "+8613233696233"


#define MODEM_TX             17
#define MODEM_RX             16

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to SIM800 module)
#define SerialAT  Serial1

// Define the serial console for debug prints, if needed
//#define DUMP_AT_COMMANDS

#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif
#endif
void setup() {
  Serial.begin(115200);
  delay(300);
#if 1
  // Set GSM module baud rate and UART pins
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  // Restart SIM800 module, it takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  if (modem.restart()) {
    SerialMon.println("success!");


    // use modem.init() if you don't need the complete restart

    // Unlock your SIM card with a PIN if needed
    if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
      modem.simUnlock(simPIN);
    }

    // To send an SMS, call modem.sendSMS(SMS_TARGET, smsMessage)
    String smsMessage = "Hello from ESP32!";
    if(modem.sendSMS(SMS_TARGET, smsMessage)){
      SerialMon.println(smsMessage);
    }
    else{
      SerialMon.println("SMS failed to send");
    }

  } else {
    SerialMon.println("failed!");
  }

#endif  
}


void loop() {
  Serial.println("loop...");
  delay(1000);
}
