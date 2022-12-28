
#define led_1 13  // first led
#define led_2 12  // second led
#define led_3 11  // third led
#define led_4 10  //fourth
#define led_5 9   //fifth
#define led_6 8   //sixth

#define Sound_R A1  //right channel
#define Sound_L A2  //left channel

#define NSamples 128

uint16_t sample = 0;

float micLev;

void setup() {
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
  pinMode(led_6, OUTPUT);

  pinMode(Sound_R, INPUT);
  pinMode(Sound_L, INPUT);

  Serial.begin(115200);
}




void loop() {
  get_samples();

}
void get_samples() {
  int16_t micIn;
  uint8_t squelch = 5;  // Let's try a squelch value of 7.
  static uint16_t sample;

  micIn = analogRead(Sound_L);              // Sample the microphone. Range will result in 0 to 1023.
  micLev = ((micLev * 127) + micIn) / 128;  // Smooth it out over the last 128 samples.

  micIn = micIn - micLev;
  micIn = abs(micIn);

  sample = (micIn <= squelch) ? 0 : (sample + micIn) / 2;

  
 
  (sample < 10) ? digitalWrite(led_1, LOW) : digitalWrite(led_1, LOW);          
  (sample > 10) ? digitalWrite(led_1, HIGH) : digitalWrite(led_1, LOW);          
  (sample > 20) ? digitalWrite(led_2, HIGH) : digitalWrite(led_2, LOW);
  (sample > 30) ? digitalWrite(led_3, HIGH) : digitalWrite(led_3, LOW);
  (sample > 40) ? digitalWrite(led_4, HIGH) : digitalWrite(led_4, LOW);          
  (sample > 50) ? digitalWrite(led_5, HIGH) : digitalWrite(led_5, LOW);
  (sample > 60) ? digitalWrite(led_6, HIGH) : digitalWrite(led_6, LOW);

  Serial.print("MicIN:");
  Serial.println(micIn);
  Serial.print(",");
  Serial.print("Sample:");
  Serial.println(sample);
  Serial.print(",");
  Serial.print("Line:");
  Serial.print(50);
  Serial.println(" ");

}
