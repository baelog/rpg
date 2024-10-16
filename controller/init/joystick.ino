int axeX = A0; // signal de l'axe X sur entrée A0
int axeY = A1; // signal de l'axe Y sur entrée A1
int BP7 = 7; // Bouton-poussoir en broche 7

void setupJoystick()
{
    pinMode(axeX, INPUT); // définition de A0 comme une entrée
    pinMode(axeY, INPUT); // définition de A1 comme une entrée
    pinMode(BP7, INPUT); // définition de 7 comme une entrée
    digitalWrite(BP7, HIGH); // Activation de la résistance de Pull-Up
}

void loopJoystick(float *x, float *y)
{
    int Bouton;
    *x = analogRead (axeX) * (5.0 / 1023.0);
    *y = analogRead (axeY) * (5.0 / 1023.0);
    Bouton = digitalRead (BP7);
    Serial.print("Axe X:");
    Serial.print(*x, 4);
    Serial.print("V, ");
    Serial.print("Axe Y:");
    Serial.print(*y, 4);
    Serial.print("V, ");
    Serial.print("Bouton:");
    if (Bouton==1) {
        Serial.println(" Aucune pression sur le bouton poussoir ");
    }
    else {
        Serial.println(" Bouton-poussoir actif ");
    }
    delay (100);
}