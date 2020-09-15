#include <Arduino_FreeRTOS.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
TaskHandle_t TaskHandle_4;

void setup()
{
  
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  /* Create two tasks with priorities 1 and 3. Capture the Task details to respective handlers */
  xTaskCreate(MyTask1, "Task1", 100, NULL, 1, &TaskHandle_1);  
  xTaskCreate(MyTask3, "Task3", 120, NULL, 3, &TaskHandle_3);

}


void loop()
{
  // Hooked to Idle task, it will run whenever CPU is idle
  Serial.println(F("Loop function"));
  delay(50);
}


/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
  while(1)
  {
    Serial.println(F("Task1 Running and About to delete itself"));
    vTaskDelete(TaskHandle_1);    // Delete the task using the TaskHandle_1
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {    
    Serial.println(F("Task2 Running and About to delete itself"));
    vTaskDelete(NULL);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


/* Task3 with priority 3 */
static void MyTask3(void* pvParameters)
{
  while(1)
  {    
    Serial.println(F("Task3 Running, Creating Task2 and Task4"));
    xTaskCreate(MyTask2, "Task2", 50, NULL, 2, &TaskHandle_2);
    xTaskCreate(MyTask4, "Task4", 100, NULL, 4, &TaskHandle_4);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    Serial.println(F("Back in Task3 and About to delete itself"));
    vTaskDelete(TaskHandle_3); 
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


/* Task4 with priority 4 */
static void MyTask4(void* pvParameters)
{
  while(1)
  {    
    Serial.println(F("Task4 Running and About to delete itself"));
    vTaskDelete(NULL);     //Delete own task by passing NULL(TaskHandle_4 can also be used)
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
