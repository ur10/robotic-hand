
/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 * 
*/

/*
  This example shows the basic example for automatic plant watering system.
  The sketch will set GPIO16 for Pump1, and GPIO12 for Pump2
  The status of pumps showed at /PlantWatering/status
  
  Two pumps will be set to turn on in the moring and evening for 120 second everyday
  To manually turn on and off both pumps, change the value under /PlantWatering/control
  To control the device, send command at /PlantWatering/control/cmd and the result from process
  showed at /PlantWatering/status/terminal
  The command and its description.
  idle: nothing to do
  get-time: get time from NTP server
  boot: restart the device
  load-pump: load pump configuration
  load-schedule: load schedule configuration
  pump-count: show the number of pumps at /PlantWatering/status/terminal
  schedule-count: show the number of schedules at /PlantWatering/status/terminal
*/

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <time.h>


#define WIFI_SSID "Free to exploit"
#define WIFI_PASSWORD "getalife"
#define FIREBASE_HOST "esp8266-560d9.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "PWZ3Tqof8pbCy4MqKhBccx0v1igrCoZdFkTkLmXD"


struct preset_time_t
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int duration;
    int state;
    int pump_index;
    int active;
    int inactive;
};

struct pump_info_t
{
    String id;
    int state;
    int gpio;
};

//FirebaseData firebaseData1;
//FirebaseData firebaseData2;

String path = "/PlantWatering";
bool timeReady = false;
//Change to match your time zone
float time_zone = 3;
float daylight_offset_in_sec = 0;

//For 10 presets
preset_time_t presetTime[10];

//For 5 pumps
pump_info_t pumpInfo[5];
int i=0;

void setPumpState(int pumpIndex, int state);
//void streamCallback(StreamData data);
//void streamTimeoutCallback(bool timeout);
//void setDeviceTime(float time_zone, float daylight_offset_in_sec);
//void setDailySchedule(int presetIndex, int pumpIndex, int activeState, int inactiveState, int hour, int min, int sec, int duration_in_sec, FirebaseJsonArray *scheduleConfig);
//void runSchedule();
//void loadSchedule(FirebaseData &data);
//void setPump(int pumpIndex, String id, int gpio, int state, FirebaseJsonArray *pumpConfig);
//void loadPump(FirebaseData &data);

void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    //get time from NTP server and set up
    Serial.println("Get time from NTP server...");
//    setDeviceTime(time_zone, daylight_offset_in_sec);

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    if(!Firebase.success())
    Serial.println("Not initialized");
    Firebase.setInt("Coordinates/Latitude",600);
    if(!Firebase.success())
    Serial.println("Not Sent");
    else
    Serial.println("Sent");
}
void loop()
{
    Firebase.setInt("Coordinates/Latitude",600);
  
}
