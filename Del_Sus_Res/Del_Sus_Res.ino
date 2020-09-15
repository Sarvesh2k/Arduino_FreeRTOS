#include <Arduino_FreeRTOS.h>
//Delete, Suspend and Resume functions

//Define two tasks
void Task_Print1(void *param);
void Task_Print2(void *param);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

int counter = 0;

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
    counter++;

    if(counter == 15) {

      vTaskResume(TaskHandle_2); //Resumes Task 2 after 15 Seconds
    }
    
    vTaskDelayUntil(&getTick,1000 / portTICK_PERIOD_MS); // wait for one second. More accurate Delay
  }
}

void Task_Print2(void *param) {

  (void) param;
  while(1) {

    //counter++;
    Serial.println("TASK 2");

    if (counter == 10) {

      vTaskSuspend(TaskHandle_2); // Suspends Task 2 after 10 seconds
      //vTaskDelete(TaskHandle_2); will delets Task 2 after 10 seconds
    }
    
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
  }
}
