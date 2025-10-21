// Traffic Light Control System with Pedestrian Lights
// Using millis() for non-blocking timing

const int PIN_GREEN = 11;
const int PIN_YELLOW = 12;
const int PIN_RED = 13;
const int PIN_PED_GREEN = 9; // Pedestrian green LED pin
const int PIN_PED_RED = 10; // Pedestrian red LED pin

class TrafficLight {
// Timer durations in milliseconds
const unsigned long TIMER_YELLOW = 3000; // 3 seconds for yellow
const unsigned long TIMER_MAIN = 10000; // 10 seconds for red/green

// Pin numbers
int pinGreen;
int pinYellow;
int pinRed;
int pinPedGreen;
int pinPedRed;

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
TrafficLight(int greenLED, int yellowLED, int redLED, int pedGreenLED, int pedRedLED) {
pinGreen = greenLED;
pinYellow = yellowLED;
pinRed = redLED;
pinPedGreen = pedGreenLED;
pinPedRed = pedRedLED;

pinMode(pinGreen, OUTPUT);
pinMode(pinYellow, OUTPUT);
pinMode(pinRed, OUTPUT);
pinMode(pinPedGreen, OUTPUT);
pinMode(pinPedRed, OUTPUT);

// Start on RED, will move to GREEN after cycle
currentState = RED;
targetState = GREEN;
previousMillis = 0; // will switch after TIMER_MAIN ms
red();
pedestrianRed(); // Pedestrian red on at start
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
pedestrianRed(); // Pedestrian red during yellow transition
} else {
pedestrianGreen(); // Pedestrians walk while cars red
}
break;

case GREEN:
if (currentMillis - previousMillis >= TIMER_MAIN) {
previousMillis = currentMillis;
currentState = YELLOW;
targetState = RED;
yellow();
pedestrianRed(); // Pedestrian red during yellow transition
} else {
pedestrianRed(); // Pedestrians stop while cars green
}
break;

case YELLOW:
if (currentMillis - previousMillis >= TIMER_YELLOW) {
previousMillis = currentMillis;
if (targetState == GREEN) {
currentState = GREEN;
green();
pedestrianRed();
} else {
currentState = RED;
red();
pedestrianGreen();
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

void pedestrianGreen() {
digitalWrite(pinPedGreen, HIGH);
digitalWrite(pinPedRed, LOW);
}

void pedestrianRed() {
digitalWrite(pinPedGreen, LOW);
digitalWrite(pinPedRed, HIGH);
}

void off() { // unused, but available if needed
digitalWrite(pinGreen, LOW);
digitalWrite(pinYellow, LOW);
digitalWrite(pinRed, LOW);
digitalWrite(pinPedGreen, LOW);
digitalWrite(pinPedRed, LOW);
}
};

// Create traffic light object with pedestrian pins
TrafficLight trafficLight(PIN_GREEN, PIN_YELLOW, PIN_RED, PIN_PED_GREEN, PIN_PED_RED);

void setup() {
// No extra setup needed aside from constructor initialization
}

void loop() {
trafficLight.loop();
}
