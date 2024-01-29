// #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
// #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

#include "arduinoFFT.h"

unsigned long previousMillis = 0;     // will store last time LED was updated
const long interval = 100;           // interval at which to blink (millisecond
double max = 0;

#define led_1 13  // first led
#define led_2 12  // second led
#define led_3 11  // third led
#define led_4 10  //fourth
#define led_5 9   //fifth
#define led_6 8   //sixth

arduinoFFT FFT = arduinoFFT();  // Create FFT object

const uint16_t samples = 128;  //This value MUST ALWAYS be a power of 2
const double signalFrequency = 1000;
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;

double vReal[samples];
double vImag[samples];

bool should_be_zero = false;

#define mic_r A1
#define mic_l A2

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void setup() {

  // sbi(ADCSRA, ADPS2);
  // cbi(ADCSRA, ADPS1);
  // cbi(ADCSRA, ADPS0);

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
  pinMode(led_6, OUTPUT);

  pinMode(mic_r, INPUT);
  pinMode(mic_l, INPUT);

  Serial.begin(115200);
  
}

// void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
// {
//    for (uint16_t i = 0; i < bufferSize; i++)
//    {
//       double abscissa;
//       /* Print abscissa value */
//       switch (scaleType)
//       {
//          case SCL_INDEX:
//          abscissa = (i * 1.0);
//       break;
//       case SCL_TIME:
//          abscissa = ((i * 1.0) / samplingFrequency);
//       break;
//       case SCL_FREQUENCY:
//          abscissa = ((i * 1.0 * samplingFrequency) / samples);
//       break;
//    }
//    Serial.print(abscissa, 6);
//    if(scaleType==SCL_FREQUENCY)
//       Serial.print("Hz");
//       Serial.print(" ");
//       Serial.println(vData[i], 4);
//    }
//    Serial.println();
// }

int16_t micIn;
uint8_t squelch = 5;  // Let's try a squelch value of 7.
static uint16_t sample;
float micLev;

uint16_t get_sample()
{
    micIn = analogRead(mic_l);              // Sample the microphone. Range will result in 0 to 1023.
    micLev = ((micLev * 127) + micIn) / 128;  // Smooth it out over the last 128 samples.

    micIn = micIn - micLev;
    micIn = abs(micIn);

    sample = (micIn <= squelch) ? 1 : (sample + micIn) / 2;
    //Serial.println(sample);
    return sample;

}

void loop() {
  unsigned long currentMillis = millis();

  /* Build raw data */
  //Serial.println("____________");
   // Number of signal cycles that the sampling will read
   //double cycles = (((samples-1) * signalFrequency) / samplingFrequency);

   for (uint16_t i = 0; i < samples; i++)
   {

  
      /* Build data with positive and negative values*/
      vReal[i] = get_sample();
      // (vReal[i] < 2) ? should_be_zero = true : should_be_zero = false;
      //Serial.println(micLev);
      //vReal[i] = uint8_t((amplitude * (sin((i * (twoPi * cycles)) / samples) + 1.0)) / 2.0);
      /* Build data displaced on the Y axis to include only positive values*/
      /* Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows */
      vImag[i] = 0.0;
    
   }
   



   /* Print the results of the simulated sampling according to time */
  //  Serial.println("Data:");
  //  PrintVector(vReal, samples, SCL_TIME);

   /* Weigh data */
  // FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  //  Serial.println("Weighed data:");
  //  PrintVector(vReal, samples, SCL_TIME);
  // FFT.Compute(vReal, vImag, samples, FFT_FORWARD); //Compute FFT
  //  Serial.println("Computed Real values:");
  //  PrintVector(vReal, samples, SCL_INDEX);
  //  Serial.println("Computed Imaginary values:");
 //  PrintVector(vImag, samples, SCL_INDEX);
  //  FFT.ComplexToMagnitude(vReal, vImag, samples); // Compute magnitudes
  //   Serial.println("Computed magnitudes:");
  // //   PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
 if (currentMillis - previousMillis >= interval) {

    max = FFT.MajorPeak(vReal, samples, samplingFrequency);

    if(get_sample() < 2) max = 0;

  (max > 200) ? digitalWrite(led_1, HIGH) : digitalWrite(led_1, LOW);
  (max > 600 ) ? digitalWrite(led_2, HIGH) : digitalWrite(led_2, LOW);
  (max > 1000 ) ? digitalWrite(led_3, HIGH) : digitalWrite(led_3, LOW);
  (max > 1400 ) ? digitalWrite(led_4, HIGH) : digitalWrite(led_4, LOW);
  (max > 1800 ) ? digitalWrite(led_5, HIGH) : digitalWrite(led_5, LOW);
  (max > 2200) ? digitalWrite(led_6, HIGH) : digitalWrite(led_6, LOW);


    Serial.print("MAX:");
    Serial.print(max);  
    Serial.print(",");
    Serial.print("Line:");
    Serial.print( 2500);
    Serial.println(" ");
     
 }
 else
 {
   max = 0;

   Serial.print("MAX:");
    Serial.print(max);  
    Serial.print(",");
    Serial.print("Line:");
    Serial.print( 2500);
    Serial.println(" ");
 }



// if (currentMillis - previousMillis >= interval) {

// // //MODE 1
//   (max < 200) ? digitalWrite(led_1, LOW) : digitalWrite(led_1, LOW);
//   (max > 200 && max < 600) ? digitalWrite(led_1, HIGH) : digitalWrite(led_1, LOW);
//   (max > 600 && max < 1000) ? digitalWrite(led_2, HIGH) : digitalWrite(led_2, LOW);
//   (max > 1000 && max < 1400) ? digitalWrite(led_3, HIGH) : digitalWrite(led_3, LOW);
//   (max > 1400 && max < 1800) ? digitalWrite(led_4, HIGH) : digitalWrite(led_4, LOW);
//   (max > 1800 && max < 2200) ? digitalWrite(led_5, HIGH) : digitalWrite(led_5, LOW);
//   (max > 2200) ? digitalWrite(led_6, HIGH) : digitalWrite(led_6, LOW);

//   previousMillis = currentMillis;
// }

//MODE 2
  // (max < 200) ? digitalWrite(led_1, LOW) : digitalWrite(led_1, LOW);
  // (max > 200) ? digitalWrite(led_1, HIGH) : digitalWrite(led_1, LOW);
  // (max > 600 ) ? digitalWrite(led_2, HIGH) : digitalWrite(led_2, LOW);
  // (max > 1000 ) ? digitalWrite(led_3, HIGH) : digitalWrite(led_3, LOW);
  // (max > 1400 ) ? digitalWrite(led_4, HIGH) : digitalWrite(led_4, LOW);
  // (max > 1800 ) ? digitalWrite(led_5, HIGH) : digitalWrite(led_5, LOW);
  // (max > 2200) ? digitalWrite(led_6, HIGH) : digitalWrite(led_6, LOW);

  // delay(50);

//MODE #3
  // (max < 200) ? digitalWrite(led_1, LOW) : digitalWrite(led_1, LOW);
  // (max > 200) ? digitalWrite(led_1, HIGH) : digitalWrite(led_1, LOW);
  // (max > 600 ) ? digitalWrite(led_2, HIGH) : digitalWrite(led_2, LOW);
  // (max > 1000 ) ? digitalWrite(led_3, HIGH) : digitalWrite(led_3, LOW);
  // (max > 1400 ) ? digitalWrite(led_4, HIGH) : digitalWrite(led_4, LOW);
  // (max > 1800 ) ? digitalWrite(led_5, HIGH) : digitalWrite(led_5, LOW);
  // (max > 2200) ? digitalWrite(led_6, HIGH) : digitalWrite(led_6, LOW);




}
