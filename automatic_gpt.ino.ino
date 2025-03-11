#define BLYNK_TEMPLATE_ID "TMPL3T86BJpwg"
#define BLYNK_TEMPLATE_NAME "Automatic Plant Watering System"
#define BLYNK_AUTH_TOKEN "m7cchcIhb0cu0tQQdo7B70Ak2YEq6J7k"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "m7cchcIhb0cu0tQQdo7B70Ak2YEq6J7k";
char ssid[] = "vivo";
char pass[] = "siiuuu@7";

#define sensorPin A0
#define relayPin D1

BlynkTimer timer;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  timer.setInterval(1000L, checkSoilMoisture);
}

void checkSoilMoisture()
{
  int sensorValue = analogRead(sensorPin);
  int moisturePercent = map(sensorValue, 1023, 0, 0, 100);
  Blynk.virtualWrite(V0, moisturePercent);

  if (moisturePercent < 30)
  {
    digitalWrite(relayPin, LOW); // Turn on pump
  }
  else
  {
    digitalWrite(relayPin, HIGH); // Turn off pump
  }
}

BLYNK_WRITE(V1)
{
  int buttonState = param.asInt();
  if (buttonState == 1)
  {
    digitalWrite(relayPin, LOW); // Turn on pump
  }
  else
  {
    digitalWrite(relayPin, HIGH); // Turn off pump
  }
}

void loop()
{
  Blynk.run();
  timer.run();
}

