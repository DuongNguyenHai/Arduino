// Nguyen Hai Duong
// 3 july 2016

// Receive data via uart

void setup() {
    Serial.begin(9600);
    Serial.println("Arduino's receiving : ");
}

void loop() {

    if (Serial.available() > 0) {

        byte data = Serial.read();
        Serial.print(data);
    }
}