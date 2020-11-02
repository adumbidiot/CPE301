#define DECL_REG_U8(name, addr) volatile unsigned char* name = (volatile unsigned char*) addr;
#define DECL_REG_U16(name, addr) volatile unsigned int* name = (volatile unsigned int*) addr;

#define SET_OUTPUT(port, pin) *port |= (0x01 << pin);
#define SET_HIGH(port, pin)  *port |= (0x01 << pin);
#define SET_LOW(port, pin)  *port &= ~(0x01 << pin);

DECL_REG_U8(myTCCR1B, 0x81);
DECL_REG_U16(myTCNT1, 0x84);
DECL_REG_U8(myTIFR1, 0x36);

DECL_REG_U8(myPORTB, 0x25);
DECL_REG_U8(myDDRB, 0x24);
DECL_REG_U8(myPINB, 0x23);

unsigned int freq = 0;

void my_delay(unsigned int freq)
{
  double period = 1.0 / double(freq);
  double half_period = period / 2.0f;
  double clk_period = 0.0000000625;
  unsigned int ticks = half_period / clk_period;
  *myTCCR1B &= 0xF8;
  *myTCNT1 = (unsigned int) (65536 - ticks);
  *myTCCR1B |= 0b00000001;
  while((*myTIFR1 & 0x01)==0);
  *myTCCR1B &= 0xF8;       
  *myTIFR1 |= 0x01;
}

void setup() {
  SET_OUTPUT(myDDRB, 6);
  
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    unsigned char in_char = Serial.read();
    switch(in_char) {
      case 'A':
        freq = 440;
        break;
      case 'a':
        freq = 466;
        break;
      case 'B':
        freq = 494;
        break;
      case 'C':
        freq = 523;
        break;
      case 'c':
        freq = 554;
        break;
      case 'D':
        freq = 587;
        break;
      case 'd':
        freq = 624;
        break;
      case 'E':
        freq = 659;
        break;
      case 'F':
        freq = 749;
        break;
      case 'G':
        freq = 784;
        break;
      case 'g':
        freq = 831;
        break;
      case 'q':
        freq = 0;
        break;
    }
  }

  if(freq != 0) {
    SET_HIGH(myPORTB, 6);
    my_delay(freq);
    
    SET_LOW(myPORTB, 6);
    my_delay(freq);
  }
}
