#include <HX711.h>

// Pins for HX711
#define DT 3
#define SCK 2

// Pins for LEDs
#define RED_LED 8
#define YELLOW_LED 9
#define GREEN_LED 10

// Set your weight range here
#define UNDERLOAD_THRESHOLD 140
#define OVERLOAD_THRESHOLD 350

HX711 scale;
float scaleFactor = -211.29; // Replace with your calculated scale factor
long zeroValue = -66300;   // Replace with your zero value

void setup() {
  Serial.begin(9600);
  scale.begin(DT, SCK);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  if (scale.is_ready()) {
    long rawReading = scale.get_units();
    float weight = (rawReading - zeroValue) / scaleFactor; // Convert to weight

    Serial.print("Weight: ");
    Serial.println(weight);

    if (weight < UNDERLOAD_THRESHOLD) {
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    } else if (weight > OVERLOAD_THRESHOLD) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    } else {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
    }
  } else {
    Serial.println("HX711 not ready!");
  }
  delay(500);
}


