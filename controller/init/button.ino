

int controlPins[] = {2, 3, 4, 5};
int inputArraySize = sizeof(controlPins) / sizeof(int);

//Mux in "SIG" pin
int SIG_pin = A3;

void setupButton() {

    // pinMode(SIG_pin, INPUT);
    // pinMode(SIG_pin, INPUT);
    for (int i = 0; i < inputArraySize; i++) {
        pinMode(controlPins[i], OUTPUT);
        digitalWrite(controlPins[i], LOW);
    }

    // pinMode(s1, OUTPUT); 
    // pinMode(s2, OUTPUT); 
    // pinMode(s3, OUTPUT); 
    // digitalWrite(s1, LOW);
    // digitalWrite(s2, LOW);
    // digitalWrite(s3, LOW);
}

void selectChannel(int channel) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(controlPins[i], bitRead(channel, i));  // Set the address pins
  }
}

int findMajority(int arr[], int n)
{
    int i, candidate = -1, votes = 0;
    // Finding majority candidate
    for (i = 0; i < n; i++) {
        if (votes == 0) {
            candidate = arr[i];
            votes = 1;
        }
        else {
            if (arr[i] == candidate)
                votes++;
            else
                votes--;
        }
    }
    int count = 0;
    // Checking if majority candidate occurs more than n/2
    // times
    for (i = 0; i < n; i++) {
        if (arr[i] == candidate)
            count++;
    }

    if (count > n / 2)
        return candidate;
    return -1;
}

int readMux(int channel){
    // int controlPin[] = {s0, s1, s2, s3};

    // int muxChannel[16][4]={
    //     {0,0,0,0}, //channel 0
    //     {1,0,0,0}, //channel 1
    //     {0,1,0,0}, //channel 2
    //     {1,1,0,0}, //channel 3
    //     {0,0,1,0}, //channel 4
    //     {1,0,1,0}, //channel 5
    //     {0,1,1,0}, //channel 6
    //     {1,1,1,0}, //channel 7
    //     {0,0,0,1}, //channel 8
    //     {1,0,0,1}, //channel 9
    //     {0,1,0,1}, //channel 10
    //     {1,1,0,1}, //channel 11
    //     {0,0,1,1}, //channel 12
    //     {1,0,1,1}, //channel 13
    //     {0,1,1,1}, //channel 14
    //     {1,1,1,1}  //channel 15
    // };

    //loop through the 4 sig
    for(int i = 0; i < 4; i ++) {
        // digitalWrite(intputPins[i], (channel >> (inputArraySize - i)) & 0b1);
        digitalWrite(controlPins[i], muxChannel[channel][i]);
    }
    delay(10);
    //read the value at the SIG pin
    int val = analogRead(SIG_pin);
  
    Serial.print("value at pin");
    Serial.print(channel);
    Serial.print(" is ");
    Serial.println(val);
    Serial.println();

    //return the value
    // float voltage = (val * 5.0) / 1024.0;
    return val;
}