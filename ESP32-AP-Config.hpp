#ifndef ESP32_AP_CONFIG_HPP
#define ESP32_AP_CONFIG_HPP

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

class ESP32APConfig {  // Renombrado para coincidir con el proyecto
public:
    ESP32APConfig();
    ~ESP32APConfig();

    void iniciar();
    void manejarCliente();
    void guardarConfiguracion(const char* ssid, const char* password);

private:
    WebServer server;
    Preferences preferences;

    void manejarPaginaConfiguracion();
    void manejarGuardado();
    void cargarConfiguracion();

    char ssid[32];
    char password[32];
};

#endif // ESP32_AP_CONFIG_HPP
