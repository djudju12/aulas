// C++ code
// o codigo repete para os dois arduinos
#define LED    A0
#define BUTTON A5

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  while(!Serial)
    ;
}

#define ON  7
#define OFF 0

void loop()
{
  int cmd = 0;
  
  if(Serial.available() > 0) {
    cmd = Serial.read();
    if (cmd == ON) {
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(LED, LOW);
    }
  }
	
  if (digitalRead(BUTTON) == HIGH) {
  	Serial.write(ON);
  } else {
    Serial.write(OFF);
  }
  
  delay(250);
}
