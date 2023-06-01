#include <TcPINOUT.h>
#include <Adafruit_INA219.h>

//*********************** INPUT Sensor ***********************//
/* 
 * Up to 4 boards may be connected. Addressing is as follows:
 * Board 0: Address = 0x40 Offset = binary 00000 (no jumpers required)
 * Board 1: Address = 0x41 Offset = binary 00001 (bridge A0 as in the photo above)
 * Board 2: Address = 0x44 Offset = binary 00100 (bridge A1)
 * Board 3: Address = 0x45 Offset = binary 00101 (bridge A0 & A1)
*/
Adafruit_INA219 ina219_1(0x40);
Adafruit_INA219 ina219_2(0x41);

/*----------------- SET OUTPUT 1-----------------*/
#define PIN_LED_GREEN_1 5
#define PIN_LED_RED_1 6

TcPINOUT LED_GREEN_1(PIN_LED_GREEN_1);
TcPINOUT LED_RED_1(PIN_LED_RED_1);
/*----------------- SET OUTPUT 1-----------------*/
#define PIN_LED_GREEN_2 7
#define PIN_LED_RED_2 8
TcPINOUT LED_GREEN_2(PIN_LED_GREEN_2);
TcPINOUT LED_RED_2(PIN_LED_RED_2);
/*----------------- SET INPUT VOLTAGE 1-----------------*/
#define PIN_VL_1 A0
/*----------------- SET INPUT VOLTAGE 2-----------------*/
#define PIN_VL_2 A1
/*----------------- VARIABLES -----------------*/

const double current_limit = 80;
const float voltage_limit = 150;
void setup() {
  Serial.begin(9600);
  ina219_1.begin();
  ina219_2.begin();
}

void loop() {

  /*------------- GET VALUE 1 -----------------*/
  double current_sensor_1 = ina219_1.getCurrent_mA();  // Read current from  sensor 1
  int sensorValue_1 = analogRead(PIN_VL_1);            // Read voltage from  sensor 1
  // float voltage_1 = sensorValue_1 * (5.0 / 1023.0);
  Serial.print("Current 1 : " + String(current_sensor_1));
  Serial.println(" Voltage 1 : " + String(sensorValue_1));
  validateVoltage(current_sensor_1, sensorValue_1, LED_GREEN_1, LED_RED_1);
  /*-------------- GET VALUE 2 -----------------*/
  double current_sensor_2 = ina219_2.getCurrent_mA();  // Read current from  sensor 2
  int sensorValue_2 = analogRead(PIN_VL_2);            // Read voltage from  sensor 2
  // float voltage_2 = sensorValue_2 * (5.0 / 1023.0);
  Serial.print("Current 2 : " + String(current_sensor_2));
  Serial.println("Voltage 2 : " + String(sensorValue_2));
  validateVoltage(current_sensor_2, sensorValue_2 , LED_GREEN_2, LED_RED_2);
  delay(50);
}

void validateVoltage(double input_current, float input_voltage, TcPINOUT LED_GREEN, TcPINOUT LED_RED) {
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
