int pin_led = 13; //13         //led pin
int potentiometer = A3;  //potentiometer pin

int Upper = 12;
int UpperRight = 11;
int UpperLeft = 10;
int Middle = 9; // 9
int Lower = 8;
int LowerRight = 7;
int LowerLeft = 6;

int number;

void setup() {

  
  pinMode(pin_led, OUTPUT);
  pinMode(Upper, OUTPUT);
  pinMode(UpperRight, OUTPUT);
  pinMode(UpperLeft, OUTPUT);
  pinMode(Middle, OUTPUT);
  pinMode(Lower, OUTPUT);
  pinMode(LowerRight, OUTPUT);
  pinMode(LowerLeft, OUTPUT);

  Serial.begin(9600);

}

int return_scaled(int input, int output, int potentiometer_value) {
  return (potentiometer_value / (input / output));
}

void turnOff()
{
  for (int i = 6; i<=12; i++)
  {
    digitalWrite(i, 0);
  }
}

void zero()
{
  for (int i = 6; i<=12; i++)
  { 
    if (i != 9)
    {
      digitalWrite(i, HIGH);
    }
  }
}

void one() 
{
  digitalWrite(UpperRight, HIGH);
  digitalWrite(LowerRight, HIGH);
}

void two()
{
  for (int i = 6; i<=12; i++)
  { 
    if ((i != 10) && (i != 7))
    {
      digitalWrite(i, HIGH);
    }
  }
}

void three()
{
  for (int i = 6; i<=12; i++)
  { 
    if ((i != 10) && (i != 6))
    {
      digitalWrite(i, HIGH);
    }
  }
}

void four()
{
  for (int i = 6; i<=12; i++)
  { 
    if ((i != 12) && (i != 8) && (i != 6))
    {
      digitalWrite(i, HIGH);
    }
  }
}

void five()
{
  for (int i = 6; i<=12; i++)
  { 
    if ((i != 11) && (i != 6))
    {
      digitalWrite(i, HIGH);
    }
  }
}

void six()
{
  for (int i = 6; i<=12; i++)
  { 
    if (i != 11)
    {
      digitalWrite(i, HIGH);
    }
  }
}

void seven()
{
  for (int i = 6; i<=12; i++)
  { 
    if ((i != 10) && (i != 9) && (i != 8) && (i != 6))
    {
      digitalWrite(i, HIGH);
    }
  }
}

void eight()
{
  for (int i = 6; i<=12; i++)
  { 
    digitalWrite(i, HIGH);
  }
}

void nine()
{
  for (int i = 6; i<=12; i++)
  { 
    if (i != 6)
    {
      digitalWrite(i, HIGH);
    }
  }
}



void loop() {
  turnOff();
  analogWrite(pin_led, return_scaled(1024, 256, analogRead(potentiometer)));
  number = return_scaled(1024, 9, analogRead(potentiometer));
  Serial.println(number);
  switch(number)
  {
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
  }
  delay(1);
}
