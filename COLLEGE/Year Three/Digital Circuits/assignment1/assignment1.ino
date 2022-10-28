int a1 = 21; // D
int a0 = 20; // X
int b1 = 19;
int b0 = 18;

int c0 = 4;
int s1 = 3;
int s0 = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(a1, OUTPUT);
  pinMode(a0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b0, OUTPUT);
  pinMode(c0, INPUT);
  pinMode(s1, INPUT);
  pinMode(s0, INPUT);
}

void loop() {
  
  digitalWrite(b0, HIGH);
  digitalWrite(b1, HIGH); // B = 3
  digitalWrite(a0, LOW);
  digitalWrite(a1, HIGH); // A = 2

  delay(2000);
  
  int c0_out = 0;
  int s1_out = 0;
  int s0_out = 0;
  c0_out = digitalRead(c0);
  s1_out = digitalRead(s1);
  s0_out = digitalRead(s0);


  Serial.print("B = ");
  Serial.print(b1);
  Serial.println(b0);
  Serial.print("A = ");
  Serial.print(a1);
  Serial.println(a0);
  Serial.print("S(A, B) = ");
  Serial.print(s1_out);
  Serial.println(s0_out);
  Serial.print("C(A, B) = ");
  Serial.println(c0_out);
  Serial.println("----------------------");
}
