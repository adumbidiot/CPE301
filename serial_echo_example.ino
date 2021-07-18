
unsigned char input[3] = {'A', 'B', 'C'}
// Serial Echo Example
void setup() 
{
  // setup the UART
  Serial.begin(9600);
}
void loop() 
{
 
  // if the UART received a character
  if(Serial.available())
  {
    // read in the character
    unsigned char in_char = Serial.read();
    for (int i = 0; i<3; i++){
      if in_char == input[i]{
        Serial.write(input[i])
        }
      }
    // write the character back to the Serial Port
   // Serial.write(in_char);
        
  }
}
