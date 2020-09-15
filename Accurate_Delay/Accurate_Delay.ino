#include <Arduino_FreeRTOS.h>
//Program to perform more accurate delays using getTick

//Define two tasks
void Task_Print1(void *param);
void Task_Print2(void *param);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

void setup() {
  // Inititalize serial communication at 9600 bits per second
  Serial.begin(9600);

  //Create tasks
  xTaskCreate(Task_Print1, "Task1", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(Task_Print2, "Task2", 100, NULL, 1, &TaskHandle_2);
}

void loop() {
  // Empty. Things are done in Tasks

}

void Task_Print1(void *param) {

  (void) param;
  TickType_t getTick;
  getTick = xTaskGetTickCount(); // the getTick will get time from systick of OS
  vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS);

  while(1) {

    Serial.println("TASK 1");
    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS); // wait for one second. More accurate Delay
  }
}

void Task_Print2(void *param) {

  (void) param;
  while(1) {

    Serial.println("TASK 2");
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
  }
}
