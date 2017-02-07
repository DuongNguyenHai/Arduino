void setup() {
	Serial.begin(115200);     // opens serial port, baudrate : 9600 bps
}

void loop() {

    if (Serial.available() > 0) {
        String str = Serial.readString();
        Serial.print("Received: ");
        Serial.println(str);
    }
}
