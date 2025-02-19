#include "arduino_secrets.h"

#include <ModbusMaster.h>

// Define RS485 communication pins
#define RS485_TX 1  // Nano 33 IoT TX pin (Connect to RS485 Module)
#define RS485_RX 0  // Nano 33 IoT RX pin (Connect to RS485 Module)

// Initialize Modbus Master
ModbusMaster modbusMaster;

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1);

    modbusMaster.begin(1, Serial1); // Slave ID 1, using Serial1
}

void loop() {
    uint16_t valueToSend = 100;
    
    // Write 100 to Holding Register 0 on ESP32
    uint8_t result = modbusMaster.writeSingleRegister(0, valueToSend);

    if (result == modbusMaster.ku8MBSuccess) {
        Serial.println("Successfully wrote 100 to register 0");
    } else {
        Serial.print("Write failed, error code: ");
        Serial.println(result);
    }

    delay(1000); // Allow ESP32 time to process

    // Read Processed Value from Register 1 on ESP32
    result = modbusMaster.readHoldingRegisters(1, 1);

    if (result == modbusMaster.ku8MBSuccess) {
        uint16_t receivedValue = modbusMaster.getResponseBuffer(0);
        Serial.print("Received from ESP32 (Register 1): ");
        Serial.println(receivedValue);
    } else {
        Serial.print("Read failed, error code: ");
        Serial.println(result);
    }

  Serial.println();
  Serial.println();

    delay(2000); // Wait before next request
}