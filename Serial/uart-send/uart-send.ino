// Nguyen Hai Duong
// 3 july 2016

// Send 1,2,..,10,1,2,..... via uart

void setup() {
  Serial.begin(9600);
}

void loop() {
	int count=0;
	Serial.println("Arduino's sending : ");
	
	while(true){
	    Serial.print(count++);
	    delay(1000);
	    if(count>10){
	    	count=0;
	    }
	}
}
