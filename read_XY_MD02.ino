#define RXD2 26
#define TXD2 27

byte ByteArray[250];
int ByteData[20];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);

  byte msg[] = {0x01,0x03,0x00,0x00,0x00,0x0A,0xC5,0xCD};

  int i;
  int len=8;

  Serial.println("Sending Data...");
  for(i=0 ; i < len ; i++){
    Serial2.write(msg[i]);
    Serial.print("[");
    Serial.print(i);
    Serial.print("]");
    Serial.print("=");
    Serial.print(String(msg[i],HEX));
  }

  len = 0;
  Serial.println();
  Serial.println();

  int a = 0;

  while(Serial2.available()){
    ByteArray[a] = Serial2.read();
    a++;
  }

  int b = 0;
  String Register;
  Serial.println("Receiving Data...");
  for(b=0;b<a;b++){
    Serial.print("[");
    Serial.print(b);
    Serial.print("]");
    Serial.print("=");

    Register = String(ByteArray[b],HEX);
    Serial.print(Register);
    Serial.print(" ");
  }

  Serial.println();
  Serial.println();
}