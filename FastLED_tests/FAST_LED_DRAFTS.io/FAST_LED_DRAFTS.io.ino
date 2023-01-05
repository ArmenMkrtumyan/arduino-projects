
  //for(int dot = 0; dot<LED_COUNT; dot++)
  //{
    //_________________________________________
    
    //RAINBOW EFFECTS WITH HALFFFFFF!!!!!!!!!!!!!!!
    
    //Example 1
    // static uint8_t hue=0; leds.fill_rainbow(hue++); FastLED.delay(30);
    
    //Example 2
    // static uint8_t hue=0;
    // leds(LED_COUNT/2 - 1,0).fill_rainbow(hue++);  // fill the first 150 items with a rainbow
    // leds(LED_COUNT-1, LED_COUNT/2) = leds(0,LED_COUNT/2-1);
    // FastLED.delay(30);
    
    //Example 3
    // static uint8_t hue=0;
    // leds(LED_COUNT/2 - 1,0) = CRGB(hue++, 0, 0);  // fill the first 150 items with a rainbow
    // leds(LED_COUNT-1, LED_COUNT/2) = leds(0,LED_COUNT/2-1);
    // FastLED.delay(30);
    
    //_______________________________________

    //FADING ALGORITHM

    // if(!leds[dot] && dot != 299){
    //   leds[dot] = CRGB::Red;
    // //  FastLED.show();
    //   if(dot<50){
    //     dot = 0;
    //   }
    //   else if(dot < 100){
    //     dot = 50;
    //   }
    //   else if(dot < 150){
    //     dot = 100;
    //   }
    //   else if(dot<200){
    //     dot = 150;
    //   }
    //   else if(dot<250){
    //     dot = 200;
    //   }
    //   else if(dot<300)
    //   {
    //     dot = 250;
    //   }
    // }
    // else if(dot == 299){
    //   while(true){
    //     fill_solid( &(leds[0]), 299 /*number of leds*/, 0xFFFF00);
    //     FastLED.show(); 
    //   }
    // }
    // else
    // {
    //   leds[dot].fadeLightBy(50);
    // //  FastLED.show();

    // }
    // FastLED.show();
  
  //_______________________________________

  //MOVING LINE
  // fill_solid( &(leds[dot]), 10 /*number of leds*/, 0xFF0000);
  // FastLED.show();
  // fill_solid( &(leds[dot]), 10 /*number of leds*/, CRGB::Black);
  
  //__________________________________________

  //MOVING RAINBOW
	//fill_rainbow( &(leds[dot]), 30 /*led count*/, 100 /*starting hue*/);
  //FastLED.show();
  //leds[dot] = CRGB::Black;
  //delay(100);

  //__________________________________________

  //COLLOR_SETTING
   //Example 1: set color from red, green, and blue components individually
  // leds[i].red =    50;
  // leds[i].green = 100;
  // leds[i].blue =  150;

  // //Example 2: set color from red, green, and blue components all at once
  // leds[i] = CRGB( 50, 100, 150);
  // // Example 3: set color via 'hex color code' (0xRRGGBB)
  // leds[i] = 0xFF007F;

  // // Example 4: set color via any named HTML web color
  // leds[i] = CRGB::HotPink;

  // // Example 5: set color via setRGB
  // leds[i].setRGB( 50, 100, 150);

  //__________________________________________
  
  // HSV  

  // Conversion to RGB is automatic.
  // leds[dot] = CHSV( 160, 255, 255);
  // FastLED.show();
  // leds[dot] = CRGB::Black;
  // delay(100);
  // alternate syntax
  //leds[i].setHSV( 160, 255, 255);

  // set color to a pure, bright, fully saturated, hue
  //leds[i].setHue( 160);

  //_______________________________________

  // Test if a color is lit at all (versus pure black)
  // if( leds[i] ) {
  //   /* it is somewhat lit (not pure black) */
  // } else {
  //   /* it is completely black */
  // }

  //_________________________________________

  //ADDING AND SUBSTRACTING COLORS  

  // Add one CRGB color to another.
  // leds[i] += CRGB( 20, 0, 0);

  // // Add a constant amount of brightness to all three (RGB) channels.
  // leds[i].addToRGB(20);

  // // Add a constant "1" to the brightness of all three (RGB) channels.
  // leds[i]++;


  // // Subtract one color from another.
  // leds[i] -= CRGB( 20, 0, 0);

  // // Subtract a contsant amount of brightness from all three (RGB) channels.
  // leds[i].subtractFromRGB(20);

  // // Subtract a constant "1" from the brightness of all three (RGB) channels.
  // leds[i]--;
    
  //______________________________________  
    // leds[dot] = CRGB(90,0,10); //White
    // FastLED.show();
    // //leds[dot] = CRGB::Black;
    // delay(50);

  //}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
