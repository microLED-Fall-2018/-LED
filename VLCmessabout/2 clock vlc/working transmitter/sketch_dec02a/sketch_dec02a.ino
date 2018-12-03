// pin defines
#define LED_PIN 1
// transmit defines
#define NUM_DATA_BITS 8
#define WORD_LENGTH NUM_DATA_BITS+2
#define SYNC_SYMBOL 0b1000000001
#define EXIT_SYMBOL 0b0111111110
#define START_BIT 0b1
#define END_BIT 0b0
// timer defines
#define TIMER_PRESCALER_DIV 1024
#define CPU_HZ 48000000
#define SYMBOL_PERIOD 10

#define turnOnLED() digitalWrite(LED_PIN, LOW);
#define turnOffLED() digitalWrite(LED_PIN, HIGH);

int word_index = -1;
int buffer_index = 0;
unsigned int current_word = 0;
unsigned int word_buffer[38] = {0,0,0,0,0b111000010,0b1011100110,0b1011100110};

// function inits
void startTimer(int frequencyHz);
void setTimerFrequency(int frequencyHz);
void TC3_Handler();
void emit_bit();

bool LED_on = false;

void emit_word(unsigned int w) {
  if ( word_index >= 0) {
    unsigned char current_bit = w >> word_index;
    Serial.print(current_bit & 0x01);
    if ( current_bit & 0x01 ) {
      turnOffLED();
    } else {
      turnOnLED();
    }
    word_index--;
  }
}

void write_word(unsigned int w) {
  Serial.print("\nwriting word ");
  Serial.println(w, BIN);
  current_word = w;
  word_index = WORD_LENGTH-1;
}

void write_buffer() {
  if ( word_index < 0) {
    if(current_word == EXIT_SYMBOL)
      buffer_index = 0;
    if(buffer_index < 38) {
      Serial.print(" current index = ");
      Serial.println(buffer_index);
      write_word(word_buffer[buffer_index]);
      buffer_index++;
    } else {
      //memset(word_buffer, 0, sizeof word_buffer);
      //buffer_index = 0;
    }
  }
}


void write_string(String s) {
  
}

void emit_bit() {
  emit_word(current_word);
}

void init_frame(){
  memset(word_buffer, 0xAA, 4*4);   // fill first 4 bytes at pointer frame with 0xAA
  word_buffer[4] = SYNC_SYMBOL;  // 4th position is SYNC symbol
  // memcpy(&(frame[5]), data, data_size); // copy data into the 6th entry of frame and beyond
  word_buffer[5 + 2] = EXIT_SYMBOL;           // set the exit bit after 
}

void setup() {
  // put your setup code here, to run once:
  init_frame();
  Serial.begin(115200);
  while(!Serial){}
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  startTimer(SYMBOL_PERIOD);
}

void loop() {
  // put your main code here, to run repeatedly:
  write_buffer();
}


//----------------------------------BEGIN TIMER SETUP----------------------------------

void setTimerFrequency(int frequencyHz) {
  int compareValue = (CPU_HZ / (TIMER_PRESCALER_DIV * frequencyHz)) - 1;
  TcCount16* TC = (TcCount16*) TC3;
  // Make sure the count is in a proportional position to where it was
  // to prevent any jitter or disconnect when changing the compare value.
  TC->COUNT.reg = map(TC->COUNT.reg, 0, TC->CC[0].reg, 0, compareValue);
  TC->CC[0].reg = compareValue;
  //Serial.println(TC->COUNT.reg);
  //Serial.println(TC->CC[0].reg);
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

void TC3_Handler() {
  TcCount16* TC = (TcCount16*) TC3;
  // If this interrupt is due to the compare register matching the timer count
  // we toggle the LED.
  if (TC->INTFLAG.bit.MC0 == 1) {
    TC->INTFLAG.bit.MC0 = 1;
    // Write callback here!!!
    emit_bit();
  }
}
//----------------------------------END TIMER SETUP----------------------------------
