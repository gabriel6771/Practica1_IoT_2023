#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "********";
const char* password = "*******";

// WebServer Instantiation
ESP8266WebServer server(80);

void handleRoot() {
  // Muestra una página HTML básica con dos botónes para encender y apagar dos LED
  String html = "<html><body>";
  html += "<center>";
  html += "<h1>Practica 1 IoT</h1><h2>Gabriel Cano</h2>";
  html += "<h2>Led1</h2>";
  html += "<p><a href=\"/led1/on\"><button>Encender</button></a></p>";
  html += "<p><a href=\"/led1/off\"><button>Apagar</button></a></p>";
  html += "<h2>Led2</h2>";
  html += "<p><a href=\"/led2/on\"><button>Encender</button></a></p>";
  html += "<p><a href=\"/led2/off\"><button>Apagar</button></a></p>";
  html += "</center>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLed1On() {
  // Enciende el LED1
  digitalWrite(D1, HIGH);
  server.send(200, "text/plain", "LED encendido");
}

void handleLed1Off() {
  // Apaga el LED1
  digitalWrite(D1, LOW);
  server.send(200, "text/plain", "LED apagado");
}

void handleLed2On() {
  // Enciende el LED2
  digitalWrite(D2, HIGH);
  server.send(200, "text/plain", "LED 2 encendido");
}

void handledLed2Off() {
  // Apaga el LED2
  digitalWrite(D2, LOW);
  server.send(200, "text/plain", "LED 2 apagado");
}

void setup() {
  // configura los puertos como salidas
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  // Configura las rutas del servidor web
  server.on("/", handleRoot);
  server.on("/led1/on", handleLed1On);
  server.on("/led1/off", handleLed1Off);
  server.on("/led2/on", handleLed2On);
  server.on("/led2/off", handledLed2Off);

  // Inicia el servidor
  server.begin();
  Serial.println("Servidor iniciado");

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println(""); 

  // Inicializa la conexión WiFi
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
   //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
}

