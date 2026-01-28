// ================= MOTOR PINS =================
#define ENA 5
#define IN1 6
#define IN2 7

#define ENB 9
#define IN3 10
#define IN4 11

// ================= SPEED =================
int baseLeft  = 98;
int baseRight = 100;
int turnSpeed = 105;

// ================= SENSOR PINS =================
int sensors[5] = {A5, A4, A3, A2, A1};

// ================= BLACK THRESHOLD =================
int BLACK = 200;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

// ================= MOTOR FUNCTIONS =================
void goStraight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, baseLeft);
  analogWrite(ENB, baseRight);
}

void turnLeft() {
  // LEFT motor STOP
  analogWrite(ENA, 0);
  // RIGHT motor FORWARD
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENB, turnSpeed);
}

void turnRight() {
  // RIGHT motor STOP
  analogWrite(ENB, 0);
  // LEFT motor FORWARD
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  analogWrite(ENA, turnSpeed);
}

// ================= MAIN LOOP =================
void loop() {
  int s5 = analogRead(A5);
  int s4 = analogRead(A4);
  int s3 = analogRead(A3);
  int s2 = analogRead(A2);
  int s1 = analogRead(A1);

  // Debug
  Serial.print(s5); Serial.print("\t");
  Serial.print(s4); Serial.print("\t");
  Serial.print(s3); Serial.print("\t");
  Serial.print(s2); Serial.print("\t");
  Serial.println(s1);

  // ===== LOGIC =====
  if (s5 < BLACK || s4 < BLACK) {
    turnLeft();
  }
  else if (s2 < BLACK || s1 < BLACK) {
    turnRight();
  }
  else if (s3 < BLACK) {
    goStraight();
  }
  else {
    goStraight();
  }

  delay(5);
}
