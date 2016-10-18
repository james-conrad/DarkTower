void setup() {
    Serial.begin(9600);
    Serial1.begin(38400);
}

void loop() {
    int incomingByte;
        
    while (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        Serial.write(incomingByte);
    }

    while (Serial.available() > 0) {
        incomingByte = Serial.read();
        Serial1.write(incomingByte);
    }
}
