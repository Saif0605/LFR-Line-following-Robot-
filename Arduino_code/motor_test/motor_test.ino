// ================= MOTOR PINS =================
#define ENA 5
#define IN1 6
#define IN2 7

#define ENB 9
#define IN3 10
#define IN4 11

// ================= SPEED SETTINGS =================
int leftSpeed  = 148;   // Adjust if robot drifts
int rightSpeed = 150;   // Adjust if robot drifts

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// ================= MAIN LOOP =================
void loop() {

  // LEFT MOTOR FORWARD
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // RIGHT MOTOR FORWARD
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // SAME SPEED → STRAIGHT
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}
