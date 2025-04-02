#define leftsensor A0
#define rightsensor A1
#define IN1 13
#define IN2 10
#define IN3 9
#define IN4 12

int threshold = 750;

void setup() {
  pinMode(leftsensor, INPUT);
  pinMode(rightsensor, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);  
}

void loop() {
  int leftvalue = analogRead(leftsensor);
  int rightvalue = analogRead(rightsensor);
  bool left = leftvalue > threshold;
  bool right = rightvalue > threshold;
  
  if (!left && !right) {
    forward();
  }
  else if (left && !right) {
    stopnow();    // 先停止
    delay(50);    // 短暂停止50毫秒
    turnleft();   // 然后左转
    delay(10);
  }
  else if (!left && right) {
    stopnow();    // 先停止
    delay(50);    // 短暂停止50毫秒
    turnright();  // 然后右转
    delay(10);
  }
  else {
    back(); 
  }
  delay(50);
}

void forward() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 70);
  analogWrite(IN3, 70);
  digitalWrite(IN4, LOW);  
}

void turnleft() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 150);  // 转弯速度从 250 降低到 150
  analogWrite(IN3, 0);
  digitalWrite(IN4, LOW); 
}

void turnright() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 0);
  analogWrite(IN3, 150);  // 转弯速度从 250 降低到 150
  digitalWrite(IN4, LOW);  
}

void stopnow() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  digitalWrite(IN4, LOW);
}
void back(){
  digitalWrite(IN1, HIGH);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  digitalWrite(IN4, HIGH); 
}
