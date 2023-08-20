#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

EventGroupHandle_t grupEvt;

const int  goCom = BIT0;
const int goSensor = BIT1;

void task1(void * params){

    unsigned int valor = 0;

    while (true)
    {
        
        printf("Gocom %d \n",goCom);
        xEventGroupSetBits(grupEvt,goCom);
        printf("Gocom %d \n",goCom);
        vTaskDelay( 2000 / portTICK_PERIOD_MS );
    }
    

}

void task3(void * params){

    while (true)
    {
        
        printf("goSensor \n");
        xEventGroupSetBits(grupEvt,goSensor);
        printf("goSensor \n");
        vTaskDelay( 5000 / portTICK_PERIOD_MS );
    }
    
    
}

void task2(void * params){

    while (true)
    {
        xEventGroupWaitBits(grupEvt,goCom | goSensor,true,true, portMAX_DELAY);
        printf("Todos os valores rescebidos %d %d \n",goCom, goSensor);
        
    }
    
}

void app_main(void)
{
    grupEvt = xEventGroupCreate();
    
    xTaskCreate(&task1,"Task1",2048,NULL,1,NULL);
    xTaskCreate(&task2,"Task2",2048,NULL,2,NULL);
    xTaskCreate(&task3,"Task3",2048,NULL,2,NULL);

}
