
#define BLYNK_TEMPLATE_NAME "YOUR BLYNK TEMPLATE NAME"
#define BLYNK_AUTH_TOKEN "YOUR TOKEN"
#define BLYNK_TEMPLATE_ID "YOUR BLYNK TEMPLATE ID"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define ADXL345_ADDR 0x53
#define BUZZER_PIN 14
#define ADXL_INT_PIN 2

char ssid[] = "YOUR WIFI NAME";
char pass[] = "YOUR WIFI PASSWORD";

BlynkTimer timer;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
bool isActive = false;

void IRAM_ATTR wakeUp() {
    isActive = true;
}

float gettiltAngle(float ax, float ay, float az) {
    float magnitude = sqrt(ax * ax + ay * ay + az * az);
    return (magnitude == 0) ? 0 : acos(az / magnitude) * 180.0 / PI;
}

void setupActivityInactivity() {
    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x28); Wire.write(5); // Free Fall Threshold
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x29); Wire.write(10); // Free Fall Time
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x24); Wire.write(10); // Activity threshold
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x25); Wire.write(5); // Inactivity threshold
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x26); Wire.write(5); // Inactivity time
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x27); Wire.write(0xFF); // Enable all axes
    Wire.endTransmission();

    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x2E); Wire.write(0x1C); // Enable interrupts
    Wire.endTransmission();
}

void sendToBlynk() {
    sensors_event_t event;
    accel.getEvent(&event);
    Serial.print("Sending to Blynk - X: "); Serial.print(event.acceleration.x);
    Serial.print(" | Y: "); Serial.print(event.acceleration.y);
    Serial.print(" | Z: "); Serial.println(event.acceleration.z);
    Blynk.virtualWrite(V0, event.acceleration.x);
    Blynk.virtualWrite(V1, event.acceleration.y);
    Blynk.virtualWrite(V2, event.acceleration.z);
    Blynk.virtualWrite(V3,int(isActive));
}

void setup() {
    Serial.begin(9600);
    Wire.begin(4, 5);
    WiFi.begin(ssid, pass);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, HIGH);

    pinMode(ADXL_INT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ADXL_INT_PIN), wakeUp, RISING);
    
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    Serial.println("Connected to Blynk");
    if (!accel.begin()) {
        Serial.println("No ADXL345 detected!");
        while (1);
    }
    Serial.println("ADXL345 initialized.");
    setupActivityInactivity();
   if(isActive){
    timer.setInterval(1000L, sendToBlynk); // Send data every second
   }
}

void loop() {
    sensors_event_t event;
    accel.getEvent(&event);

    float ax = event.acceleration.x;
    float ay = event.acceleration.y;
    float az = event.acceleration.z;
    float tiltAngle = gettiltAngle(ax, ay, az);

    Wire.beginTransmission(ADXL345_ADDR);
    Wire.write(0x30);
    Wire.endTransmission();
    Wire.requestFrom(ADXL345_ADDR, 1);
    uint8_t intSource = Wire.read();

    if ((intSource & 0x04) == 0x04) {
        Serial.println("🚀 Free Fall Detected!");
        Blynk.logEvent("free_fall_detected", "🚀 Free Fall Detected!");
    }

    if ((intSource & 0x10) == 0x10) {
        Serial.println("📌 Activity Detected! Waking up...");
        isActive = true;
    }

    if (tiltAngle > 45.0) {
        Serial.println("⚠️ WARNING: Loss of balance detected! Alerting user...");
        digitalWrite(BUZZER_PIN, LOW);
        delay(2000);
        digitalWrite(BUZZER_PIN, HIGH);
        Blynk.logEvent("unstable_posture", "⚠️ Loss of balance detected!");
    }

    if ((intSource & 0x08) == 0x08) {
        Serial.println("💤 Inactivity Detected! Entering Deep Sleep...");
        isActive = false;
        // ESP.deepSleep(0);
    }
  if (isActive){
    Blynk.run();
    
    timer.run();
  }
    delay(500);
}
