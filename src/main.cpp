#include <Arduino.h>
#include <sbus.h>

#define RX_pin = 20
#define TX_pin = 21

void setup() {
    /* Serial to display data */
    Serial.begin(115200);
    while (!Serial) {}
    /* Begin the SBUS communication */
    sbus_rx.Begin();
    sbus_tx.Begin();
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
        /* Set the SBUS TX data to the received data */
        sbus_tx.data(data);
        /* Write the data to the servos */
        sbus_tx.Write();
    }
}