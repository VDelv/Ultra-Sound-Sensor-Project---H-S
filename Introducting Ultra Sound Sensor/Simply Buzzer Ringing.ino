#define BUZZER_PIN D4

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
       
}

void loop(){
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);
  delay(500);  
}
