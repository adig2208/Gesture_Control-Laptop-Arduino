const int Trigger_R = 2;
const int Echo_R = 3;
const int Trigger_L = 4;
const int Echo_L = 5;
const int LED_Pin = 13;

float minDistR = 50.0;
float minDistL = 50.0;

void setup() {
  Serial.begin(9600);
  pinMode(Trigger_R, OUTPUT);
  pinMode(Echo_R, INPUT);
  pinMode(Trigger_L, OUTPUT);
  pinMode(Echo_L, INPUT);
  pinMode(LED_Pin, OUTPUT);

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

void loop() {

  float distance1 = Distance(Trigger_R, Echo_R);
  float distance2 = Distance(Trigger_L, Echo_L);

  if (distanceR > 0 && distanceR < 10) {
    Serial.println("Volume_Up");
    digitalWrite(LED_Pin, HIGH);
    delay(500);
    digitalWrite(LED_Pin, LOW);
  } else if (distanceL > 0 && distanceL < 10) {
    Serial.println("Volume_Down");
    digitalWrite(LED_Pin, HIGH); 
    delay(500);
    digitalWrite(LED_Pin, LOW);
  }

  while (distance1 < 20 && distance1 > 0) {
    delay(300);
    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance1 == 50) {
      Serial.println("Forward");
      digitalWrite(LED_Pin, HIGH); 
      delay(1000);
      digitalWrite(LED_Pin, LOW);
    }
    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance1 > 0 && distance1 < 20 && distance2 == 50) {
      Serial.println("Scroll_Up");
      digitalWrite(LED_Pin, HIGH); 
      delay(1);
      digitalWrite(LED_Pin, LOW);
    }
  }

  if (distance1 > 25 && distance1 < 50 && distance2 == 50) {
    Serial.println("Scroll_Down");
    digitalWrite(LED_Pin, HIGH); 
    delay(100);
    digitalWrite(LED_Pin, LOW);
  }

  while (distance2 < 20 && distance2 > 0) {
    delay(300);
    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance2 == 50) {
      Serial.println("Rewind");
      digitalWrite(LED_Pin, HIGH); 
      delay(1000);
      digitalWrite(LED_Pin, LOW);
    }

    distance1 = Distance(Trigger_R, Echo_R);
    distance2 = Distance(Trigger_L, Echo_L);
    if (distance2 > 0 && distance2 < 20 && distance1 == 50) {
      Serial.println("Change_Tab");
      digitalWrite(LED_Pin, HIGH); 
      delay(1000);
      digitalWrite(LED_Pin, LOW);
    }
  }

  if (distance2 > 25 && distance2 < 50 && distance1 == 50) {
    Serial.println("Drop_Down");
    digitalWrite(LED_Pin, HIGH); 
    delay(1000);
    digitalWrite(LED_Pin, LOW);
  }
  if ((distance1 > 0 && distance1 < 50) && (distance2 > 0 && distance2 < 50)) {
    Serial.println("Enter");
    digitalWrite(LED_Pin, HIGH); 
    delay(1500);
    digitalWrite(LED_Pin, LOW);
  }
  delay(100);

}
