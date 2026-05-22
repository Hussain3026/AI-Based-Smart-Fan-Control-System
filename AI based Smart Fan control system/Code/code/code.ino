#include <DHT.h>
#include <LiquidCrystal.h>

// ===== PIN DEFINITIONS =====
#define DHTPIN 2
#define DHTTYPE DHT11
#define FAN 9
#define BUZZER 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);
DHT dht(DHTPIN, DHTTYPE);

// ===== PID (TUNED) =====
float Kp = 6.0;
float Ki = 0.2;
float Kd = 1.5;

float prev_error = 0;
float integral = 0;

// ===== TARGET TEMP =====
float setTemp = 30.0;

// ===== ML MODEL (CALIBRATED) =====
float predictTempML(float temp){
  return (1.01 * temp) + 0.9;   // smoother prediction
}

float predictSpeedML(float temp){
  return (10.5 * temp) - 200;   // reduced aggressiveness
}

// ===== PID FUNCTION =====
float PID(float setpoint, float current){
  float error = current - setpoint;

  integral += error;
  integral = constrain(integral, -40, 40);   // anti-windup

  float derivative = error - prev_error;

  float output = (Kp * error) + (Ki * integral) + (Kd * derivative);

  prev_error = error;

  return output;
}

// ===== SMOOTHING =====
float smoothSpeed(float input){
  static float prev = 0;
  float output = (0.7 * prev) + (0.3 * input);
  prev = output;
  return output;
}

void setup(){
  pinMode(FAN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  dht.begin();

  lcd.begin(16,2);
  lcd.print("Optimized System");
  delay(2000);
  lcd.clear();
}

void loop(){

  float temp = dht.readTemperature();

  // ===== SENSOR FAULT =====
  if(isnan(temp)){
    lcd.clear();
    lcd.print("Sensor Error!");
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    return;
  } else {
    digitalWrite(BUZZER, LOW);
  }

  // ===== ML TEMP PREDICTION =====
  float futureTemp = predictTempML(temp);

  // ===== ML SPEED =====
  float ml_speed = predictSpeedML(futureTemp);

  // ===== PID OUTPUT =====
  float pid_speed = PID(setTemp, futureTemp);

  // ===== BALANCED COMBINATION =====
  float combined = (0.6 * ml_speed) + (0.4 * pid_speed);

  // ===== SMOOTHING =====
  float final_speed = smoothSpeed(combined);

  final_speed = constrain(final_speed, 0, 255);

  if(final_speed > 0 && final_speed < 70) final_speed = 70;

  analogWrite(FAN, (int)final_speed);

  // ===== FAN FAULT =====
  if(final_speed > 200 && temp > setTemp + 3){
    lcd.clear();
    lcd.print("Fan Fault!");
    digitalWrite(BUZZER, HIGH);
  }

  // ===== LCD DISPLAY =====
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print(" F:");
  lcd.print((int)final_speed);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(futureTemp);
  lcd.print("   ");

  // ===== SERIAL DEBUG =====
  Serial.print("Temp:");
  Serial.print(temp);
  Serial.print(" Future:");
  Serial.print(futureTemp);
  Serial.print(" ML:");
  Serial.print(ml_speed);
  Serial.print(" PID:");
  Serial.print(pid_speed);
  Serial.print(" Final:");
  Serial.println(final_speed);

  delay(1000);
}