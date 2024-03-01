#include <Arduino.h>
#include <sbus.h>

#define RX_pin 20
#define TX_pin 21

#include <HardwareSerial.h>

HardwareSerial SBUSS(0);

/* SBUS object, reading SBUS */
bfs::SbusRx sbus_rx(&SBUSS, 20, 21, true);
/* SBUS object, writing SBUS */
//bfs::SbusTx sbus_tx(&SBUSS, 22, 23, true);
/* SBUS data */
bfs::SbusData data;

void setup() {
    /* Serial to display data */
    Serial.begin(115200);
    //while (!Serial) {}
    delay(1000);
    Serial.println("-------------------------");
    Serial.println("Setup");
    Serial.println("-------------------------");
    /* Begin the SBUS communication */
    sbus_rx.Begin();
}

void loop(){
    if (sbus_rx.Read()) {
        /* Grab the received data */
        data = sbus_rx.data();
        /* Display the received data */
        for (int8_t i = 0; i < data.NUM_CH; i++) {
            Serial.print(data.ch[i]);
            Serial.print("\t");
        }
        /* Display lost frames and failsafe data */
        Serial.print(data.lost_frame);
        Serial.print("\t");
        Serial.println(data.failsafe);
    }
}