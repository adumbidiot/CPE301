/*
 * CPE 301 Lab 7
 * Nathaniel Daniel Fall 2020
 */
 
#define DECL_REG_U8(name, addr) volatile unsigned char* name = (volatile unsigned char*) addr;
#define DECL_REG_U16(name, addr) volatile unsigned int* name = (volatile unsigned int*) addr;

#define SET_OUTPUT(port, pin) *port |= (0x01 << pin);
#define SET_INPUT(port, pin) *port &= ~(0x01 << pin);

#define ENABLE_PULLUP(port, pin) *port |= (0x01 << pin);

#define SET_HIGH(port, pin) *port |= (0x01 << pin);
#define SET_LOW(port, pin) *port &= ~(0x01 << pin);

#define IS_HIGH(port, pin) ((*port & (0x01 << pin)) != 0)

DECL_REG_U8(myPORTB, 0x25);
DECL_REG_U8(myDDRB, 0x24);
DECL_REG_U8(myPINB, 0x23);

DECL_REG_U8(myPORTH, 0x102);
DECL_REG_U8(myDDRH, 0x101);
DECL_REG_U8(myPINH, 0x100);

DECL_REG_U8(EEPROM_ADDR_REG, 0x41);
DECL_REG_U8(EEPROM_DATA_REG, 0x40);
DECL_REG_U8(EEPROM_CNTRL_REG, 0x3F);

DECL_REG_U8(myTCCR1B, 0x81);
DECL_REG_U16(myTCNT1, 0x84);
DECL_REG_U8(myTIFR1, 0x36);

unsigned char chr_array[16] = {
  0b01111110,
  0b00001100,
  0b10110110,
  0b10011110,
  0b11001100,
  0b11011010,
  0b11111010,
  0b00001110,
  0b11111110,
  0b11011110,
  0b11101110,
  0b11111000,
  0b01110010,
  0b10111100,
  0b11110010,
  0b11100010
};

unsigned int DATA_ADDR = 0x00;

void eeprom_write(unsigned int address, unsigned char data_in)
{
  while(*EEPROM_CNTRL_REG & 0x02);
  *EEPROM_ADDR_REG = address;
  *EEPROM_DATA_REG = data_in;
  *EEPROM_CNTRL_REG |= 0x04;
  *EEPROM_CNTRL_REG &= ~(0x02);
  *EEPROM_CNTRL_REG |= 0x02;
}

unsigned char eeprom_read(unsigned int address)
{
  while(*EEPROM_CNTRL_REG & 0x02);
  *EEPROM_ADDR_REG = address;
  *EEPROM_CNTRL_REG |= 0x01;
  return *EEPROM_DATA_REG;
}

void display_num(unsigned char num){
  *myPORTB = chr_array[num];
}

void my_delay(unsigned int ticks, unsigned char prescalar)
{
  *myTCCR1B &= 0xF8;
  *myTCNT1 = (unsigned int) (65536 - ticks);
  *myTCCR1B |= prescalar;
  while((*myTIFR1 & 0x01)==0);
  *myTCCR1B &= 0xF8;       
  *myTIFR1 |= 0x01;
}

void setup() {
  SET_OUTPUT(myDDRB, 7);
  SET_OUTPUT(myDDRB, 6);
  SET_OUTPUT(myDDRB, 5);
  SET_OUTPUT(myDDRB, 4);
  SET_OUTPUT(myDDRB, 3);
  SET_OUTPUT(myDDRB, 2);
  SET_OUTPUT(myDDRB, 1);
  
  SET_INPUT(myDDRH, 6);
  ENABLE_PULLUP(myPORTH, 6);

  unsigned int saved = eeprom_read(DATA_ADDR);
  eeprom_write(DATA_ADDR, saved & 0x0F);
}

void loop() {
  unsigned int temp = eeprom_read(DATA_ADDR);
  display_num(temp);

  while(!IS_HIGH(myPINH, 6));
  
  bool should_exit = false;
  while(!should_exit){
    should_exit = true;
    
    if(IS_HIGH(myPINH, 6)) should_exit = false;
    my_delay(65535, 5);
    if(IS_HIGH(myPINH, 6)) should_exit = false;
  }
  
  temp = (temp + 1) % 0x10;
  eeprom_write(DATA_ADDR, temp);
}
