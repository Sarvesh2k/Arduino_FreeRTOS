#include <Arduino_FreeRTOS.h>
#include <semphr.h>

/* Mutex -> In certain time only 1 task runs and the other tasks will wait until that task is finished.
 * Finally, that task needs to release mutex key (Basically a variable), in order for other tasks to
 * then start executing using that mutex key. 
 */

//Define two tasks
void Task_Print1(void *param);
void Task_Print2(void *param);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
SemaphoreHandle_t myMutex;

volatile int a;
//volatile boolean myMutex = false;

void setup() {
  // Inititalize serial communication at 9600 bits per second
  Serial.begin(9600);

  //Initialise Mutex
  myMutex = xSemaphoreCreateMutex();
  if (myMutex == NULL) {

    Serial.println("Mutex cannot be created");
  }

  //Create tasks
  xTaskCreate(Task_Print1, "Task1", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(Task_Print2, "Task2", 100, NULL, 1, &TaskHandle_2);
}

void loop() {
  // Empty. Things are done in Tasks

}

void Task_Print1(void *param) {

  (void) param;
  
  while(1) {

    //while(myMutex == true);
    xSemaphoreTake(myMutex, portMAX_DELAY); // Take Mutex
    
    for(int i=0; i < 5; i++) {

      //a = 1;
      Serial.println(i);
      vTaskDelay(50 / portTICK_PERIOD_MS); // wait for half second.
    }
    //myMutex = true;
    xSemaphoreGive(myMutex); // Release Mutex
  }
}

void Task_Print2(void *param) {

  (void) param;
  while(1) {

    //while(myMutex == false);
    xSemaphoreTake(myMutex, portMAX_DELAY); // Take Mutex
    
    for(int i=0; i < 5; i++) {

      //a = 2;
      Serial.println(i);
      vTaskDelay(50 / portTICK_PERIOD_MS); // wait for half second.
    }
    //myMutex = false;
    xSemaphoreGive(myMutex); // Release Mutex
  }
}
