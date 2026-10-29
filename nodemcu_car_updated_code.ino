#define ENA   14
#define ENB   12
#define IN_1  15
#define IN_2  13
#define IN_3  2
#define IN_4  0

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;

int speedCar = 800;
int speed_Coeff = 3;

const char* ssid = "NodeMCU Car";

ESP8266WebServer server(80);

unsigned long lastCommandTime = 0;
const unsigned long commandTimeout = 1000;

bool motorsMoving = false;


// ---------------- SETUP ----------------

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  stopRobot();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();

  Serial.println();
  Serial.println("Robot Car Started");
  Serial.print("WiFi Name: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(myIP);

  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);

  server.begin();

  Serial.println("HTTP Server Started");
  Serial.println("Waiting for commands...");
}


// ---------------- MOVEMENT ----------------

void goAhead() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  motorsMoving = true;
  lastCommandTime = millis();
}


void goBack() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  motorsMoving = true;
  lastCommandTime = millis();
}


void goRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  motorsMoving = true;
  lastCommandTime = millis();
}


void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);

  motorsMoving = true;
  lastCommandTime = millis();
}


void goAheadRight() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar / speed_Coeff);
  analogWrite(ENB, speedCar);

  motorsMoving = true;
  lastCommandTime = millis();
}


void goAheadLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar / speed_Coeff);

  motorsMoving = true;
  lastCommandTime = millis();
}


void goBackRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar / speed_Coeff);
  analogWrite(ENB, speedCar);

  motorsMoving = true;
  lastCommandTime = millis();
}


void goBackLeft() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar / speed_Coeff);

  motorsMoving = true;
  lastCommandTime = millis();
}


// ---------------- STOP ----------------

void stopRobot() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  motorsMoving = false;
}


// ---------------- SPEED ----------------

void setSpeed(int newSpeed) {
  speedCar = newSpeed;

  if (motorsMoving) {
    analogWrite(ENA, speedCar);
    analogWrite(ENB, speedCar);
  }

  Serial.print("Speed: ");
  Serial.println(speedCar);
}


// ---------------- HTTP HANDLER ----------------

void HTTP_handleRoot() {
  Serial.println();
  Serial.println("HTTP Request Received");

  Serial.print("Request URI: ");
  Serial.println(server.uri());

  if (server.hasArg("State")) {
    command = server.arg("State");

    Serial.print("Received Command: ");
    Serial.println(command);

    if (command == "F") {
      goAhead();
    }
    else if (command == "B") {
      goBack();
    }
    else if (command == "L") {
      goLeft();
    }
    else if (command == "R") {
      goRight();
    }
    else if (command == "I") {
      goAheadRight();
    }
    else if (command == "G") {
      goAheadLeft();
    }
    else if (command == "J") {
      goBackRight();
    }
    else if (command == "H") {
      goBackLeft();
    }
    else if (command == "S") {
      stopRobot();
    }

    else if (command == "0") setSpeed(400);
    else if (command == "1") setSpeed(470);
    else if (command == "2") setSpeed(540);
    else if (command == "3") setSpeed(610);
    else if (command == "4") setSpeed(680);
    else if (command == "5") setSpeed(750);
    else if (command == "6") setSpeed(820);
    else if (command == "7") setSpeed(890);
    else if (command == "8") setSpeed(960);
    else if (command == "9") setSpeed(1023);

    else {
      Serial.println("Unknown Command");
      server.send(400, "text/plain", "Unknown Command");
      return;
    }

    server.send(
      200,
      "text/plain",
      "Command received: " + command
    );

  } else {
    Serial.println("State Parameter Missing");

    server.send(
      400,
      "text/plain",
      "Missing State parameter"
    );
  }
}


// ---------------- MAIN LOOP ----------------

void loop() {
  server.handleClient();

  if (motorsMoving &&
      millis() - lastCommandTime >= commandTimeout) {

    stopRobot();

    Serial.println("Safety Timeout: Motors Stopped");
  }
}
