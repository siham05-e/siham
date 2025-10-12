// Traffic Light Control System
// Using millis() 

const int PIN_GREEN = 10;
const int PIN_YELLOW = 12;
const int PIN_RED = 13;

class TrafficLight {
// Timer durations in milliseconds
const unsigned long TIMER_YELLOW = 3000;
const unsigned long TIMER_MAIN = 10000; 
// Pin numbers
int pinGreen;
int pinYellow;
int pinRed;

// Timing
unsigned long previousMillis;

// Traffic light states
enum State {
GREEN,
YELLOW,
RED
};

State currentState;
State targetState;

public:
TrafficLight(int greenLED, int yellowLED, int redLED) {
pinGreen = greenLED;
pinYellow = yellowLED;
pinRed = redLED;

pinMode(pinGreen, OUTPUT);
pinMode(pinYellow, OUTPUT);
pinMode(pinRed, OUTPUT);

// Start on RED, will move to GREEN after cycle
currentState = RED;
targetState = GREEN;
previousMillis = 0; // will switch after TIMER_MAIN ms
red();
}

void loop() {
unsigned long currentMillis = millis();

switch (currentState) {
case RED:
if (currentMillis - previousMillis >= TIMER_MAIN) {
previousMillis = currentMillis;
currentState = YELLOW;
targetState = GREEN;
yellow();
}
break;

case GREEN:
if (currentMillis - previousMillis >= TIMER_MAIN) {
previousMillis = currentMillis;
currentState = YELLOW;
targetState = RED;
yellow();
}
break;

case YELLOW:
if (currentMillis - previousMillis >= TIMER_YELLOW) {
previousMillis = currentMillis;
if (targetState == GREEN) {
currentState = GREEN;
green();
} else {
currentState = RED;
red();
}
}
break;
}
}

private:
void green() {
digitalWrite(pinGreen, HIGH);
digitalWrite(pinYellow, LOW);
digitalWrite(pinRed, LOW);
}

void yellow() {
digitalWrite(pinGreen, LOW);
digitalWrite(pinYellow, HIGH);
digitalWrite(pinRed, LOW);
}

void red() {
digitalWrite(pinGreen, LOW);
digitalWrite(pinYellow, LOW);
digitalWrite(pinRed, HIGH);
}

void off() { // unused, but available if needed
digitalWrite(pinGreen, LOW);
digitalWrite(pinYellow, LOW);
digitalWrite(pinRed, LOW);
}
};

// Create traffic light object
TrafficLight trafficLight(PIN_GREEN, PIN_YELLOW, PIN_RED);

void setup() {
// nothing extra needed for now
}

void loop() {
trafficLight.loop();
}
