#include <FastLED.h>        //Library for efficiently controlling LED strips
#include "arduinoFFT.h"     //Library for Fast Fourier transforms with Arduino

#define LED_COUNT 300       //Number of LED's used
#define mic_r A1            //Microphone input 1 using the Capacitor 1
#define mic_l A2            //Microphone input 2 using the Capacitor 2

//CRGB leds[LED_COUNT]; 
CRGBArray<LED_COUNT> leds;    //creating an array for letter addressing of each LED

unsigned long previousMillis = 0;     // will store last time LED was updated
const long interval = 100;            // interval at which to blink in milliseconds   ---SOMETHING TO PLAY AROUND WITH
double max = 0;                       // max is the highest frequence over the given sample, its value changes every iteration
arduinoFFT FFT = arduinoFFT();        // Create FFT object

const uint16_t samples = 128;  //This value MUST ALWAYS be a power of 2.    ---IF YOU HAVE MORE RAM GO AHEAD AND INCREASE THIS NUMBER
const double signalFrequency = 1000;        //Next 3 are related and essential for FFT Library
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;

double vReal[samples];            //Array to store real value outputs of FFT
double vImag[samples];            //Array to store imaginary value outputs of FFT

int16_t micIn;        //Raw input from microphone
uint8_t squelch = 5;  // recommended range 2-7 ----- it is used for dropping low noises. ---SOMETHING TO PLAY AROUND WITH
static uint16_t sample;   //Final transformed output from micIn
float micLev;             //Used for smoothing micIn

uint16_t get_sample()       //Getting sample output from the batch of 128
{
    micIn = analogRead(mic_l);              // Sample the microphone. Range will result in 0 to 1023.
    micLev = ((micLev * (samples-1)) + micIn) / samples;  // Smooth it out over the last 128 samples.

    micIn = micIn - micLev;         //↓↓↓ There is never too much smoooooothing )))
    micIn = abs(micIn);             

    sample = (micIn <= squelch) ? 1 : (sample + micIn) / 2;   // 0 was causing problems for calculations, 
                                                              // so the minimum value is 1 for sample  

    return sample;

}

void setup() {

  pinMode(mic_r, INPUT);
  pinMode(mic_l, INPUT);

  Serial.begin(115200); 

  FastLED.addLeds<WS2812B, 7, GRB>(leds, LED_COUNT);     // Setting up the LED strip type, pin that it is connected, 
                                                         // The color sequence, and the count

  FastLED.setBrightness(200); //yes, you are correct thats THE BRIGHTNESS !

}

void loop()
{
  unsigned long currentMillis = millis();    // saving current time

  for (uint16_t i = 0; i < samples; i++)      //getting real and imaginary values
  {
    vReal[i] = get_sample();
    vImag[i] = 0.0;
  }
  if (currentMillis - previousMillis >= interval) {

    max = FFT.MajorPeak(vReal, samples, samplingFrequency);

    //Example1
    uint16_t sample = get_sample();
    max = 149 / 40 * sample;
    if(max > 149) max = 149;
    if(get_sample() < 2) max = 0;

    //Example2
    //max = map(max, 0, 2520, 0, 149);

    //Rainbow Code
    //fill_rainbow( leds(LED_COUNT/2 - 1,LED_COUNT/2 - 1 - max), max /*led count*/, 100 /*starting hue*/);
    
    if((LED_COUNT/2 - 1) - (LED_COUNT/2 - 1 - max ))
    {
      if((LED_COUNT/2 - 1) - (LED_COUNT/2 - 1 - max ) != 0) leds(LED_COUNT/2 - 1,LED_COUNT/2 - 1 - max) = CRGB::Purple;
      leds(LED_COUNT-1, LED_COUNT/2) = leds(0,LED_COUNT/2-1);
    }
    
    FastLED.delay(1);
    fill_solid( &(leds[0]), 300 /*number of leds*/, 0x000000);
  }
  else
  {
    max = 0;
  }
}
