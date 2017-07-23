#include "ESPHelper.h"

#define TOPIC "MA003/relay"
#define STATUS TOPIC "/status"
#define RELAY_PIN 3   

char* relayTopic = TOPIC;
char* statusTopic = STATUS;

const int relayPin = RELAY_PIN;

netInfo homeNet = {
  .name = "MA003",
  .mqtt = "192.168.10.101",
  .ssid = "mozolino",
  .pass = "costinha"
};

ESPHelper myESP(&homeNet);

void setup() {

  //setup the rest of ESPHelper
  myESP.addSubscription(relayTopic);
  myESP.begin();
  myESP.setCallback(callback);

  pinMode(relayPin, OUTPUT);
    delay(100);
}

void loop(){
  //loop ESPHelper and wait for commands from mqtt
  myESP.loop();
  yield();
}

//mqtt callback
void callback(char* topic, byte* payload, unsigned int length) {
  String topicStr = topic;

  //if the payload from mqtt was 1, turn the relay on and update the status topic with 1
  if(payload[0] == '1'){
    digitalWrite(relayPin, HIGH);
    myESP.publish(statusTopic, "1",true);
  } else if (payload[0] == '0'){
    digitalWrite(relayPin, LOW);
    myESP.client.publish(statusTopic, "0", true);
  }
}

