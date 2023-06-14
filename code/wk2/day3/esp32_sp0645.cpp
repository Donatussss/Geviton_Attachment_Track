//Lin J
#include <WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#include <math.h>

#define SERIAL_BAUD 115200
#define SAMPLE_RATE 16000
#define MTU 1440

int16_t sample16 = 0;
int32_t sample = 0;
int16_t element = 0;
int sample_counter = 0;

const char * udpAddress = "192.168.xx.xxx";
const int udpPort = 3333;
boolean transmit = false;
const char* ssid     = "xxxxxxx";
const char* password = "xxxxxxx";
QueueHandle_t queueSample;
int queueSize = SAMPLE_RATE * 2;
const i2s_port_t I2S_PORT = I2S_NUM_0;
//create UDP instance
WiFiUDP udp;

void setupSampleTask(){
xTaskCreate(
                    sampleAudio,          /* Task function. */
                    "SampleAudio",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
}

void  setupI2SMic() {
  Serial.println("Configuring I2S...");
  // The I2S config as per the example
  esp_err_t err;
 const  i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive, not transfer
    .sample_rate = SAMPLE_RATE,                         // 16KHz
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // could only get it to work with 32bits
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT, // although the SEL config should be left, it seems to transmit on right
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,     // Interrupt level 1
    .dma_buf_count = 32,                           // number of buffers
    .dma_buf_len = 64,
    .use_apll = true
  };
  // The pin config as per the setup
  const i2s_pin_config_t pin_config = {
    .bck_io_num = 25,   // BCKL
    .ws_io_num = 27,    // LRCL
    .data_out_num = -1, // not used (only for speakers)
    .data_in_num = 26   // DOUT
  };
  err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  if (err != ESP_OK) {
    Serial.printf("Failed installing driver: %d\n", err);
    while (true);
  }
  err = i2s_set_pin(I2S_PORT, &pin_config);
  if (err != ESP_OK) {
    Serial.printf("Failed setting pin: %d\n", err);
    while (true);
  }  
  Serial.println("I2S driver installed.");
};

void setup() {

    Serial.begin(SERIAL_BAUD);
    //Serial.println("I was built on " + "14-06-2023" + " at " + String(millis()));
    Serial.println("Hello");
    Serial.print("Init Serial Communication:");
    Serial.println(SERIAL_BAUD);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected with IP address: ");
    Serial.println(WiFi.localIP());
    queueSample = xQueueCreate( queueSize, sizeof( int16_t ) );   
    if(queueSample == NULL){      
         Serial.println("Error creating the queue");   
    }   
    setupI2SMic();    
    setupSampleTask();
    Serial.println("Setup done!");
}

void loop() {              
        udp.beginPacket(udpAddress, udpPort);        
        for(sample_counter=0; sample_counter<MTU/2; sample_counter++){         
        xQueueReceive(queueSample, &element, portMAX_DELAY);
        udp.write((byte*)&element,2);          
        }        
        udp.endPacket();      
}

void sampleAudio( void * parameter )
{      
      while ( true ){        
            i2s_pop_sample(I2S_PORT, (char *)&sample,10);
            sample>>=14;
            sample16 = (int16_t)sample;
            xQueueSend(queueSample, &sample16, 10);          
      }
      vTaskDelete( NULL ); 
}
