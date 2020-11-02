/*
 * CPE 301 Lab 7 Sample code
 * Debouncing, 7-Segments, EEPROM
 * Written By Syed Zawad, Fall 2020
 * This program counts the presses of a button and displays the counts on
 * a 7-segment display (displays 0 thru F). The counter variable is also stored and read back from
 * EEPROM memory at boot time. 
 */

// this is the character array, mapped such that the first element displays a '0' on the 7-segment
unsigned char chr_array[16] = {??, ??, ......};

// make some pointers to a port you want for the 7 segment register

// make some pointers to a different port for the button

// make some pointers to the EEPROM registers
// Look at the EEPROM DEMO CODE

void setup() 
{
  // Set up the ddr, port registers for input and output ports

  // Read counter from EEPROM
  
  // initialize display to whatever we read...
  display_num(counter);
}

void loop() 
{
  // Debouncing input code here
  // Increment counter
  // Light up 7-Seg display
  // Save counter to EEPROM
}

void display_num(unsigned char num)
{
  // Set the PORT values to 1's and 0's sets them to highs/lows, and so lights up the appropriate
  // LEDs in the 7-seg display
  *port_WHATEVER_YOU_ARE_USING = chr_array[num];
}
