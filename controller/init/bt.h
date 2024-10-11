
#define rxPin 11 // Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define txPin 10 // Broche 10 en tant que TX, à raccorder sur RX du HC-05

#define BUTTON_NUMBER  16

#define BUFFER_LEN 2

enum architechture {
    NONE,
    PIC8
};

typedef struct DataHeader {
    __int16 arc;
    __int16 size;
}DataHeader;

typedef struct Data{
    DataHeader header; 
    float joystickX;
    float joystickY;
    char button[BUFFER_LEN];
    __int16 gx;
    __int16 gy;
    __int16 gz;
    char arc; // specify the architecture of the sender
    char crc;
}Data;

#define a sizeof(Data);
#define a sizeof(DataHeader);
#define a sizeof(float);