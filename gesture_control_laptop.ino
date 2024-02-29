#include <avr/sleep.h>

#include <avr/power.h>

const int Trigger_R = 2;
const int Echo_R = 3;
const int Trigger_L = 4;
const int Echo_L = 5;
const int LED_Pin = 13;
const int WakeUp_Pin = 2;

float minDistR = 50.0;
float minDistL = 50.0;

void wakeUpNow() {
  Serial.println("Waking up, starting recalibration...");
  calibrateSensors();
  Serial.println("Recalibration completed.");
}

void setup() {
  Serial.begin(9600);
  pinMode(Trigger_R, OUTPUT);
  pinMode(Echo_R, INPUT);
  pinMode(Trigger_L, OUTPUT);
  pinMode(Echo_L, INPUT);
  pinMode(LED_Pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), wakeUpNow, LOW); // Assuming digital pin 2 is used for wake-up

  Serial.println("Calibration Start");
  calibrateSensors();
  Serial.println("Calibration Done");
}

void calibrateSensors() {
  for (int i = 0; i < 10; i++) {
    float distanceR = Distance(Trigger_R, Echo_R);
    float distanceL = Distance(Trigger_L, Echo_L);
    minDistR = min(minDistR, distanceR);
    minDistL = min(minDistL, distanceL);
    delay(100);
  }
  minDistR += 5.0;
  minDistL += 5.0;
}

float Distance(int Trigger, int Echo) {
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  float time = pulseIn(Echo, HIGH);
  float distance = time * 0.034 / 2;
  return min(distance, 50);
}

void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Deepest sleep mode
  sleep_enable(); // Enable sleep mode
  sleep_mode(); // Enter sleep mode

  // Device is now asleep and will continue from here when woken up
  sleep_disable(); // Disable sleep mode after wake up
}

void loop() {

  float distance1 = Distance(Trigger_R, Echo_R);
  float distance2 = Distance(Trigger_L, Echo_L);

  if (distanceR > 0 && distanceR < 10) {
    Serial.println("Volume_Up");
    digitalWrite(feedbackLED, HIGH);
    delay(500);
    digitalWrite(feedbackLED, LOW);
  } else if (distanceL > 0 && distanceL < 10) {
    Serial.println("Volume_Down");
    digitalWrite(feedbackLED, HIGH); // Feedback
    delay(500);
    digitalWrite(feedbackLED, LOW);
  }

  while (distance1 < 20 && distance1 > 0) {
    delay(300);
    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance1 == 50) {
      Serial.println("Forward");
      delay(1000);
    }
    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance1 > 0 && distance1 < 20 && distance2 == 50) {
      Serial.println("Scroll_Up");
      delay(1);
    }
  }

  if (distance1 > 25 && distance1 < 50 && distance2 == 50) {
    Serial.println("Scroll_Down");
    delay(100);
  }

  while (distance2 < 20 && distance2 > 0) {
    delay(300);
    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance2 == 50) {
      Serial.println("Rewind");
      delay(1000);
    }

    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance2 > 0 && distance2 < 20 && distance1 == 50) {
      Serial.println("Change_Tab");
      delay(1000);
    }
  }

  if (distance2 > 25 && distance2 < 50 && distance1 == 50) {
    Serial.println("Drop_Down");
    delay(1000);
  }
  if ((distance1 > 0 && distance1 < 50) && (distance2 > 0 && distance2 < 50)) {
    Serial.println("Enter");
    delay(1500);
  }
  if (distanceR < 10 && distanceL > 30 && distanceL < 50) {
    Serial.println("Volume_Up");
    delay(500); // Short delay to prevent multiple triggers
  }
  // Volume Down: Left hand moves closer while right hand remains static
  else if (distanceL < 10 && distanceR > 30 && distanceR < 50) {
    Serial.println("Volume_Down");
    delay(500);
  }
  // Existing gestures for reference
  else if (distanceR < 20 && distanceR > 0) {
    Serial.println("Scroll_Up");
    delay(300);
  } else if (distanceL < 20 && distanceL > 0) {
    Serial.println("Change_Tab");
    delay(300);
  }

  delay(100);
  goToSleep();

}
