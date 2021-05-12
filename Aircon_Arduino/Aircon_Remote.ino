#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "DL_Aircon.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ArduinoJson.h>

#define MQTT_MAXBUFFERSIZE 250
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

const char* ssid = "************";
const char* password = "***********";

#define MQTT_SERVER "192.168.x.x"
#define MQTT_PORT   1883
#define MQTT_USER   "aircon"

#define IR_PIN 14

#define LED_GREEN 12
#define LED_BLUE 13
#define LED_RED 15
#define BUTTON 4

IRsend irsend(IR_PIN); //an IR led is connected to GPIO pin 14
DynamicJsonBuffer  jsonBuffer;

dl_aircon_msg_t msg;
bool recv = false;
unsigned long millis_last = 0;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USER, "");

const char ONOFF_FEED[] PROGMEM = MQTT_USER "/set";
Adafruit_MQTT_Subscribe mq_aircon_set = Adafruit_MQTT_Subscribe(&mqtt, ONOFF_FEED);

const char STATUS_FEED[] PROGMEM = MQTT_USER "/status";
Adafruit_MQTT_Publish mq_aircon_status = Adafruit_MQTT_Publish(&mqtt, STATUS_FEED);

void MQTT_connect();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(112500);  
  Serial.println("Booting");
  
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(IR_PIN, OUTPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);
  
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  
  //Default settings
  irsend.begin();
  msg.on = false;
  msg.temperature = 24;
  msg.unitF = false;
  msg.timer = false;
  msg.timer_value = 1;
  msg.mode=8;
  msg.fan=2;
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_RED, HIGH);
    delay(100);
    digitalWrite(LED_RED, LOW);
    delay(400);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  mqtt.subscribe(&mq_aircon_set);

  Serial.println("Go!");
  
  digitalWrite(LED_GREEN, HIGH);
  delay(100);
  digitalWrite(LED_GREEN, LOW);
}

void loop() {  

  if (millis() - millis_last > 500){
    MQTT_connect();

    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(500))) {
      if (subscription == &mq_aircon_set) {
        digitalWrite(LED_BLUE, HIGH);
        Serial.println("Got MQTT");
        JsonObject& root = jsonBuffer.parseObject((char*)mq_aircon_set.lastread);
  
        if (!root.success()) {
          Serial.println("parseObject() failed");
          return;
        }
      
        if (root.containsKey("on")) msg.on = root["on"];
        if (root.containsKey("temperature")) msg.temperature = root["temperature"];
  
        if (root.containsKey("mode"))msg.mode = root["mode"];
        if (root.containsKey("fan")) msg.fan = root["fan"];
  
        if (root.containsKey("unitF")) msg.unitF = root["unitF"];
        if (root.containsKey("timer")) msg.timer = root["timer"];
        if (root.containsKey("timer_value")) msg.timer_value = root["timer_value"];
  
        unsigned long data = dl_assemble_msg(&msg);
        irsend.sendNEC(data, 32);
        recv = true;
      }
    }

    millis_last = millis();
  }
  
  if (recv){  
    Serial.println("Answer");
    JsonObject& root = jsonBuffer.createObject();

    root["on"] = msg.on;
    root["temperature"] = msg.temperature;
    root["mode"] = msg.mode;
    root["fan"] = msg.fan;
    root["unitF"] = msg.unitF;
    root["timer"] = msg.timer;
    root["timer_value"] = msg.timer_value;

    //char buf[root.measureLength()];
    char buf[250];
    root.printTo(buf, 250);
    
    mq_aircon_status.publish(buf);
    recv = false;
    digitalWrite(LED_BLUE, LOW);
  }
  
  yield();
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
