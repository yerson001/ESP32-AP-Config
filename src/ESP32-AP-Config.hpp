#ifndef ESP32_AP_CONFIG_HPP
#define ESP32_AP_CONFIG_HPP

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <map>

namespace ESP32AP {

    class Config {
    public:
        Config();
        ~Config();

        void setupAccesPoint();
        void handleClient();

        void addVariable(const String& key,const String& defaultValue);
        String getVariable(const String& key);
        int getVariableInt(const String& key);
        double getVariableDouble(const String& key);
        void setVariable(const String& key, const String& value);
       

    private:
        WebServer server;
        Preferences preferences;
        std::map<String, String> variables;

        void handleRoot();
        void handleSave();
        void handleCancel();
    };

} // namespace ESP32AP

#endif // ESP32_AP_CONFIG_HPP
