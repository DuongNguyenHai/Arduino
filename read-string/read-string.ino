void setup() {
    Serial.begin(115200);
    Serial.println("Arduino's receiving : ");
}

String str = "OK";

void loop() {

    if( Serial.available() ){ 
      String storedData = Serial.readString();
      Serial.println(storedData);
      Serial.flush();
      if(storedData == str)
        Serial.println("Bravo");
    }
}