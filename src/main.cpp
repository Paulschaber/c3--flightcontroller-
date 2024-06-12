#include <Arduino.h>
#include <sbus.h>

#define RX_pin 20
#define TX_pin 21

#define Throttle data.ch[2]
#define Yaw data.ch[3]
#define Pitch data.ch[1]
#define Roll data.ch[0]

#define MotorPin 0
#define RudderPin
#define ElevatorPin
#define AileronLPin 1
#define AileronRPin 2

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

    ledcAttachPin(AileronLPin, 1);
    ledcAttachPin(AileronRPin, 2);
    ledcSetup(1, 50, 14);
    ledcSetup(2, 50, 14);
}

/* Display the received data */
        /*for (int8_t i = 0; i < data.NUM_CH; i++) {
            Serial.print(data.ch[i]);
            Serial.print("\t");
        }*/
        /* Display lost frames and failsafe data */
        /*Serial.print(data.lost_frame);
        Serial.print("\t");
        Serial.println(data.failsafe);*/

/*
        Serial.print("Throttle: ");
        Serial.print(Throttle);
        Serial.print("\t");
        Serial.print("Yaw: ");
        Serial.print(Yaw);
        Serial.print("\t");
        Serial.print("Roll: ");
        Serial.print(Roll);
        Serial.print("\t");
        Serial.print("Pitch: ");
        Serial.print(Pitch);
        Serial.print("\n");
*/

// min value = 172
// max value = 1811
// mid value = 992

u16_t getDutyFromRcIn(double rcVal) {

    double temp1 = (rcVal - 172.0) / (1811.0 - 172.0);
    u16_t temp2 = (temp1 + 1) * (16383 / 20);

    return(temp2);
}

void loop(){
    if (sbus_rx.Read()) {
        /* Grab the received data */
        data = sbus_rx.data();
        
        ledcWrite(1, getDutyFromRcIn(1983.0 - Roll));
        ledcWrite(2, getDutyFromRcIn(Roll));

        Serial.print(getDutyFromRcIn(1983.0 - Roll));
        Serial.print("\n");
    }
}