#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h> 

// --- Configuration Wi-Fi et Telegram ---
const char* ssid = "SSID";
const char* password = "PASSWORD";
#define BOTtoken "BOT TOKEN*"
#define CHAT_ID "ID*"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// --- Définition des Broches ---
#define trigPin 5
#define echoPin 18
#define ENA 25
#define ENB 13
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12
#define servoPin 4 

Servo myServo;
bool modeAutomatique = false;
unsigned long lastTimeBotRan;

// --- Fonctions de Pilotage (LOGIQUE INVERSÉE) ---

void moveForward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, 200);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, 200);
}

void moveBackward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 200);
}

void turnRight() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, 200);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 200);
}

void turnLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 200);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); analogWrite(ENB, 200);
}

void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

// --- Mesure de Distance ---
int getDistance() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); 
  int dist = duration * 0.034 / 2;
  return (dist <= 0) ? 400 : dist;
}

// --- Algorithme d'Évitement ---
void scannerEtEviter() {
  stopCar();
  delay(200);
  moveBackward(); 
  delay(500);
  stopCar();

  myServo.write(0); // Regarder à droite
  delay(700); 
  int distD = getDistance();

  myServo.write(180); // Regarder à gauche
  delay(700); 
  int distG = getDistance();

  myServo.write(90); // Revenir au centre
  delay(400);

  if (distD > distG) {
    turnRight();
  } else {
    turnLeft();
  }
  delay(700); 
  stopCar();
}

// --- Gestion des Messages Telegram ---
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String text = bot.messages[i].text;
    
    if (text == "/avancer") { modeAutomatique = false; moveForward(); }
    else if (text == "/reculer") { modeAutomatique = false; moveBackward(); }
    else if (text == "/droite") { modeAutomatique = false; turnRight(); }
    else if (text == "/gauche") { modeAutomatique = false; turnLeft(); }
    else if (text == "/stop") { modeAutomatique = false; stopCar(); }
    else if (text == "/auto") { 
      modeAutomatique = true; 
      bot.sendMessage(CHAT_ID, "Mode Automatique Activé 🤖", ""); 
    }
    else if (text == "/start") {
      bot.sendMessage(CHAT_ID, "Commandes : /avancer, /reculer, /droite, /gauche, /stop, /auto", "");
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  // Configuration Servo
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);
  myServo.attach(servoPin, 500, 2400); 
  myServo.write(90);

  // Configuration Pins
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);

  // Connexion Wi-Fi
  WiFi.begin(ssid, password);
  client.setInsecure();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  bot.sendMessage(CHAT_ID, "Robot prêt et connecté !", "");
}

void loop() {
  // Vérification Telegram toutes les 1 seconde
  if (millis() > lastTimeBotRan + 1000) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    handleNewMessages(numNewMessages);
    lastTimeBotRan = millis();
  }

  // Lecture constante de la distance
  int distance = getDistance();

  if (modeAutomatique) {
    if (distance < 25) {
      scannerEtEviter();
    } else {
      moveForward();
    }
  } 
  else {
    // Sécurité manuelle : si un obstacle est trop proche (< 15cm), on stoppe
    if (distance < 15) {
      stopCar();
    }
  }
}