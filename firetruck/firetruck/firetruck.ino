#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6

int ledsGesamt = 58;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledsGesamt, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint32_t blue = strip.Color(0, 0, 255);
uint32_t green = strip.Color(0,255, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t magenta = strip.Color(255, 0, 255);
uint32_t eg = strip.Color(250,167 , 0);
uint32_t off = strip.Color(0, 0 , 0);  
uint32_t white = strip.Color(127, 127, 127);
  
void setup() {
  Serial.begin(9600);
  strip.begin();
  //strip.setBrightness(128);
  strip.setBrightness(25);
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  delay(30);
/*  
  uint32_t blue = strip.Color(0, 0, 255);
  uint32_t green = strip.Color(0,255, 0);
  uint32_t red = strip.Color(255, 0, 0);
  uint32_t magenta = strip.Color(255, 0, 255);
  uint32_t eg = strip.Color(250,167 , 0);
  uint32_t off = strip.Color(0, 0 , 0);  
  uint32_t white = strip.Color(127, 127, 127);
  */
  //leftToRight(magenta, 50);
  //leftToRight(green, 5);
  //leftToRight(red, 50);
  
  
  // Some example procedures showing how to display to the pixels:
  //colorWipe(red, 20); // Red
  //colorWipe(strip.Color(0, 255, 0), 10); // Green
  //colorWipe(blue, 150); // Blue
  //colorWipe(eg, 30);

  //coolColorWipe(red,blue,20);
  
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 500); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue*/

  //rainbow(10);
  //rainbowCycle(5);
  //theaterChaseRainbow(5);
  
  //allColors(red, 500);
  //theWheel(50);
  
  //foo(red,blue,20);
  //foo(blue,red,20);
  //foo2(red,blue,20);
  //foo2(blue,red,20);
  //foo3(red,blue,20);
  //foo3(blue,red,20);
  //foo4(red,blue,20);
  //foo4(blue,red,20);
  
  sequence();
  //stropo(red, white, 20);
  
}

void sequence() {

  for(uint8_t i=0; i<5; i++) {
    foo4(red,blue, 20);
  }

  for(uint8_t i=0; i<15; i++) {
    stropo(red, white, 20);
  }

  for(uint8_t i=0; i<5; i++) {
    foo4(red,blue, 20);
  }
  
  uint8_t w = 100;
  for(uint8_t i=0; i<5; i++) {
    everyXth(red, white, 20, 3);
    delay(w);
    allOff();
    delay(w);
    everyXth(red, white, 20, 2);
    delay(w);
    allOff();
    delay(w);
    everyXth(red, white, 20, 1);
    delay(w);
    allOff();
    delay(w);
  }
}

void allOff(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

void everyXth(uint32_t c1,uint32_t c2, uint16_t wait, uint8_t x){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if(i%x==0) {
      strip.setPixelColor(i, c1);
    } else {
      strip.setPixelColor(i, c2);
    }
  }
  strip.show();
}

void stropo(uint32_t c1,uint32_t c2, uint16_t wait) {
  // all c1
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c1);
  }
  strip.show();

  delay(wait*6);
  
  // all off
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c2);
  }
  strip.show();
  delay(wait);
}

void foo4(uint32_t c1, uint32_t c2, uint16_t wait){
  // all c1
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c1);
  }
  strip.show();

  for(uint16_t i=0; i<strip.numPixels(); i++) {
      //strip.setPixelColor(strip.numPixels()/2-i, c2);
      strip.setPixelColor(i, c2);
      strip.setPixelColor(i+1, c2);
      strip.setPixelColor(i+2, c2);
      strip.setPixelColor(i+3, c2);
      if (i>0) strip.setPixelColor(i-1, c1);
      if (i>1) strip.setPixelColor(i-2, c1);
      if (i>2) strip.setPixelColor(i-3, c1);
      //if (i>3) strip.setPixelColor(i-4, c1);
      strip.show();
      delay(wait);
  }  
  
  for(uint16_t i=strip.numPixels(); i>0; i--) {
      //strip.setPixelColor(strip.numPixels()/2-i, c2);
      strip.setPixelColor(i, c2);
      strip.setPixelColor(i-1, c2);
      strip.setPixelColor(i-2, c2);
      strip.setPixelColor(i-3, c2);
      
      if (i<strip.numPixels()) strip.setPixelColor(i+1, c1);
      if (i-2<strip.numPixels()) strip.setPixelColor(i+2, c1);
      if (i-3<strip.numPixels()) strip.setPixelColor(i+3, c1);
      if (i-4<strip.numPixels()) strip.setPixelColor(i+4, c1);
      
      strip.show();
      delay(wait);
  }
}


void foo3(uint32_t c1, uint32_t c2, uint16_t wait){
  // all c1
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c1);
  }
  strip.show();

  for(uint16_t i=0; i<strip.numPixels(); i++) {
      //strip.setPixelColor(strip.numPixels()/2-i, c2);
      strip.setPixelColor(i, c2);
      strip.setPixelColor(i+1, c2);
      strip.setPixelColor(i+2, c2);
      strip.setPixelColor(i+3, c2);
      if (i>0) strip.setPixelColor(i-1, c1);
      if (i>1) strip.setPixelColor(i-2, c1);
      if (i>2) strip.setPixelColor(i-3, c1);
      //if (i>3) strip.setPixelColor(i-4, c1);
      strip.show();
      delay(wait);
  }      
}


void foo2(uint32_t c1, uint32_t c2, uint16_t wait){
  // all c1
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c1);
      //if (i+1<strip.numPixels())strip.setPixelColor(i+1, c2);
      
  }
  strip.show();

  for(uint16_t i=0; i<strip.numPixels()/2; i++) {
      strip.setPixelColor(strip.numPixels()/2-i, c2);
      strip.setPixelColor(strip.numPixels()/2+i, c2);
      strip.show();
      delay(wait);
  }      
}

void foo(uint32_t c1, uint32_t c2, uint16_t wait){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c1);
      if (i+1<strip.numPixels())strip.setPixelColor(i+1, c2);
      strip.show();
      delay(wait);
  }
}

// Fill the dots one after the other with a color
void leftToRight(uint32_t c, uint16_t wait) {
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      if (i+1<strip.numPixels()){
        strip.setPixelColor(i+1, c);  
      }

      if (i>0) {
        strip.setPixelColor(i-1, 0);  
      }
      
      strip.show();
      delay(wait);
  }
/*
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
      strip.show();
      delay(wait);
  }
  */
}

void theWheel(uint16_t wait){
  for (uint16_t r=0; r<255;r++){
    //for (uint16_t g=0; g<255;g++){
     // for (uint16_t b=0; b<255;b++){
          
      
      Serial.print(r);      
      Serial.print("\t"); 
      //Serial.print(g);
      //Serial.print("\t"); 
      //Serial.print(b); 
      Serial.print("\n"); 
      
        //allColors(strip.Color(r, r, r), wait);
        //allColors(Wheel(r), wait);
      //}
    //}
  }
}
void allColors(uint32_t c, uint16_t wait) {
  
  for(uint16_t i=0; i<=strip.numPixels(); i++) {    
      strip.setPixelColor(i, c);
  }

  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color
void coolColorWipe(uint32_t first, uint32_t scnd, uint16_t wait) {
  
  for(uint16_t i=0; i<=strip.numPixels(); i++) {
      strip.setPixelColor(i, first);
      //strip.setPixelColor(strip.numPixels()-i, c);      
      strip.show();
      delay(wait);
  }

  for(uint16_t i=0; i<=strip.numPixels(); i++) {     
      strip.setPixelColor(i, scnd);          
      strip.show();
      delay(wait);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  
  for(uint16_t i=0; i<=strip.numPixels(); i++) {
      /*Serial.print(i);
      Serial.print(" "); 
      Serial.print(strip.numPixels()-i);      
      Serial.print("\t"); 
      Serial.print("\n"); 
      */
      strip.setPixelColor(i, c);
      //strip.setPixelColor(strip.numPixels()-i, c);      
      strip.show();
      delay(wait);
  }

  for(uint16_t i=0; i<=strip.numPixels(); i++) {     
      strip.setPixelColor(i, 0);          
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels()/2; i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      strip.setPixelColor(strip.numPixels()-i, Wheel((i+j) & 255));      
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels()/2; i++) {
      strip.setPixelColor(strip.numPixels()/2-i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip.setPixelColor(strip.numPixels()/2+i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));      
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<40; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels()/2; i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
        strip.setPixelColor(strip.numPixels()-(i+q), c);    //turn every third pixel on        
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels()/2; i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
        strip.setPixelColor(strip.numPixels()-(i+q), 0);        //turn every third pixel off        
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels()/2; i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
          strip.setPixelColor(strip.numPixels()-(i+q), Wheel( (i+j) % 255));    //turn every third pixel on          
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels()/2; i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
          strip.setPixelColor(strip.numPixels()-(i+q), 0);        //turn every third pixel off          
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

