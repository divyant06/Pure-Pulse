// --- BLYNK CREDENTIALS  ---
#define BLYNK_TEMPLATE_ID "TMPL3GNZF8XfN"
#define BLYNK_TEMPLATE_NAME "AQI Monito"
#define BLYNK_AUTH_TOKEN "zgoJ20jv12uJg3SVnIl-VHMdBV4USJBi"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Wokwi's simulated WiFi credentials
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// --- Pin Mapping ---
#define DHTPIN 15
#define DHTTYPE DHT22       
#define MQ135_PIN 34        
#define BUZZER_PIN 5
#define RED_PIN 4
#define GREEN_PIN 16
#define BLUE_PIN 17

// --- OLED Setup ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,20);
  display.println("Connecting to WiFi...");
  display.display();

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  display.clearDisplay();
  display.setCursor(0,20);
  display.println("System Ready!");
  display.display();
  delay(1000);

  // timer to send data every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void setLED(bool r, bool g, bool b) {
  digitalWrite(RED_PIN, r ? HIGH : LOW);
  digitalWrite(GREEN_PIN, g ? HIGH : LOW);
  digitalWrite(BLUE_PIN, b ? HIGH : LOW);
}

// Function to handle reading, alerts, and sending to cloud
void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int rawAQI = analogRead(MQ135_PIN); 
  int aqi = map(rawAQI, 0, 4095, 0, 500);

  // Send data to Blynk Virtual Pins
  Blynk.virtualWrite(V0, aqi);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);

  // Update OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("AQI: ");
  display.println(aqi);
  
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.print("Temp: "); display.print(temp); display.println(" C");
  display.setCursor(0, 40);
  display.print("Humidity: "); display.print(hum); display.println(" %");

  // Alert Logic
  display.setCursor(0, 55);
  if (aqi <= 50) {
    setLED(false, true, false); 
    noTone(BUZZER_PIN);
    display.print("Status: GOOD");
  } else if (aqi <= 150) {
    setLED(true, true, false);  
    noTone(BUZZER_PIN);
    display.print("Status: MODERATE");
  } else {
    setLED(true, false, false); 
    tone(BUZZER_PIN, 1000);     
    display.print("Status: HAZARDOUS!");
  }
  display.display();
}

void loop() {
  Blynk.run();
  timer.run();
}