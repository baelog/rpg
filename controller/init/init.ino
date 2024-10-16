

#include <SoftwareSerial.h>



const int ledPin = 13;    // the number of the LED pin
const int baseDelay = 1;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
    setupBT();
    setupJoystick();
    setupGyro();
    setupButton();
    
    pinMode(8, INPUT_PULLUP);
    Serial.begin(9600);

    // initialize the LED pin as an output:
    // for (int i = 0; i != buttonPinSize; ++i) {
    //     pinMode(buttonPins[i], INPUT);
    // }
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // // initialize the pushbutton pin as an input:
}

void loop() {
    loopBT();
    // loopJoystick();
    // loopGyro();
    if (digitalRead(8) == LOW) {  // Button pressed (pin is connected to GND)
        Serial.println("Button is pressed");
    } else {  // Button not pressed (pin is pulled to HIGH by the pull-up resistor)
        Serial.println("Button is not pressed");
    }
    delay(500);
}