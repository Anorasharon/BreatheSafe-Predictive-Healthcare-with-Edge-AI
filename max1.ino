#include <Wire.h>
#include "MAX30105.h"
#include "BluetoothSerial.h"
#include "model.h"  // Your SVM model from micromlgen

MAX30105 sensor;
BluetoothSerial SerialBT;
Eloquent::ML::Port::SVM classifier;

const int windowSize = 5;
long irBuffer[windowSize];
int sampleIndex = 0;
long lastBeatTime = 0;
float bpm = 0, spo2 = 0;
bool waitingForFinger = true;
bool readingSent = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-BPM");
  Serial.println("Bluetooth started. Pair with 'ESP32-BPM'");

  if (!sensor.begin()) {
    Serial.println("MAX30102 not found!");
    while (1);
  }

  sensor.setup(60, 4, 2, 100, 411, 4096);
  sensor.setPulseAmplitudeIR(0x3F);
  sensor.setPulseAmplitudeRed(0x3F);
}

bool isPeak(long c, long b, long a) {
  return b > a && b > c;
}

void loop() {
  long ir = sensor.getIR();
  long red = sensor.getRed();

  if (ir < 50000) {
    // Finger removed
    waitingForFinger = true;
    readingSent = false;
    Serial.println("👉 Place finger on sensor...");
    SerialBT.println("👉 Place finger on sensor...");
    delay(1000);
    return;
  }

  if (waitingForFinger) {
    Serial.println("🧠 Measuring...");
    SerialBT.println("🧠 Measuring...");
    waitingForFinger = false;
    sampleIndex = 0;
    bpm = 0;
    spo2 = 0;
    delay(1000);
  }

  float ratio = (float)red / ir;
  spo2 = constrain(110.0 - 25.0 * ratio, 70, 100);

  irBuffer[sampleIndex % windowSize] = ir;
  sampleIndex++;

  if (sampleIndex >= windowSize) {
    long a = irBuffer[(sampleIndex - 3) % windowSize];
    long b = irBuffer[(sampleIndex - 2) % windowSize];
    long c = irBuffer[(sampleIndex - 1) % windowSize];

    if (isPeak(c, b, a)) {
      long now = millis();
      long dt = now - lastBeatTime;
      lastBeatTime = now;

      if (dt > 300 && dt < 2000) {
        bpm = 60.0 / (dt / 1000.0);
      }
    }
  }

  if (!readingSent && bpm > 40) {
    // 🔍 ML Prediction
    float input[2] = { bpm, spo2 };
    int result = classifier.predict(input);

    Serial.print("📤 BPM: "); Serial.print(bpm, 1);
    Serial.print(" | SpO₂: "); Serial.print(spo2, 1);
    Serial.print(" | Risk: ");
    
    SerialBT.print("📤 BPM: "); SerialBT.print(bpm, 1);
    SerialBT.print(" | SpO₂: "); SerialBT.print(spo2, 1);
    SerialBT.print(" | Risk: ");

    switch (result) {
      case 0:
        Serial.println("⚠️ High Risk");
        SerialBT.println("⚠️ High Risk");
        break;
      case 1:
        Serial.println("⚠️ Low Risk");
        SerialBT.println("⚠️ Low Risk");
        break;
      case 2:
        Serial.println("✅ No Risk");
        SerialBT.println("✅ No Risk");
        break;
      default:
        Serial.println("❓ Unknown");
        SerialBT.println("❓ Unknown");
    }

    readingSent = true;
    Serial.println("👉 Remove finger to measure again...");
    SerialBT.println("👉 Remove finger to measure again...");
  }

  delay(100);  // ~10 Hz sampling
}
