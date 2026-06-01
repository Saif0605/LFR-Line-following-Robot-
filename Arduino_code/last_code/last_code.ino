// ================= MOTOR PINS =================
#define ENA 5
#define IN1 6
#define IN2 7

#define ENB 9
#define IN3 10
#define IN4 11

// ================= SPEED =================
int baseLeft  = 255;   // FULL SPEED
int baseRight = 255;   // FULL SPEED
int turnSpeed = 220;   // Slightly less for control

// ================= SENSOR PINS =================
int sensors[5] = {A5, A4, A3, A2, A1};

// ================= BLACK THRESHOLD =================
int BLACK = 200;

// ================= LAST TURN MEMORY =================
enum LastTurn {NONE, LEFT, RIGHT};
LastTurn lastTurn = NONE;

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
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  analogWrite(ENA, baseLeft);
  analogWrite(ENB, baseRight);
}

void turnLeft() {
  analogWrite(ENA, 0);             // Left motor stop
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);           // Right motor forward
  analogWrite(ENB, turnSpeed);
  lastTurn = LEFT;
}

void turnRight() {
  analogWrite(ENB, 0);             // Right motor stop
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);           // Left motor forward
  analogWrite(ENA, turnSpeed);
  lastTurn = RIGHT;
}

// ================= MAIN LOOP =================
void loop() {

  int s5 = analogRead(A5);  // Far Left
  int s4 = analogRead(A4);  // Left
  int s3 = analogRead(A3);  // Center
  int s2 = analogRead(A2);  // Right
  int s1 = analogRead(A1);  // Far Right

  // ===== DEBUG =====
  Serial.print(s5); Serial.print("\t");
  Serial.print(s4); Serial.print("\t");
  Serial.print(s3); Serial.print("\t");
  Serial.print(s2); Serial.print("\t");
  Serial.println(s1);

  // ===== LOGIC =====

  // VERY HARD LEFT (90° TURN)
  if (s5 < BLACK && s4 < BLACK) {
    analogWrite(ENA, 0);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 255);
    lastTurn = LEFT;
  }

  // VERY HARD RIGHT (90° TURN)
  else if (s1 < BLACK && s2 < BLACK) {
    analogWrite(ENB, 0);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);
    lastTurn = RIGHT;
  }

  // HARD LEFT
  else if (s5 < BLACK) {
    turnLeft();
  }

  // NORMAL LEFT
  else if (s4 < BLACK) {
    turnLeft();
  }

  // HARD RIGHT
  else if (s1 < BLACK) {
    turnRight();
  }

  // NORMAL RIGHT
  else if (s2 < BLACK) {
    turnRight();
  }

  // STRAIGHT
  else if (s3 < BLACK) {
    goStraight();
    lastTurn = NONE;
  }

  // ALL WHITE → SEARCH LAST DIRECTION
  else {
    if (lastTurn == LEFT) {
      turnLeft();
    } 
    else if (lastTurn == RIGHT) {
      turnRight();
    } 
    else {
      goStraight();
    }
  }

  delay(1);  // Faster response
}
