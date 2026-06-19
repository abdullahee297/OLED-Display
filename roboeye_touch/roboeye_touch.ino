#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define touchpin A3

#define OLED_RESET     -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RoboEyes<Adafruit_SSD1306> roboEyes(display); 

int mood = 1;
bool lasttouchtouch = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(touchpin, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);

  // Define some automated eyes behaviour
  roboEyes.setAutoblinker(ON, 3, 2); // Start auto blinker animation cycle -> bool active, int interval, int variation -> turn on/off, set interval between each blink in full seconds, set range for random interval variation in full seconds
  roboEyes.setIdleMode(ON, 2, 2); // Start idle animation cycle (eyes looking in random directions) -> turn on/off, set interval between each eye repositioning in full seconds, set range for random time interval variation in full seconds
  

  roboEyes.setMood(DEFAULT);
  roboEyes.setPosition(DEFAULT); 
  roboEyes.setCuriosity(ON); 
  
  // Set horizontal or vertical flickering
  //roboEyes.setHFlicker(ON, 2);
  //roboEyes.setVFlicker(ON, 2); 
  
}


void loop() {
 roboEyes.update();
 
 bool touch = digitalRead(touchpin);

 // Making the mood condition
 if (touch == HIGH && lasttouchtouch == LOW){
  mood++;

  if (mood > 3){
    mood = 0;
  }
  switch (mood){

    case 0:
    roboEyes.setMood(DEFAULT);
    break;

    case 1:
    roboEyes.setMood(HAPPY);
    break;

    case 2:
    roboEyes.setMood(ANGRY);
    break;

    case 3:
    roboEyes.setMood(TIRED);
    break;
  }
  delay(10);
 }

 lasttouchtouch = touch;

}
