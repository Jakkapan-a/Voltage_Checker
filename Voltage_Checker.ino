#include <TcPINOUT.h>

/*----------------- SET PINOUT 1-----------------*/
#define PIN_LED_GREEN_1 5
#define PIN_LED_RED_1 6

TcPINOUT LED_GREEN_1(PIN_LED_GREEN_1);
TcPINOUT LED_RED_1(PIN_LED_RED_1);
/*----------------- SET PINOUT 1-----------------*/
#define PIN_LED_GREEN_2 7
#define PIN_LED_RED_2 8
TcPINOUT LED_GREEN_2(PIN_LED_GREEN_2);
TcPINOUT LED_RED_2(PIN_LED_RED_2);

/*----------------- VARIABLES -----------------*/

const float current_limit = 80;
const float voltage_limit = 2.5;

void setup() {
  Serial.begin(9600);
}

void loop() {

  /*------------- GET VALUE 1 -----------------*/
 float current_sensor_1 = 100;  // Read current from  sensor 1
 float voltage_1 = 2.3;        // Read voltage from  sensor 1
// Call function validateVoltage
 validateVoltage(current_sensor_1 ,voltage_1,LED_GREEN_1, LED_RED_1);


 /*-------------- GET VALUE 2 -----------------*/
 float current_sensor_2 = 100;  // Read current from  sensor 2
 float voltage_2 = 2.3;        // Read voltage from  sensor 2
 // Call function validateVoltage
 validateVoltage(current_sensor_2 ,voltage_2,LED_GREEN_2, LED_RED_2);

}

void validateVoltage(float input_current, float input_voltage, TcPINOUT LED_GREEN, TcPINOUT LED_RED) {
 if (input_current > current_limit) {
    // Check Voltage
    if (input_voltage < voltage_limit) {
      // LED Green on
      LED_GREEN.on();
      LED_RED.off();
    } else {
      // LED Red on
      LED_GREEN.off();
      LED_RED.on();
    }
  } else {
    // LED Off All
      LED_GREEN.off();
      LED_RED.off();
  }
}
