#include <Arduino.h>
#include <sbus.h>

#define RX_pin 20
#define TX_pin 21

#define THROTTLE data.ch[2]
#define YAW data.ch[3]
#define PITCH data.ch[1]
#define ROLL data.ch[0]

#define MOTOR_PIN 0
#define RUDDER_PIN
#define ELEVATOR_PIN
#define AILERON_L_PIN 1
#define AILERON_R_PIN 2

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

    ledcAttachPin(AILERON_L_PIN, 1);
    ledcAttachPin(AILERON_R_PIN, 2);
    ledcSetup(1, 50, 14);
    ledcSetup(2, 50, 14);

    ledcAttachPin(MOTOR_PIN, 0);
    ledcSetup(0, 20000, 12);
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
        Serial.print("THROTTLE: ");
        Serial.print(THROTTLE);
        Serial.print("\t");
        Serial.print("YAW: ");
        Serial.print(YAW);
        Serial.print("\t");
        Serial.print("ROLL: ");
        Serial.print(ROLL);
        Serial.print("\t");
        Serial.print("PITCH: ");
        Serial.print(PITCH);
        Serial.print("\n");
*/

// min value = 172
// max value = 1811
// mid value = 992

u16_t getServoDutyFromRcIn(double rcVal) {

    double temp1 = (rcVal - 172.0) / (1811.0 - 172.0);
    u16_t temp2 = (temp1 + 1) * (16383 / 20);

    return(temp2);
}

u16_t getMotorDutyFromRcIn(double rcVal) {

    double temp1 = (rcVal - 172.0) / (1811.0 - 172.0);
    u16_t temp2 = (temp1) * 4095;

    return(temp2);
}

void loop(){
    if (sbus_rx.Read()) {
        /* Grab the received data */
        data = sbus_rx.data();
        
        ledcWrite(1, getServoDutyFromRcIn(1983.0 - ROLL));
        ledcWrite(2, getServoDutyFromRcIn(ROLL));

        ledcWrite(0, getMotorDutyFromRcIn(THROTTLE));

        Serial.print(getMotorDutyFromRcIn(THROTTLE));
        Serial.print("\n");

    }
}