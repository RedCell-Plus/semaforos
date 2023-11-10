#include <Servo.h>

// Definición de pines para los semáforos y zumbadores
#define redCar 13
#define yellowCar 12
#define greenCar 8
#define buzzer 3

#define redPed 7
#define greenPed 4
#define buzzerTraffic 5

// Inicialización del servo y tiempos
Servo myServo;
int carGreenTime = 3000;
int yellowTime = 1000;

void setup(){
  // Configura los pines como salidas o entradas
  pinMode(redCar, OUTPUT);
  pinMode(yellowCar, OUTPUT);
  pinMode(greenCar, OUTPUT);
  pinMode(redPed, OUTPUT);
  pinMode(greenPed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buzzerTraffic, OUTPUT);
  
  // Asocia el pin del servo
  myServo.attach(6);
  
  // Mueve el servo a la posición inicial
  myServo.write(0);
  
  // Inicia la comunicación serial
  Serial.begin(9600);
}

void loop(){
  // Comprueba si el semáforo de los autos está en rojo
  if (digitalRead(redCar) == LOW)
  {
    // Cambia los estados de los semáforos y activa señal auditiva
    digitalWrite(redCar, HIGH);
    digitalWrite(greenPed, HIGH);
    audibleSignal();
    digitalWrite(greenPed, LOW);
    digitalWrite(redPed, HIGH);
    digitalWrite(redCar, LOW);
    digitalWrite(greenCar, HIGH);
    myServo.write(90);
    audibleSignalTraffic();
  }
  
  // Espera durante el tiempo verde de los autos
  int time = 0;
  while (time < carGreenTime)
  {
    time = time + 1000;
    delay(1000);
  }
  
  // Cambia los semáforos para permitir el paso de peatones
  digitalWrite(greenCar, LOW);
  digitalWrite(yellowCar, HIGH);
  delay(yellowTime);  

  // Hace que el semáforo de los autos parpadee en amarillo
  for (int y = 0; y <= 2; y++)
  {
    digitalWrite(yellowCar, LOW);
    delay(300);
    digitalWrite(yellowCar, HIGH);
    delay(300);
  }
  
  // Apaga el semáforo de los autos y permite el paso de peatones
  digitalWrite(yellowCar, LOW);
  digitalWrite(redPed, LOW);
  myServo.write(0);
}

void audibleSignal()
{
  // Detiene el zumbador y genera una señal audible
  noTone(buzzer);
  for (int x = 1; x <= 3; x++) {
    tone(buzzer, 30);
    digitalWrite(greenPed, HIGH);
    delay(2000);
    digitalWrite(greenPed, LOW);
    noTone(buzzer);
    delay(1000);
  }
  for (int x = 0; x <= 3; x++) {
    tone(buzzer, 30);
    digitalWrite(greenPed, HIGH);
    delay(500);
    digitalWrite(greenPed, LOW);
    noTone(buzzer);
    delay(500);
  }
  // Genera más parpadeos con el zumbador
  for (int x = 0; x <= 3; x++) {
    tone(buzzer, 30);
    digitalWrite(greenPed, HIGH);
    delay(300);
    digitalWrite(greenPed, LOW);
    noTone(buzzer);
    delay(300);
  }
}

void audibleSignalTraffic()
{
  // Detiene el zumbador de tráfico y genera una señal audible
  noTone(buzzerTraffic);
  for (int x = 1; x <= 3; x++) {
    tone(buzzerTraffic, 1000);
    delay(1500);
    noTone(buzzerTraffic);
    delay(1000);
  }
  for (int x = 0; x <= 3; x++) {
    tone(buzzerTraffic, 1000);
    delay(1500);
    noTone(buzzerTraffic);
    delay(500);
  }
  // Genera más parpadeos con el zumbador de tráfico
  for (int x = 0; x <= 3; x++) {
    tone(buzzerTraffic, 1000);
    delay(500);
    noTone(buzzerTraffic);
    delay(500);
  }
}