#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 40, NEO_GRB + NEO_KHZ800);
int redLEDPin = 13;
int rPin = 6;
int gPin = 5;
int bPin = 4;
String str;
int count = 0;
String body = "";
int offset = 0;

void setup() {
  // put your setup code here, to run once:
  //strip.setBrightness(50);
  //strip.begin();
  //strip.show();
  pinMode(redLEDPin, OUTPUT);

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  analogWrite(rPin, 255);
  analogWrite(gPin, 255);
  analogWrite(bPin, 255);

  Serial.begin(9600);
}

void basic() {
  if(offset == 0)
    strip.setPixelColor(0, 255, 0, 0);
  else if(offset == 1)
    strip.setPixelColor(0, 0, 255, 0);
  else
    strip.setPixelColor(0, 0, 0, 255);
  strip.show();
  delay(1000);
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  delay(1000);
  offset = offset > 2 ? 0 : offset+1;
}

void loop() {
  // put your main code here, to run repeatedly:
  //basic();
  
  if(Serial.available()) {
    str = Serial.readStringUntil('.');
    if(str.length() > 0) {
      Serial.println(str);
      if(str[0] == '!') {
        initialize();
      } else if(str[0] == '?') {
        digitalWrite(13, LOW);
      } else if(str[0] == 'R') {
        int strength = str.substring(1, str.length()).toInt();
        analogWrite(rPin, strength);
        Serial.println(strength);
      } else if(str[0] == 'G') {
        int strength = str.substring(1, str.length()).toInt();
        analogWrite(gPin, strength);
        Serial.println(strength);
      } else if(str[0] == 'B') {
        int strength = str.substring(1, str.length()).toInt();
        analogWrite(bPin, strength);
        Serial.println(strength);
      } else {
        body += str + '\n';
        count++;
      }
      str = "";
    }
  }
}

int initialize() {
  int size = 0;
  digitalWrite(13, HIGH);
  
  if(str.length() > 1) {
    int i = 1;
    int size = str.substring(1,str.length()-1).toInt();
    Serial.print(size);
  }
  return size;
}