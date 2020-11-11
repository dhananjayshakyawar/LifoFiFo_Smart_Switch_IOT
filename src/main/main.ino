//--------------------- Includes ---------------------------//
#include <ESP8266WiFi.h>  
#include "update.h"
#include "smartswitch.h"
#define DEVICE_NAME "LIFOFIFO SMART SWITCH V2"
#define BAUD_RATE 115200

#define CONNECT_TIMEOUT 3000


unsigned long last_update_check; 
updateclass updateConnector;
//---------------- Setup ---------------------------------//
void setup(){
    Serial.begin(BAUD_RATE);
    
    char version_msg[100];
    sprintf(version_msg, "Running FW version: %s", FIRMWARE_VERSION);
    Serial.println("");
    Serial.println(version_msg);
    
    last_update_check = millis();
    setPinModes();
    setDefaultPinStates();
    ss_setup();
}

//-------------- Main ---------------------------------//
void loop(){
    handle_update();
    ss_loop();
}

void handle_update(){



    if(millis() >= (last_update_check + UPDATE_PERIOD)){

        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("INFO: Not Connected to Internet! Skipping update...");     
            return;
        }

        Serial.println("############################# Checking Servers for update ###################################");
        last_update_check  = millis();
        updateConnector.update(STATUS_LED);
        delay(5000);
    }
}

void setPinModes(){

}

void setDefaultPinStates(){

}
