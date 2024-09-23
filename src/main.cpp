#include <WS2812FX.h>
#define LED_COUNT 64 // How many LED on your board ?
#define LED_PIN PC15
#define EffectBTN  PA15 //Pull-down resistor

int currentEffect = 0;       // To track the current effect
bool lastState = HIGH;  
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

/*CHECK modes_arduino.h TO GET MORE EFFECTS*/ 
void setEffect(int effect){
  switch (effect) {
  
    case 0:
      ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);     // Effect 1: Rainbow Cycle
      break;
    case 1:
      ws2812fx.setMode(FX_MODE_COLOR_SWEEP_RANDOM);
      //ws2812fx.setColor(0x42fe19);         // Effect 2: Fireworks
      break;
    case 2:
      ws2812fx.setMode(FX_MODE_RUNNING_RANDOM );
      //ws2812fx.setColor(0xe319fe);        // Effect 3: Color Wipe
      break;
    case 3:
      ws2812fx.setMode(FX_MODE_THEATER_CHASE_RAINBOW); // Effect 4: Theater Chase Rainbow
      break;
    case 4:
      ws2812fx.setMode(FX_MODE_FIREWORKS_RANDOM);
      ws2812fx.setColor(0x37bdf3);           // Effect 5: Twinkle
      break;
    case 5:
      ws2812fx.setMode(FX_MODE_CHASE_BLACKOUT_RAINBOW);
      //ws2812fx.setColor(0xffef00);          
      break;
    // case 6:
    //   ws2812fx.setMode(FX_MODE_RAIN);
    //   ws2812fx.setColor(0x3a6bf8);          
    //   break;
    // case 7:
    //   ws2812fx.setMode(FX_MODE_STROBE);
    //   ws2812fx.setColor(0x22fbe6);          
    //   break;
    // case 8:
    //   ws2812fx.setMode(FX_MODE_TWINKLE_FADE);
    //   ws2812fx.setColor(0xfb2278);          
    //   break;


  }
}
// Use this code if your have trouble with 1st LED (Show only 1 color and did not change color with efect)
// void clear1stLEDs() {
//   for (int i = 0; i < LED_COUNT; i++) {
//     ws2812fx.setPixelColor(i, ws2812fx.Color(0, 0, 0)); 
//   }
//   ws2812fx.show(); 
// }

void setup() {
  Serial.begin(115200);
  ws2812fx.init();
  ws2812fx.setBrightness(120);
  ws2812fx.setSpeed(200);
  ws2812fx.getModeName(currentEffect);
  ws2812fx.start();
  //clear1stLEDs();

}

void Readeffect(){
  int reading = digitalRead(EffectBTN);
    if (reading != lastState) {
    lastDebounceTime = millis(); 
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == HIGH ) {  
      currentEffect = (currentEffect + 1) % 6;  // Cycle through 9 effects (0 to 8)
      setEffect(currentEffect);  
    }
  }
    lastState = reading; 
}
void loop() {
  Readeffect();
  ws2812fx.service();
}
