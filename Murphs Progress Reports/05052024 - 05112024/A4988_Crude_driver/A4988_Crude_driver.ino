#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
    // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  Serial.begin(9600);
}

void loop() {
  set(39,4);
  set(58,4);
  set(52,1);
  set(50,1);
  set(44,1);
  set(77,4);
  set(58,4);
  set(52,1);
  set(50,1);
  set(44,1);
  set(77,4);
  set(58,4);
  set(52,1);
  set(50,1);
  set(52,1);
  set(44,4);
  delay(1000);
}

void set(int speed, int duration){
  // convert rpm to microseconds for on and off period of pulse
  int realSpeed = (int)floor((((60.0 / speed) * 1000000.0) / stepsPerRevolution) / 2.0);
  Serial.println(realSpeed);
    for (int i = 0; i < (speed * duration); i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(realSpeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(realSpeed);
  }
  delay(10);
}