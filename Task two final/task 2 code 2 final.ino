const int green = 11;
const int yellow = 12;
const int red = 13;
const int pedGreen = 9;
const int pedRed = 10;

unsigned long previousMillis = 0;
int state = 0;
const unsigned long greenTime = 10000;   // 10 seconds green for cars
const unsigned long yellowTime = 3000;   // 3 seconds yellow
const unsigned long redTime = 10000;     // 10 seconds red for cars (pedestrians walk)

void setup() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  switch(state) {
    case 0:  // Green cars, red pedestrians
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(red, LOW);
      digitalWrite(pedGreen, LOW);
      digitalWrite(pedRed, HIGH);
      if (currentMillis - previousMillis >= greenTime) {
        state = 1;
        previousMillis = currentMillis;
      }
      break;

    case 1:  // Yellow cars, red pedestrians
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(pedGreen, LOW);
      digitalWrite(pedRed, HIGH);
      if (currentMillis - previousMillis >= yellowTime) {
        state = 2;
        previousMillis = currentMillis;
      }
      break;

    case 2:  // Red cars, green pedestrians
      digitalWrite(green, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(pedGreen, HIGH);
      digitalWrite(pedRed, LOW);
      if (currentMillis - previousMillis >= redTime) {
        state = 0;
        previousMillis = currentMillis;
      }
      break;
  }
}
