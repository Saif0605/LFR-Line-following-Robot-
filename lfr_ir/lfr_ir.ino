// const int sensorPins[5] = {A5, A4, A3, A2, A1};

// void setup() {
//   Serial.begin(9600);
//   Serial.println("TCRT5000 RAW Sensor Values");
//   Serial.println("Format: A5  A4  A3  A2  A1");
// }

// void loop() {

//   for (int i = 0; i < 5; i++) {
//     int value = analogRead(sensorPins[i]);
//     Serial.print(value);
//     Serial.print("\t");   // tab spacing
//   }

//   Serial.println();
//   delay(200);
// }

#define NUM_SENSORS 5

int sensorPins[NUM_SENSORS] = {A5, A4, A3, A2, A1};
int sensorValues[NUM_SENSORS];
int sensorBinary[NUM_SENSORS];

int threshold = 400;   // adjust if needed

void setup() {
  Serial.begin(9600);
}

void loop() {

  // Read sensors
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorValues[i] = analogRead(sensorPins[i]);

    // Convert to 0/1
    if (sensorValues[i] < threshold) {
      sensorBinary[i] = 1;   // BLACK line
    } else {
      sensorBinary[i] = 0;   // WHITE surface
    }
  }

  // Print RAW values
  Serial.print("RAW: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }

  // Print BINARY values
  Serial.print(" | BIN: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensorBinary[i]);
    Serial.print(" ");
  }

  Serial.println();
  delay(100);
}
