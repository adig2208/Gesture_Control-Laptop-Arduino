#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <avr/sleep.h>

// Pin Definitions
const int Trigger_R = 2;
const int Echo_R = 3;
const int Trigger_L = 4;
const int Echo_L = 5;
const int LED_Pin = 13;

// RTOS Objects
QueueHandle_t gestureQueue;          
SemaphoreHandle_t sensorMutex;       
SemaphoreHandle_t gestureSem;  
TaskHandle_t ledTask;          

void setup() {
  Serial.begin(9600);

  // Pin Configuration
  pinMode(Trigger_R, OUTPUT);
  pinMode(Echo_R, INPUT);
  pinMode(Trigger_L, OUTPUT);
  pinMode(Echo_L, INPUT);
  pinMode(LED_Pin, OUTPUT);

  gestureQueue = xQueueCreate(5, sizeof(char[20]));

  // Creating Mutex
  sensorMutex = xSemaphoreCreateMutex();

  // Using Binary Semaphore
  gestureSem = xSemaphoreCreateBinary();

  // RTOS Tasks
  xTaskCreate(GestureDetectionTask, "Gesture", 256, NULL, 2, NULL);
  xTaskCreate(ActionProcessingTask, "Action", 256, NULL, 1, NULL);
  xTaskCreate(LED_FeedbackTask, "LED", 128, NULL, 1, &ledTask);
  xTaskCreate(PowerManagementTask, "Sleep", 128, NULL, 1, NULL);

  Serial.println("RTOS with Mutex & Semaphore Started!");
}

// Distance Calculation with Mutex Protection
float Distance(int Trigger, int Echo) {
  float distance = 50.0;  

  if (xSemaphoreTake(sensorMutex, portMAX_DELAY)) {  
    digitalWrite(Trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger, LOW);

    float time = pulseIn(Echo, HIGH);
    distance = time * 0.034 / 2;  

    xSemaphoreGive(sensorMutex); 
  }

  return min(distance, 50);  
}

// Task 1: Gesture Detection Task
void GestureDetectionTask(void *pvParameters) {
  char gesture[20];

  while (1) {
    float distance1 = Distance(Trigger_R, Echo_R);
    float distance2 = Distance(Trigger_L, Echo_L);

    if (distance1 > 0 && distance1 < 10) {
      strcpy(gesture, "Volume_Up");
    } else if (distance2 > 0 && distance2 < 10) {
      strcpy(gesture, "Volume_Down");
    } else if (distance1 < 20 && distance1 > 0) {
      strcpy(gesture, "Scroll_Up");
    } else if (distance2 < 20 && distance2 > 0) {
      strcpy(gesture, "Change_Tab");
    } else {
      vTaskDelay(pdMS_TO_TICKS(100));  
      continue;
    }

    xQueueSend(gestureQueue, (void *)&gesture, portMAX_DELAY);
    xSemaphoreGive(gestureSem);
  }
}

// Task 2: Action Processing Task
void ActionProcessingTask(void *pvParameters) {
  char receivedGesture[20];

  while (1) {
    if (xSemaphoreTake(gestureSem, portMAX_DELAY)) {  
      if (xQueueReceive(gestureQueue, &receivedGesture, portMAX_DELAY) == pdTRUE) {
        Serial.println(receivedGesture);
        xTaskNotifyGive(ledTask);  
      }
    }
  }
}

// Task 3: LED Feedback Task
void LED_FeedbackTask(void *pvParameters) {
  while (1) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  
    digitalWrite(LED_Pin, HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
    digitalWrite(LED_Pin, LOW);
  }
}

// Task 4: Power Management Task (Sleep Mode)
void PowerManagementTask(void *pvParameters) {
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(5000));  

    Serial.println("Going to sleep...");
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();  
    sleep_disable();
    Serial.println("Waking up...");
  }
}
