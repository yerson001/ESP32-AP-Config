#include "ESP32-AP-Config.hpp"

ESP32APConfig::ESP32APConfig() : server(80) {}

ESP32APConfig::~ESP32APConfig() {
    preferences.end();
}

void ESP32APConfig::iniciar() {
    WiFi.softAP("ESP32_Config", "12345678");

    preferences.begin("wifi_config", false);
    cargarConfiguracion();

    server.on("/", [this]() { manejarPaginaConfiguracion(); });
    server.on("/guardar", [this]() { manejarGuardado(); });
    server.begin();
}

void ESP32APConfig::manejarCliente() {
    server.handleClient();
}

void ESP32APConfig::manejarPaginaConfiguracion() {
    String pagina = "<html><body><h2>Configuración WiFi</h2>";
    pagina += "<form action='/guardar' method='POST'>";
    pagina += "SSID: <input type='text' name='ssid'><br>";
    pagina += "Contraseña: <input type='password' name='password'><br>";
    pagina += "<input type='submit' value='Guardar'>";
    pagina += "</form></body></html>";

    server.send(200, "text/html", pagina);
}

void ESP32APConfig::manejarGuardado() {
    if (server.hasArg("ssid") && server.hasArg("password")) {
        String newSSID = server.arg("ssid");
        String newPassword = server.arg("password");

        guardarConfiguracion(newSSID.c_str(), newPassword.c_str());
        server.send(200, "text/html", "<h3>Guardado, reinicia el ESP32</h3>");
    }
}

void ESP32APConfig::guardarConfiguracion(const char* newSSID, const char* newPassword) {
    preferences.putString("ssid", newSSID);
    preferences.putString("password", newPassword);
}

void ESP32APConfig::cargarConfiguracion() {
    String savedSSID = preferences.getString("ssid", "");
    String savedPassword = preferences.getString("password", "");

    if (savedSSID.length() > 0) {
        strncpy(ssid, savedSSID.c_str(), sizeof(ssid));
        strncpy(password, savedPassword.c_str(), sizeof(password));
    }
}
