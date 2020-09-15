#include <Arduino_FreeRTOS.h>

/* Implements multitasking i.e. LED's will turn ON or OFF
 * simultaneously. Timing is determined in the respective functions.
 */

const int red_led = 10;
const int green_led = 11;
const int white_led = 12; //setting the pins

void setup()  {
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(white_led, OUTPUT);

  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(white_led, LOW);
  delay(3000);

  xTaskCreate(red, "Red", 100, NULL, 3, NULL);
  xTaskCreate(green, "Green", 100, NULL, 2, NULL);
  xTaskCreate(white, "White", 100, NULL, 1, NULL);
  vTaskStartScheduler();
}

void loop() {
  //Idle Task
}

void red(void* pvParameters)  {
  while(1)  {
    digitalWrite(red_led, LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(red_led, HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void green(void* pvParameters)  {
  while(1)  {
    digitalWrite(green_led, LOW);
    vTaskDelay(2000/portTICK_PERIOD_MS);
    digitalWrite(green_led, HIGH);
    vTaskDelay(2000/portTICK_PERIOD_MS);
  }
}

void white(void* pvParameters)  {
  while(1)  {
    digitalWrite(white_led, LOW);
    vTaskDelay(3000/portTICK_PERIOD_MS);
    digitalWrite(white_led, HIGH);
    vTaskDelay(3000/portTICK_PERIOD_MS);
  }
}
