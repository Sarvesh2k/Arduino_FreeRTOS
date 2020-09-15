#include <Arduino_FreeRTOS.h>

void setup() {
  Serial.begin(9600);
  Serial.println("This is a setup function");
  delay(2000);

  xTaskCreate(task1, "Task1", 100, NULL, 1, NULL);
  xTaskCreate(task2, "Task2", 100, NULL, 2, NULL);
  vTaskStartScheduler(); //Starts the RTOS scheduler
}

void loop() {

}

void task1(void* pvParamaeters) {
  while(1)  {
    Serial.println("Task1 is running");
    vTaskDelay(2000/portTICK_PERIOD_MS); //unblock for 2 ms
  }
}

void task2(void* pvParamaeters) {
  while(1)  {
    Serial.println("Task2 is running");
    vTaskDelay(4000/portTICK_PERIOD_MS); //unblock for 2 ms
  }
}
