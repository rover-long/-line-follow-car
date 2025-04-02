#define leftsensor A0
#define rightsensor A1
#define IN1 13
#define IN2 10
#define IN3 9
#define IN4 12

// PID 参数
float Kp = 20.0;  // 比例增益
float Ki = 0.1;   // 积分增益
float Kd = 5.0;   // 微分增益

// PID 变量
float error = 0;
float previousError = 0;
float integral = 0;
float derivative = 0;

// 基础速度
int baseSpeed = 70;
int maxSpeed = 150;

void setup() {
  pinMode(leftsensor, INPUT);
  pinMode(rightsensor, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  // 读取传感器模拟值
  int leftValue = analogRead(leftsensor);
  int rightValue = analogRead(rightsensor);

  // 计算误差（目标是保持在黑线上，误差基于传感器差值）
  error = leftValue - rightValue; // 左高右低则error为正，需右转

  // 计算PID各部分
  integral += error;            // 积分项
  derivative = error - previousError; // 微分项
  float correction = Kp * error + Ki * integral + Kd * derivative;

  // 计算左右电机速度
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // 限制速度范围
  leftSpeed = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  
  if (leftValue > 750 && rightValue > 750) { 
    back();
    delay(50);
  } else {
    moveMotors(leftSpeed, rightSpeed); 
  }

  // 更新上一次误差
  previousError = error;


  Serial.print("Left: "); Serial.print(leftValue);
  Serial.print(" Right: "); Serial.print(rightValue);
  Serial.print(" Error: "); Serial.print(error);
  Serial.print(" LeftSpeed: "); Serial.print(leftSpeed);
  Serial.print(" RightSpeed: "); Serial.println(rightSpeed);

  delay(50); 
}

void moveMotors(int leftSpeed, int rightSpeed) {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, leftSpeed);
  analogWrite(IN3, rightSpeed);
  digitalWrite(IN4, LOW);
}

void back() {
  digitalWrite(IN1, HIGH);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  digitalWrite(IN4, HIGH);
}

void stopnow() {
  digitalWrite(IN1, LOW);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  digitalWrite(IN4, LOW);
}
