#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;
// int16_t gx, gy, gz;

void setupGyro() {
    Wire.begin();
    mpu.initialize();
    
    // Serial.begin(9600);
    // while (!Serial) {
    //     // Attendez que la connexion série soit établie (pour les cartes Arduino qui nécessitent cela)
    
}

void loopGyro(__int16 *gx, __int16 *gy, __int16 *gz) {

    mpu.getMotion6(&ax, &ay, &az, gx, gy, gz);
    
    Serial.print("Accel X: "); Serial.println(ax);
    Serial.print(" Accel Y: "); Serial.println(ay);
    Serial.print(" Accel Z: "); Serial.println(az);
    Serial.print(" Gyro X: "); Serial.println(gx);
    Serial.print(" Gyro Y: "); Serial.println(gy);
    Serial.print(" Gyro Z: "); Serial.println(gz);
    
    // delay(1000);
}