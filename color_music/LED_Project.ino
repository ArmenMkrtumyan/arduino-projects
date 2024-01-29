#define DECODE_NEC             // Includes Apple and Onkyo
#define LED_COUNT 207          //Number of LED's used
#define interval 100           // interval at which to blink in milliseconds   ---SOMETHING TO PLAY AROUND WITH
#define SAMPLES 128            //This value MUST ALWAYS be a power of 2.    ---IF YOU HAVE MORE RAM GO AHEAD AND INCREASE THIS NUMBER
#define SIGNAL_FREQUENCY 1000  //Next 3 are related and essential for FFT Library
#define SAMPLING_FREQUENCY 5000
#define AMPLITUDE 100
#define mic_l A2   //Microphone input 2 using the Capacitor 2 // #define mic_r A1 //Microphone input 1 using the Capacitor 1
#define squelch 2  // recommended range 2-7 ----- it is used for dropping low noises. ---SOMETHING TO PLAY AROUND WITH
#define HALF_COUNT (LED_COUNT / 2 - 1)
#define potPin A3    // Potentiometer output connected to analog pin 3
#define buttonPin 4  // the number of the pushbutton pin

#include "arduinoFFT.h"  //Library for Fast Fourier transforms with Arduino
#include <Arduino.h>
#include "PinDefinitionsAndMore.hpp"  // This include defines the actual pin number for pins like
#include <IRremote.hpp>               // IR_RECEIVE_PIN, IR_SEND_PIN for many different boards and architectures
#include <FastLED.h>                  //Library for efficiently controlling LED strips

CRGBArray<LED_COUNT> leds;  //creating an array for letter addressing of each LED

unsigned long previousMillis = 0;  // will store last time LED was updated
double max = 0;                    // max is the highest frequence over the given sample, its value changes every iteration
arduinoFFT FFT = arduinoFFT();     // Create FFT object

double vReal[SAMPLES];  //Array to store real value outputs of FFT
double vImag[SAMPLES];  //Array to store imaginary value outputs of FFT

int16_t micIn;    //Raw input from microphone
uint16_t sample;  //Final transformed output from micIn
float micLev;     //Used for smoothing micIn

int number_pressed = 0;
auto color = CRGB::Red;

int potVal = 0;           // Variable to store the input from the potentiometer
bool buttonState = true;  // variable for reading the pushbutton status

int mapValue(int inputValue, int inputMin, int inputMax, int outputMin, int outputMax) {
  // Make sure the input value is within the specified range
  inputValue = max(inputMin, min(inputValue, inputMax));

  // Scale the input value to the output range
  return static_cast<int>((static_cast<double>(inputValue - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin) + outputMin);
}

uint16_t get_sample()  //Getting sample output from the batch of 128 (SAMPLES)
{
  micIn = analogRead(mic_l);                            // Sample the microphone. Range will result in 0 to 1023.
  micLev = ((micLev * (SAMPLES - 1)) + micIn) / SAMPLES;  // Smooth it out over the last 128 SAMPLES.

  micIn = micIn - micLev;  //↓↓↓ There is never too much smoooooothing )))
  micIn = abs(micIn);

  sample = (micIn <= squelch) ? 1 : (sample + micIn) / 2;  // 0 was causing problems for calculations,

  // so the minimum value is 1 for sample
  return sample;
}


void setup() {

  // pinMode(mic_r, INPUT);
  pinMode(mic_l, INPUT);
  pinMode(buttonPin, INPUT);
  FastLED.addLeds<WS2812B, 7, GRB>(leds, LED_COUNT);  // Setting up the LED strip type, pin that it is connected,
                                                      // The color sequence, and the count
  FastLED.setBrightness(255);                         //yes, you are correct thats THE BRIGHTNESS !

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED

  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
  unsigned long currentMillis = millis();  // saving current time

  potVal = analogRead(potPin);  // read the potentiometer value at the input pin
  potVal = mapValue(potVal, 0, 1023, 0, 255);
  FastLED.setBrightness(potVal);
  // FastLED.setBrightness(200);

  if (IrReceiver.decode()) {
    IrReceiver.resume();  // Enable receiving of the next value
    number_pressed++;
    switch (number_pressed) {
      case 0:
        color = CRGB::Red;
        break;
      case 1:
        color = CRGB::Navy;
        break;
      case 2:
        color = CRGB::Lime;
        break;
      case 3:
        color = CRGB::MediumVioletRed;
        break;
      case 4:
        color = CRGB::Cyan;
        break;
      case 5:
        color = CRGB::DarkOrange;
        break;
      case 6:
        color = CRGB::FireBrick;
    }
    if (number_pressed == 6)
      number_pressed = number_pressed % 6;
  }

  buttonState = digitalRead(buttonPin);
  if (buttonState) {
    for (uint16_t i = 0; i < SAMPLES; i++)  //getting real and imaginary values
    {
      vReal[i] = get_sample();
      vImag[i] = 0.0;
    }
    if (currentMillis - previousMillis >= interval) {
      max = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
      //   //Example1
      uint16_t sample = get_sample();
      max = HALF_COUNT / 40 * sample;
      if (max > HALF_COUNT) max = HALF_COUNT;
      if (get_sample() < 2) max = 0;

    } else {
      max = 0;
    }
  } else {
    max = HALF_COUNT;
  }

  if (HALF_COUNT - (HALF_COUNT - max) != 0) {
    leds(HALF_COUNT, HALF_COUNT - max) = color;
    leds(LED_COUNT - 1, LED_COUNT / 2) = leds(0, HALF_COUNT);
  }

  FastLED.show();
  fill_solid(&(leds[0]), 300 /*number of leds*/, 0x000000);
}
