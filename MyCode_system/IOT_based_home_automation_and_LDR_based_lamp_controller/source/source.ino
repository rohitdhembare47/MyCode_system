/*****************************************************************************
 * Author: Rohitkumar Dhembare
 * Project : IoT based Home Automation
 * Board : NodeMCU(12E)
 * Sensord : MQ9,  LDR, 4-Channel Relay Board, AC Lamp, Bulb Holder
*****************************************************************************/

#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "use-wifi-hostname";
const char* password = "use-wifi-password#";
const char* mqtt_server = "broker.mqtt-dashboard.com";  /* This is the mqtt host  free server*/

int auto_mode_val=2;
int count_val = 0;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0; 

void setup_wifi() {

  delay(10);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   
  }

  randomSeed(micros());
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  
  for (int i = 0; i < length; i++) {

  }
   char payload_data = (char)payload[0];
   
   if(payload_data == 'A'){
   
       auto_mode_val =1; /* auto_mode_val =1 LDR mode working*/
      }
      
   if(payload_data == 'B'){
    
       auto_mode_val = 2; /* auto_mode_val =2 IoT mode working*/
       }
       
   if( auto_mode_val==2){                             /* if IOT mode set*/
    
      if(payload_data == '0'){digitalWrite(2,LOW);}     /*turn on relay 1*/
      if(payload_data == '1'){digitalWrite(2,HIGH);}     /*turn off relay 1*/
      
      if(payload_data == '2'){digitalWrite(3,LOW);}     /*turn on relay 2*/
      if(payload_data == '3'){digitalWrite(3,HIGH);}     /*turn off relay 2*/
      
      if(payload_data == '4'){digitalWrite(4,LOW);}     /*turn on relay 3*/
      if(payload_data == '5'){digitalWrite(4,HIGH);}     /*turn off relay 3*/
      
      if(payload_data == '6'){digitalWrite(5,LOW);}     /*turn on relay 4*/
      if(payload_data == '7'){digitalWrite(5,HIGH);}     /*turn off relay 4*/
      
    }
    
    client.publish("07connectledtdemo", "8");
   
    
   
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
  
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
   
      // Once connected, publish an announcement...
      client.publish("07connectledtdemo", "8");
      // ... and resubscribe
      client.subscribe("Led1out07"); 
      client.subscribe("Led2out07");
      client.subscribe("Led3out07");
      client.subscribe("Led4out07");
      client.subscribe("Ledout07_automanual");
      
    
    } else {
      delay(5000);
    }
  }
}

void setup() {
  //GPIO 1 (TX) swap the pin to a GPIO.
  pinMode(1, FUNCTION_3); 
//GPIO 3 (RX) swap the pin to a GPIO.
  pinMode(3, FUNCTION_3);
  pinMode(0, INPUT);      /* IR sensor     nodemcu pin D3 */
  pinMode(1, OUTPUT);     /* buzzer        nodemcu pin TX */
  pinMode(2, OUTPUT);     /**relay1        nodemcu pin D4 */
  pinMode(3, OUTPUT);     /**relay2        nodemcu pin RX */
  pinMode(4, OUTPUT);     /**relay3        nodemcu pin D2 */
  pinMode(5, OUTPUT);     /**relay4        nodemcu pin D1 */
  pinMode(A0, INPUT);     /* LPS Sensor    nodemcu pin A0 */
  
 
  pinMode(BUILTIN_LED, OUTPUT);      // Initialize the BUILTIN_LED pin as an output
 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
 int ldr = 0;
 int lpg_val = 0;
  
   

     if (auto_mode_val == 1)         //LDR MODE
     
       { 
       ldr = digitalRead(0);                         /* read LDR sensor value*/

        if(ldr == 1 ){        
                            digitalWrite(2,HIGH);    /* All relay on */
                            digitalWrite(3,HIGH); 
                            digitalWrite(4,HIGH); 
                            digitalWrite(5,HIGH);
                              delay(500);
                         }
           else {           
                            digitalWrite(5,LOW);        /* All relay off */
                            digitalWrite(2,LOW); 
                            digitalWrite(3,LOW); 
                            digitalWrite(4,LOW);  
                            delay(500);      
                       }         
         
         
       }
       if(count_val >10000){
        count_val=0;
       
       lpg_val = analogRead(A0);                              /*read LPG sensor value*/
       if(lpg_val >=500){     digitalWrite(1,HIGH);    }      /*turn on buzzer*/
         else       {     digitalWrite(1,LOW);     }          /*turn off buzzer*/
       }
       count_val++;

}
