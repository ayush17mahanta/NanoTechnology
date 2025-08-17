#include <WiFi.h> 
#include <HTTPClient.h> 
#include <OneWire.h> 
#include <DallasTemperature.h> 
// Wi-Fi credentials 
const char* ssid = "Your_SSID"; 
const char* password = "Your_PASSWORD"; 
// Cloud endpoint 
String serverName = "http://your-cloud-server/api/data"; 
// DS18B20 temperature sensor 
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 
int nanoSensorPin = 34;   // A0 equivalent on ESP32 
int pHSensorPin = 35;     // A1 equivalent 
int turbidityPin = 32;    // A2 equivalent 
void setup() { 
Serial.begin(115200); 
WiFi.begin(ssid, password); 
Serial.print("Connecting to WiFi"); 
while (WiFi.status() != WL_CONNECTED) { 
delay(500); 
Serial.print("."); 
} 
Serial.println("Connected!"); 
sensors.begin(); 
} 
void loop() { 
sensors.requestTemperatures(); 
float temperature = sensors.getTempCByIndex(0); 
int nanoValue = analogRead(nanoSensorPin); 
int pHValue = analogRead(pHSensorPin); 
int turbidityValue = analogRead(turbidityPin); 
Serial.printf("Nano: %d | pH: %d | Turbidity: %d | Temp: %.2f 
C\n", 
nanoValue, 
temperature); 
pHValue, 
if(WiFi.status() == WL_CONNECTED) { 
HTTPClient http; 
http.begin(serverName); 
turbidityValue, 
http.addHeader("Content-Type", "application/json"); 
String jsonData = "{\"nano\":" + String(nanoValue) + 
",\"pH\":" + String(pHValue) + 
",\"turbidity\":" 
String(turbidityValue) + 
+ 
",\"temperature\":" + String(temperature) 
+ "}"; 
int httpResponseCode = http.POST(jsonData); 
http.end(); 
} 
delay (5000); // Send data every 5 seconds 
}