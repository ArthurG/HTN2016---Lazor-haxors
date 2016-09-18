const int ledPin = 3;
const int data_size = 7;
const int wait_between_signal = 20;
const int repeat = 1;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  char msg[] = "Hello World! The Quick Brown Fox jumped over the Lazy Dog!!!!!!!1";
  for (int i=0; i<sizeof(msg)/sizeof(char); i++)
    sendChar(msg[i]);
}

void sendChar(char c) {
  digitalWrite(ledPin, LOW);
  delay(wait_between_signal*2);
  digitalWrite(ledPin, HIGH);
  delay(wait_between_signal);

  int data[7] = {0,0,0,0,0,0,0};
  int r = min((int) c, 127);
  int d = 6;
  while (r > 0) {
    data[d] = r%2;
    r/=2;
    d--;
  }

  Serial.print("Sending char ");
  Serial.print(c);
  Serial.print(": [");
  
  //data
  for (int i=0; i<7; i++) {
      Serial.print(data[i]);
      Serial.print(" ");
      digitalWrite(ledPin, data[i]);
      delay(wait_between_signal);
  }
  Serial.println("]");

  digitalWrite(ledPin, LOW);
}

void loop() {}

