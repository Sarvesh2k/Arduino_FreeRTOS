#include <Arduino_FreeRTOS.h>

TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
TaskHandle_t TaskHandle_4;

void setup()
{  
    Serial.begin(9600);
    Serial.println(F("In Setup function"));

    /* Use INT0(pin2) falling edge interrupt for resuming tasks */
    attachInterrupt(digitalPinToInterrupt(2), ExternalInterrupt, FALLING); 

  /* Create 3-tasks with priorities 2-4. Capture the Task details to respective handlers */
  xTaskCreate(MyTask2, "Task2", 100, NULL, 2, &TaskHandle_2);  
  xTaskCreate(MyTask3, "Task3", 100, NULL, 3, &TaskHandle_3);
  xTaskCreate(MyTask4, "Task4", 100, NULL, 4, &TaskHandle_4);  
}


void loop()
{
    // Hooked to IDle task, it will run whenever CPU is idle
    Serial.println(F("Loop function"));
    delay(1000);
}


/* 
 *  Tasks are resumed every time a Falling edge interrupt is detected on PIN2.
 *  One task is resumed at a time, a counter is used to resume 3 tasks, after which no tasks will resumed.
 *  xTaskResumeFromISR() returns True if Context switch is required and accordingly we need to call portYIELD_FROM_ISR/taskYield(AVR).
 *  Serial data is printed in ISR only for demonstrating the control flow. This should not be done as it takes long time to send data on Serial port.
 *  Taking too much ISR time will starve the other tasks or User application. 
 *  
 */
static void ExternalInterrupt() // Based on Switch Press, tasks will resume on Falling Edge (Interrupt on Pin 2)
{
    static int count=0;
    BaseType_t taskYieldRequired = 0;

    if(count<=3)
    {
        count++;
    }

    switch(count) // Resume one task at a time depending on count value
    {    
    case 1:
        Serial.println(F("ISR Resuming Task2"));
        taskYieldRequired = xTaskResumeFromISR(TaskHandle_2);
        Serial.println(F("Leaving ISR"));
        break;

    case 2:
        Serial.println(F("ISR Resuming Task3"));
        taskYieldRequired = xTaskResumeFromISR(TaskHandle_3);
        Serial.println(F("Leaving ISR"));
        break;

    case 3:
        Serial.println(F("ISR Resuming Task4"));
        taskYieldRequired = xTaskResumeFromISR(TaskHandle_4);
        Serial.println(F("Leaving ISR"));
        break;

    default: //DO nothing
    
        break;
    }

    if(taskYieldRequired == 1) // If the taskYield is required then trigger the same.
    {
        taskYIELD();
    }
}



/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{        
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println(F("Task2, Deleting itself"));
    vTaskDelete(NULL);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
}


/* Task3 with priority 3 */
static void MyTask3(void* pvParameters)
{
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    Serial.println(F("Task3, Deleting Itself"));
    vTaskDelete(NULL);     //Delete own task by passing NULL(TaskHandle_3 can also be used)  
}


/* Task4 with priority 4 */
static void MyTask4(void* pvParameters)
{
    Serial.println(F("Task4 Running, Suspending all tasks"));
    vTaskSuspend(TaskHandle_2); //Suspend Task2/3
    vTaskSuspend(TaskHandle_3);
    vTaskSuspend(NULL);         //Suspend Own Task

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    Serial.println(F("Back in Task4, Deleting Itself"));
    vTaskDelete(TaskHandle_4);       
}
