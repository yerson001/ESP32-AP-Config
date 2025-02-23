#ifndef ESP32_AP_CONFIG_HPP
#define ESP32_AP_CONFIG_HPP

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

namespace ESP32AP {

    class Config {
    public:
        Config();
        ~Config();

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

} // namespace ESP32AP

#endif // ESP32_AP_CONFIG_HPP
