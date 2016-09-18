#define inputPin A0

const int timeInterval = 20;
const int repetition = 5;
const int bitsAmount = 7;
const int threshold = 200;
const int numberOfCharacters = 1;

void setup() {
  Serial.begin(9600);
 pinMode(inputPin, INPUT);
}

void readChar() {
  int numberOfBits = 0;
  int data[bitsAmount] = {0};
  
  //Serial.println("Waiting to read char");
  while(analogRead(A0)>threshold) {}
  delay(timeInterval);
  //Serial.println("Starting to read");
  
  for (int k=1; k<=bitsAmount; k++) {
    int sum = 0;
    for (int i=1; i<=repetition; i++) {
      //Serial.println(digitalRead(A0));
      sum += analogRead(A0)<threshold ? 1 : 0;
      delay(timeInterval/repetition);
    }
    int bitReceived = (sum<=(repetition/2)) ? 0 : 1;
    data[numberOfBits] = bitReceived;
    //Serial.println(bitReceived);
    numberOfBits++;
 }
 //printing bits received
 //Serial.print("Received: [");
 //for (int i=0; i<bitsAmount; i++) {
 //  Serial.print(data[i]);
 //  Serial.print(" ");
 //}
 //Serial.println("]");

 //converts to char
 int characterInt = 0;
 for (int i=0; i<bitsAmount; i++) {
    characterInt += data[i]*(1<<(bitsAmount-1-i));
  }
//Serial.print("character in binary: ");
 //Serial.println(characterInt);
char character = (char)characterInt;
//Serial.print("character received: ");
Serial.print(character);

delay(timeInterval);
}

void loop() {
 readChar();
}
