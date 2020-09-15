#include <Arduino_FreeRTOS.h>

void setup()
{
  
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  /* Create two tasks with priorities 1 and 2. 
   * Enable the Idle Task Hook by setting configUSE_IDLE_HOOK to 1, by this the loop function can be used as Idle task.
  */

  xTaskCreate(MyTask1, "Task1", 100, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 2, NULL);
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
    Serial.println(F("Task1"));
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}


/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {    
    Serial.println(F("Task2"));
    vTaskDelay(150/portTICK_PERIOD_MS);
  }
}
