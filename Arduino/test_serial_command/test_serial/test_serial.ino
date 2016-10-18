void setup() {
    Serial1.begin(38400);
}

void loop() {
    int incomingByte;
        
	while (Serial1.available() > 0) {
		incomingByte = Serial1.read();
		Serial1.print("Received Data: ");
		Serial1.println(incomingByte, DEC);
	}
}

