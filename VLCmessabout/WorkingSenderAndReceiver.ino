//#define R_LED_PIN 7
#define R_LED_PIN 7
#define G_LED_PIN 6
#define B_LED_PIN 5
#define ANODE_PIN 8

#define CPU_HZ 48000000 //48MH
#define TIMER_PRESCALER_DIV 1024
const int AMBIENT_SAMPLES = 4;
const unsigned int TIMEOUT = 10000;
const unsigned int THRESH_INC = 200;
/* VLC STEPS
   RECEIVER:
   Calibration:
   1) Use method described bellow to detect 1 or 0
   2) Take 4*x samples (either from counter or ADC) and average them to determine ambient light
   Read LED (Option 1):
   1) Apply reverse bias to "charge" diode
   2) Digital read should see 1 at this point
   3) Loop and increment a counter until digital read sees a 0
   4) On digital read 0 return counter from read
   Read LED (Option 2):
   1) Apply reverse bias to "charge" diode
   2) Have ADC measure 4x times while diode discharges
   3) Return average
   Read Bit:
   1) Run calibration
   2) Read LED
   3) Determine if it's above or below ambient threshold from calibration
      - If less than threshold LED was on         = 1
      - If greater than threshold LED was off     = 0
   Synchronization:
   1) If two bits in series are read as the same value there is desync
   2) Rerun ambient light calibration.
   3) Continue reading.

   Transmitter:
   Be a flashy boy on a predetermined interval frequency matching receiver
*/

void calibrate(); // record ambient light levels to determine threshold
int readLED(); // apply reverse bias and count down
void startTimer(int frequencyHz); // start timer using provided frequency
void setTimerFrequency(int frequencyHz); // tune timer to desired frequency
void TC3_Handler(); // handler for timer event

int ambient;

unsigned int sequence_length = 8;
int sequence [] = { 1, 1, 0, 0, 1, 1, 0, 0};

void setup() {
  int frequency = 16000;
  // A4 Anode
  // A5 Cathode
  pinMode(13, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(R_LED_PIN, OUTPUT);
  // transmitter
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  //receiver
  digitalWrite(1, HIGH);
  digitalWrite(0, LOW);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, LOW);
  Serial.begin(9600);
  while (!Serial) {}
  digitalWrite(A4, LOW);
  //pinMode(B_LED_PIN, OUTPUT);
  //pinMode(G_LED_PIN, OUTPUT);
  //pinMode(ANODE_PIN, OUTPUT);
  //digitalWrite(ANODE_PIN, HIGH);
  // TODO: set up pixel

  Serial.print("Frequency per bit: ");
  Serial.println(frequency/2);
  calibrate();
  delay(3000);

  startTimer(frequency);
}

int counter = 0;
bool isRead = false;
int read = 0;

void loop() {
  /*
  //startTimer(10);
  if (isRead)
  {
    digitalWrite(A4, LOW);
    int read = readLED();
    //Serial.println(read);
    if (read > ambient + 12)
    {
      //Serial.println(1);
      digitalWrite(13, HIGH);
    } else if (read < ambient - 12)
    {
      //Serial.println(0);
      digitalWrite(13, LOW);
    }
    isRead = false;
  } else
  {
    if(counter == 0)
    {
      pinMode(A5, OUTPUT);
      digitalWrite(A5, LOW);
      digitalWrite(A4, HIGH);

    }
    
    if (counter > 10) {
      isRead = true;
      counter = 0;
    }
    else
      counter++;
  }
  */
}


void calibrate()
{
  int i;
  ambient = 0;
  for (i = 0; i < AMBIENT_SAMPLES/2; i++)
  {
    ambient += readLED() / AMBIENT_SAMPLES;
  }

  digitalWrite(0, HIGH);

  for (i; i < AMBIENT_SAMPLES; i++)
  {
    ambient += readLED() / AMBIENT_SAMPLES;
  }

  digitalWrite(0, LOW);

  Serial.print("ambient: ");
  Serial.println(ambient);
}

int readLED()
{
  int i;
  int time = 0;

  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);

  pinMode(A5, INPUT);
  digitalWrite(A5, LOW);

  for (i = 0; i < 8; i++)
  {
    time += analogRead(A5) / 8;
  }
  
  Serial.print(time);
  Serial.print(" ");
  return time;

  return time;
}


  // - Timer -

void setTimerFrequency(int frequencyHz) {
  //frequency = f_clock / (Prescaler * (top + 1))
  int top = (CPU_HZ / (TIMER_PRESCALER_DIV * frequencyHz)) - 1;
  TcCount16* TC = (TcCount16*) TC3;
  // Make sure the count is in a proportional position to where it was
  // to prevent any jitter or disconnect when changing the compare value.
  TC->COUNT.reg = map(TC->COUNT.reg, 0, TC->CC[0].reg, 0, top);
  TC->CC[0].reg = top;
  Serial.println(TC->COUNT.reg);
  Serial.println(TC->CC[0].reg);
  while (TC->STATUS.bit.SYNCBUSY == 1);
}


void startTimer(int frequencyHz) {
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 ); // wait for sync

  TcCount16* TC = (TcCount16*) TC3;

  TC->CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  // Use the 16-bit timer
  TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  // Use match mode so that the timer counter resets when the count matches the compare register
  TC->CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  // Set prescaler to 1024
  TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  setTimerFrequency(frequencyHz);

  // Enable the compare interrupt
  TC->INTENSET.reg = 0;
  TC->INTENSET.bit.MC0 = 1;

  NVIC_EnableIRQ(TC3_IRQn);

  TC->CTRLA.reg |= TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
}

int countTrans= 0;
bool isTrans = false;

void TC3_Handler() {
  //Serial.print("Time: ");
  //Serial.println(millis());
  TcCount16* TC = (TcCount16*) TC3;
  // If this interrupt is due to the compare register matching the timer count
  // we toggle the LED.
  if (TC->INTFLAG.bit.MC0 == 1) {
    TC->INTFLAG.bit.MC0 = 1;
    // begin playback

    
    if(isRead)
    {
      //Serial.println("Timer Read:");
      //Serial.print("[0]: ");
      read = readLED();
      if (read > ambient + 12)
      {
        //Serial.println(1);
        Serial.println("\t 1");
        digitalWrite(13, HIGH);
      } else if (read < ambient - 12)
      {
        Serial.println("\t 0");
        //Serial.println(0);
        digitalWrite(13, LOW);
      }

      if(counter == 8)
      {
        counter = 0;
        Serial.println("");
      }
      isRead = false;
    } else
    {
      //Serial.print("[1]: ");
      //readLED();

      pinMode(0, sequence[counter] == 1 ? LOW : HIGH);
      counter ++;
      
      //pinMode(A5, OUTPUT);
      //digitalWrite(A5, LOW);
      //digitalWrite(A4, HIGH);
      isRead = true;
      //digitalWrite(0, LOW);
    }
  }
}
