#include <SoftwareSerial.h>
#include "bt.h"

SoftwareSerial SerialBT(rxPin, txPin);


void setupBT() {
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    SerialBT.begin(9600);

}

void loopBT() {
    Data data;
    // char inputs[4] = { 0 };
    while (SerialBT.available()) {
        Serial.print((char)SerialBT.read());
    }
    memset(&data, 0, sizeof(Data));
    data.arc = PIC8;
    data.size = sizeof(Data);
    data.size = sizeof(__int16);
    loopButton(data.playload1);
    loopGyro(&data.gx, &data.gy, &data.gz);
    // loopButton(data.playload2);
    // loopButton(data.playload3);
    SerialBT.write((char*)&data, sizeof(Data));
    // delay(10);
    // if (divide) {
    //     SerialBT.write(buff, sizeof(buff), );
    // } else {
    //     digitalWrite(ledPin, LOW);
    // }
}

void loopButton(char *payload) {

    for (int i = 0; i < BUTTON_NUMBER; i++) {    // Loop through all 16 channels (S0 - S15)
        selectChannel(i);
    
        int buttonState = analogRead(A3);  // Read from the selected channel

        // Convert analog read value to digital
        if (buttonState > 512) { // Button pressed (LOW, closer to 0)
            Serial.print("Button on Channel ");
            Serial.print(i);
            Serial.print(" is PRESSED ");
        } else {  // Button not pressed (HIGH, closer to 1023)
            Serial.print("Button on Channel ");
            Serial.print(i);
            Serial.print(" is NOT pressed ");
        }
        Serial.println(buttonState);
        
        delay(100);  // Delay for better readability in the Serial Monitor
    }
}