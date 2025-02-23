#include <ESP32-AP-Config.hpp>

ESP32AP::Config apConfig;

void setup() {
    Serial.begin(115200);
    apConfig.iniciar();
}

void loop() {
    apConfig.manejarCliente();
}