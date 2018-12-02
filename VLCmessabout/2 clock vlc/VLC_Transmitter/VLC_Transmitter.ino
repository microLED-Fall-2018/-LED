// change to alter communication speed, 
// will lower values will result in faster communication
// the receiver must be tuned to the same value
#define SYMBOL_PERIOD  10/* Defined a symbol period in hz*/

#define WORD_LENGTH 10 /* Each byte is encoded on 10-bit with start, byte, stop */
#define SYNC_SYMBOL 0xD5 /* Synchronization symbol to send after a preamble, before data communication happens */
#define SYNC_SYMBOL 0b1000000001
#define STOP_SYMBOL 0b0111111110
#define START_SYMBOL 0b1 // 10 high to low
#define EXIT_SYMBOL 0b0  // 01 low to high
#define DATA_SIZE 8
#define CPU_HZ 48000000
#define TIMER_PRESCALER_DIV 1024

void startTimer(int frequencyHz);
void setTimerFrequency(int frequencyHz);
void TC3_Handler();


//Fast manipulation of LED IO. 
//These defines are for a LED connected on D13
/*#define OUT_LED() DDRB |= (1 << 5);
#define SET_LED() PORTB |= (1 << 5)
#define CLR_LED() PORTB &= ~(1 << 5)
*/

//These defines are for a RGB led connected to D2, D3, D4
/*#define OUT_LED() DDRD |= ((1 << 2) | (1 << 3) | (1 << 4))
#define SET_LED() PORTD |= ((1 << 2) | (1 << 3) | (1 << 4))
#define CLR_LED() PORTD &= ~((1 << 2) | (1 << 3) | (1 << 4))
*/

//These defines are for a single led connected to D2
#define LED 1
//----------------------------------BEGIN TIMER SETUP----------------------------------

void setTimerFrequency(int frequencyHz) {
  int compareValue = (CPU_HZ / (TIMER_PRESCALER_DIV * frequencyHz)) - 1;
  TcCount16* TC = (TcCount16*) TC3;
  // Make sure the count is in a proportional position to where it was
  // to prevent any jitter or disconnect when changing the compare value.
  TC->COUNT.reg = map(TC->COUNT.reg, 0, TC->CC[0].reg, 0, compareValue);
  TC->CC[0].reg = compareValue;
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


unsigned int frame_buffer [38] ; //buffer for frame
int frame_index = -1; // index in frame
int frame_size = -1  ; // size of the frame to be sent

//state variables of the manchester encoder
unsigned int bit_counter = 0 ;
unsigned short data_word = 0 ;  //start + 8bit data + stop
unsigned long int byte_data ;

//emitter interrupt
void emit_bit(){
  if(frame_index != -1) {
    Serial.println(frame_index, DEC);
    Serial.println(frame_buffer[0]);
    //Serial.println(bit_counter);
    bit_counter -- ;
    if((byte_data >> bit_counter) & 0x01){
      digitalWrite(LED, LOW); // on
    }else{
      digitalWrite(LED, HIGH); // off
    }
    if(bit_counter == 0){   
      //is there still bytes to send in the frame ?
      //byte_data = 0xAAAA; // keep sending ones if nothing to send
      if(frame_index >= 0 ){
        Serial.println("word");
        frame_index++;
        bit_counter = WORD_LENGTH;
      }
    }
  }
}

void init_frame(unsigned int * frame){
  memset(frame, 0xAA, 4);   // fill first 4 bytes at pointer frame with 0xAA
  frame[4] = SYNC_SYMBOL;  // 4th position is SYNC symbol
}

#define START_MASK 0x1 << DATA_SIZE
int fill_frame(char * data, int data_size, unsigned int * frame){
  Serial.println("filling frame");
  int i;
  for (i = 0; i < data_size; i++) {
    data[i] = (data[i] | START_MASK) << 1; //STOP bit is 0
    Serial.println(data[i]);
  }
  memcpy(&(frame[5]), data, data_size); // copy data into the 6th entry of frame and beyond
  frame[5 + data_size] = STOP_SYMBOL;           // set the exit bit after 
  byte_data = frame_buffer[0];
  return 1 ;
}

inline int write(char * data, int data_size){
  if(frame_index >=  0) return -1;
  if(data_size > 32) return -1;
  fill_frame(data, data_size,frame_buffer); // copy data into frame
  frame_index = 0 ; // set frame index to 0
  frame_size = data_size + 6; // set frame size to the size of data + extra bits
                              // 4 bytes of 0xAA followed by
  return 0;
}

// check if anything is being trasmitted
int transmitter_available(){
  if(frame_index >=  0) return 0 ; // if the current index is greater than zero then something is being trasnsmitted
  return 1 ; 
}

char * msg = "Hello World" ;
char com_buffer [32] ;
char com_buffer_nb_bytes = 0 ;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  pinMode(LED, OUTPUT); // set LED pin to output
  digitalWrite(LED, LOW); // set LED to low
  init_frame(frame_buffer); // set first 3 bits of buffer to 0xAA, sync, and start symbol, reset frame_index and frame_size
  // start timer
  startTimer(SYMBOL_PERIOD); //SYMBOL_PERIOD bauds

  memcpy(com_buffer, msg, 11);
  com_buffer[11] = 1 + '0' ;
  write(com_buffer, 12);
}


void loop() {
  static int i = 0 ;
  memcpy(com_buffer, msg, 11);
  com_buffer[11] = i + '0' ;
  if(write(com_buffer, 12) < 0){
    delay(10);
  }else{
    i ++ ; 
    if(i > 9) i = 0 ;
  }
}
