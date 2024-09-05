#define MAX485_DE_RE 32

// half second wait for a reply
const uint32_t TIMEOUT = 200UL;

// canned message to your RS485 device
uint8_t msg[] = {0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 26, 27);
  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);
  delay(1000);
}

void loop() {
  uint32_t startTime = 0;

  Serial.print("TX: ");
  printHexMessage( msg, sizeof(msg) );

  // send the command
  digitalWrite(MAX485_DE_RE, HIGH);
  delay( 10 );
  Serial1.write( msg, sizeof(msg) );
  Serial1.flush();
  digitalWrite(MAX485_DE_RE, LOW);

  Serial.print("RX: ");
  
  // read any data received and print it out
  startTime = millis();
  while ( millis() - startTime <= TIMEOUT ) {
    if (Serial1.available()) {
      printHexByte(Serial1.read());
    }
  }
  Serial.println();
  delay(2000);
}

void printHexMessage( uint8_t values[], uint8_t sz ) {
  for (uint8_t i = 0; i < sz; i++) {
    printHexByte( values[i] );
  }
  Serial.println();
}

void printHexByte(byte b)
{
  Serial.print((b >> 4) & 0xF, HEX);
  Serial.print(b & 0xF, HEX);
  Serial.print(' ');
}
