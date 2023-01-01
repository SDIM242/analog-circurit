#include <OneWire.h>
#include <DallasTemperature.h>
#include <FastLED.h>
#define ONE_WIRE_BUS 3
#define LED_PIN     2
#define NUM_LEDS    33
CRGB leds[NUM_LEDS];
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float data;
int a = 0;
int b = 0;
void setup() {
  Serial.begin(9600);
  sensors.begin();
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  sensors.requestTemperatures(); // Aquire temperature
  float Temp=sensors.getTempCByIndex(0);
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0)); 
  delay(50); 
  if (Temp>=37){
    for (int i = 0; i <= 32; i++) {
      leds[i] = CRGB ( 255, 69, 0);
    }
    FastLED.show();
    delay(50);
  }
  data = analogRead(A0);
  Serial.print("the voltage is:");
  Serial.print(data);
  Serial.println("V");
  delay(50);
  if (data<=657&&data>622){
    a=a+1;
  }
  if (data<=622&&data>100){
    b=b+1;
  }
  if (a<3&&b<3&&Temp<37){
    for (int i = 0; i <= 32; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  if (a>=3&&b<3&&Temp<37){
    for (int i = 0; i <= 32; i++) {
      leds[i] = CRGB ( 255, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  if(b>=3&&Temp<37){
    for (int i = 0; i <= 32; i++) {
      leds[i] = CRGB ( 255, 0, 0);
    }
    FastLED.show();
    delay(50);
  }

}
