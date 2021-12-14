/*
 * Lisa Monpierre
 * EFRITS SAS
 * 
 * MAX7219 Library
 * Dec. 2021
 */

byte ClockPin      = 13;
byte DataInPin     = 11;
byte ChipSelectPin = 10;

byte noOpRegister        = 0x00;
byte digit0Register      = 0x01;
byte digit1Register      = 0x02;
byte digit2Register      = 0x03;
byte digit3Register      = 0x04;
byte digit4Register      = 0x05;
byte digit5Register      = 0x06;
byte digit6Register      = 0x07;
byte digit7Register      = 0x08;
byte decodeModeRegister  = 0x09;
byte intensityRegister   = 0x0A;
byte scanLimitRegister   = 0x0B;
byte shutdownRegister    = 0x0C;
byte displayTestRegister = 0x0F; 

byte usingLedMatrix        = 0x00; // Not digits model
byte intensityOfBrightness = 0x01; // Range 0x00 - 0x01
byte scan8LEDs             = 0x07;
byte normalMode            = 0x01; // For shutdown/power-down mode set 0
byte displayMode           = 0x00; // For test display mode set 1

byte maxDigit = 8;
byte maxSegment = 4;

byte digits[] = {digit0Register, digit1Register, digit2Register, digit3Register, digit4Register, digit5Register, digit6Register, digit7Register};

byte matrix[8][4] =
{
  {0X00, 0X00, 0X00, 0X00 },
  {0X00, 0X00, 0X00, 0X00 },
  {0X00, 0X00, 0X00, 0X00 },
  {0X00, 0X00, 0X00, 0X00 },
  {0X00, 0X00, 0X00, 0X00 },
  {0X00, 0X00, 0X00, 0X00 },
  {0X00, 0X00, 0X00, 0X00 },
  {0X00, 0X00, 0X00, 0X00 }
};

void initPins()
{
  pinMode(ClockPin, OUTPUT);
  pinMode(ChipSelectPin,  OUTPUT);
  pinMode(DataInPin, OUTPUT);
}

void sendBytesToMax7219(byte data) 
{
  for (byte i = 0; i < 8; ++i)
  {
    digitalWrite(ClockPin, LOW);
    digitalWrite(DataInPin, data & 0x80);
    data = data << 1;
    digitalWrite(ClockPin, HIGH);
   }
}

void writeToRegister(byte registerNumber, byte data)
{
  digitalWrite(ChipSelectPin, LOW);
  sendBytesToMax7219(registerNumber);
  sendBytesToMax7219(data);
  digitalWrite(ChipSelectPin, HIGH);
}

void initMax7219Component()
{
  writeToRegister(decodeModeRegister,  usingLedMatrix);
  writeToRegister(intensityRegister,   intensityOfBrightness);
  writeToRegister(scanLimitRegister,   scan8LEDs);
  writeToRegister(shutdownRegister,    normalMode);
  writeToRegister(displayTestRegister, displayMode);
}

void setup() 
{
  Serial.begin(9600); 
  
  initPins();
  delay(50);
  
  initMax7219Component();
  delay(50);
  
  displayScreen();
}

void writeToNextSegment(byte digitRegister, byte data)
{
  sendBytesToMax7219(digitRegister);
  sendBytesToMax7219(data);
}

void beginWriteLine()
{
  digitalWrite(ChipSelectPin, LOW);
}

void endWriteLine()
{
  digitalWrite(ChipSelectPin, HIGH);
}

void displayScreen()
{
  for (byte indexDigit = 0; indexDigit < maxDigit; ++indexDigit)
  {
    beginWriteLine();
    for (byte indexSegment = 0; indexSegment < maxSegment; ++indexSegment)
    {
      writeToNextSegment(digits[indexDigit], matrix[indexDigit][indexSegment]);
    }
    endWriteLine();
  }
}

void blankSegment(byte indexSegment)
{
  for (byte indexDigit = 0; indexDigit < maxDigit; ++indexDigit)
  {
    putPixel(indexDigit, indexSegment, 0x00);
  }
}

void putPixel(byte indexDigit , byte indexSegment, byte pixel)
{
  matrix[indexDigit][indexSegment] = pixel;
}

void loop() 
{
  putPixel(1, 1, B11111111);
}
