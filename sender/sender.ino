#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "LAZERS";
const char* password = "12345678";
const int input_pin = 2;
const int output_pin = 0;

const int ledPin = 2;
const int data_size = 7;
const int wait_between_signal = 20;
const int repeat = 1;

IPAddress apIP(192, 168, 1, 1);
ESP8266WebServer server(80);

void handleRoot() {
  Serial.println("Handling root");
  String message = "LAZERS!!!!1<br />";
  message += "<form method='post' action='/msg' >";
  message += "    <textarea name=msg></textarea>";
  message += "    <input type=submit value='Submit' />";
  message += "</form>";
  server.send(200, "text/html", message);
}

void handleMsg() {
  String msg = server.arg("msg");

  for (int i=0; i<msg.length(); i++)
    sendChar(msg.charAt(i));
  
  server.send(200, "text/plain", "Message Sent!");
}

void handleNotFound(){
  Serial.println("Handling 404");
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/html", message);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  Serial.println("Started wifi.");

  server.on("/", handleRoot);
  server.on("/msg", handleMsg);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void sendChar(char c) {
  digitalWrite(ledPin, LOW);
  delay(wait_between_signal*2);
  digitalWrite(ledPin, HIGH);
  delay(wait_between_signal);

  int data[7] = {0,0,0,0,0,0,0};
  int r = c;
  if (r < 0) r = 0;
  if (r > 127) r = 127;
  
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

void loop() {
  server.handleClient();
}

