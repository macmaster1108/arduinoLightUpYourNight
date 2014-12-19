//LIGHT UP YOUR NIGHT!
//Arduino embedded system LED backlights
//by Stephen Keller CSE321 Fall 2014
//with help from SparkFun Electronics code
//please see presentation for full reference list
//Thanks!
//see more at macmaster1108.tumblr.com

const int RED_PIN = 9;//RGB
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int WHITE_PIN=8;
const int MicPin = 0;//Analog 0
int mode =0;
int modes=9;
int sensitivity;
int potpin =1;

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;


/////////////////////////////////////////////////////////////
void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(WHITE_PIN,OUTPUT);
  attachInterrupt(0,modechange,RISING);
}
/////////////////////////////////////////////////////////////

void loop()
{
  switch ( mode ) {
  case 0:
    standby();
    break;
  case 1:
    red();
    break;
  case 2:
    green();
    break;
  case 3:
    blue();
    break;
  case 4:
    yellow();
    break;
  case 5:
    cyan();
    break;
  case 6:
    purple();
    break;
  case 7:
    white();
    break;
  case 8:
    showSpectrum();
    break;
  case 9:
    music();
    break;  
  }
}
/////////////////////////////////////////////////////////////

void modechange(){
  delay(1000);//switch debounce
  if(mode<modes){
    mode++;
  }
  else{
    mode=0;
  }

}

void standby(){
  // All LEDs off, waiting for input
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

}
void red(){
  // Red (turn just the red LED on):
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}
void green(){
  // Green (turn just the green LED on):
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
}
void blue(){
  // Blue (turn just the blue LED on):
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
}
void yellow(){
  // Yellow (turn red and green on):
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
}
void cyan(){
  // Cyan (turn green and blue on):
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
}
void purple(){
  // Purple (turn red and blue on):
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
}
void white(){
  // White (turn all the LEDs on):
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
}

void showSpectrum()
{
  int x;  
  for (x = 0; x < 768; x++)
  {
    showRGB(x);  // Call RGBspectrum() with our new x
    delay(1);   // Delay for 10 ms (1/100th of a second)
  }
}

void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  if (color <= 255)          // zone 1
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)     // zone 2
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 255 - (color - 256); // green on to off
    blueIntensity = (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 512);         // red off to on
    greenIntensity = 0;                   // green is always off
    blueIntensity = 255 - (color - 512);  // blue on to off
  }

  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
}
 

void music() {
  digitalWrite(WHITE_PIN, HIGH);

  int potvalue;
  potvalue= analogRead(potpin);

  unsigned long startMillis= millis(); // Start of sample window
  unsigned int peakToPeak = 0; // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(MicPin);
    if (sample < 1024) // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample; // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample; // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin; // max - min = peak-peak amplitude
  double volts = (peakToPeak * 3.3) / 1024; // convert to volts

  if(volts>0.05&&volts<=0.08){
    digitalWrite(GREEN_PIN,HIGH);
  }
  else if(volts>0.08&&volts<=0.12){
    digitalWrite(BLUE_PIN,HIGH);
    digitalWrite(GREEN_PIN,HIGH);
  }
  else if(volts>0.12&&volts<=0.17){
    digitalWrite(BLUE_PIN,HIGH);
  }
  else if(volts>0.17&&volts<=0.21){
    digitalWrite(BLUE_PIN,HIGH);
    digitalWrite(RED_PIN,HIGH);
  }
  else if(volts>0.21){
    digitalWrite(RED_PIN,HIGH);
  }
  delay(potvalue);
  digitalWrite(RED_PIN,LOW);
  digitalWrite(BLUE_PIN,LOW);
  digitalWrite(GREEN_PIN,LOW);
  digitalWrite(WHITE_PIN, LOW);
}









