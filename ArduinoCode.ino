#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

WiFiClient client;

long ChannelNo = 149857;
const char APIKey[] = "OARWEJDH3Q676BJV";

const int trigPin = D5;
const int echoPin = D6;

long timeTaken;
float emptyLength, percent;
int maxLength = 18;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  WiFi.begin("WiFiPassword", "WiFiName");
  while(Wifi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
    Serial.println();
    Serial.println("NodeMCU is Connected");
    Serial.println(WiFi.localIP());
    ThingSpeak.begin(client);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  
  timeTaken = pulseIn(echoPin, HIGH);
  
  emptyLength = timeTaken*0.034/2;
  percent = ((maxLength - emptyLength)/maxLength)*100;
  
  Serial.print(percent);
  Serial.println(" % jar filled");
  
  ThingSpeak.writeField(ChannelNo, 1, percent, APIKey);
  delay(4000);
}
                 
