#include "ESP32-AP-Config.hpp"

namespace ESP32AP
{

    Config::Config() : server(80) {}

    Config::~Config()
    {
        preferences.end();
        variables.clear();
    }

    void Config::setupAccesPoint()
    {
        preferences.begin("config", false);

        String storedSSID = preferences.getString("ssid", "ESP_AP_CONFIG");
        String storedPassword = preferences.getString("password", "12345678");

        if (storedPassword.length() < 8) {
            storedPassword = "12345678"; 
        }

        bool apStarted = WiFi.softAP(storedSSID.c_str(), storedPassword.c_str());

        if (apStarted)
        {
            Serial.println("[ +++++++++++++++++++++++++++++++ ]");
            Serial.println("| ACCESPOINT STARTED SUCCESSFULLY |");
            Serial.print("| ACCESPOINT IP ADDRESS:");
            Serial.println(WiFi.softAPIP());
            Serial.println("[ +++++++++++++++++++++++++++++++ ]");
        }
        else
        {
            Serial.println("[ ACCESSPOINT FAILED TO START ]");
        }
        server.on("/", std::bind(&Config::handleRoot, this));
        server.on("/save", HTTP_POST, std::bind(&Config::handleSave, this));
        server.on("/cancel", std::bind(&Config::handleCancel, this));

        server.begin();
    }

    void Config::handleRoot()
    {
        String storedSSID = preferences.getString("ssid", "ESP_AP_CONFIG");
        String storedPassword = preferences.getString("password", "12345678");
        String storedwifiSSID = preferences.getString("wifissid", "admin");
        String storedwifiPassword = preferences.getString("wifipassword", "12345678");

        String html = R"rawliteral(
            <!DOCTYPE html>
            <html lang="es">

            <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Configuración WiFi</title>
            <style>
                body {
                font-family: Arial, sans-serif;
                text-align: center;
                background: #121212;
                color: #ddd;
                margin: 0;
                padding: 0;
                }

                .container {
                max-width: 400px;
                margin: 20px auto;
                padding: 20px;
                }

                .section {
                margin-bottom: 15px;
                border-radius: 6px;
                overflow: hidden;
                }

                .section-title {
                background: #333;
                padding: 12px;
                cursor: pointer;
                border-radius: 6px;
                text-align: left;
                font-weight: bold;
                transition: background 0.3s ease-in-out;
                }



                .section-content {
                display: none;
                padding: 15px;
                background: #1E1E1E;
                border-left: 1px solid #f30957c0;
                box-shadow: 0 0 10px rgba(139, 0, 0, 0.3);
                transition: all 0.3s ease-in-out;
                }

                form {
                display: flex;
                flex-direction: column;
                }

                label {
                display: flex;
                align-items: center;
                font-weight: bold;
                margin-bottom: 5px;
                }

                input {
                flex: 2;
                padding: 10px;
                padding-right: 15px;
                border: none;
                background: #252525;
                color: #fff;
                border-radius: 5px;
                font-size: 14px;
                margin-bottom: 10px;
                border: 1px solid #444;
                }

                button {
                padding: 12px;
                background: #dc3545;
                color: white;
                border: none;
                border-radius: 5px;
                font-size: 16px;
                cursor: pointer;
                margin-top: 10px;
                width: 100%;
                transition: background 0.3s;
                }

                .save-btn {
                background: #183e66;
                color: rgba(255, 255, 255, 0.788);
                }

                .save-btn:hover {
                background: #0056b3;
                box-shadow: 0 0 10px rgba(0, 91, 179, 0.5);
                }

                button:hover {
                background: #8B0000;
                }

                @media (max-width: 480px) {
                .container {
                    width: 90%;
                }

                input {
                    width: calc(100% - 20px);
                }
                }

                .footer {
                margin-top: 20px;
                font-size: 12px;
                color: #777;
                }
            </style>
                <script>
                    function toggleSection(id) {
                        var content = document.getElementById(id);
                        var section = content.parentElement;
                        if (content.style.display === "block") {
                            content.style.display = "none";
                            section.classList.remove("active");
                        } else {
                            content.style.display = "block";
                            section.classList.add("active");
                        }
                    }

                    // Agrega un listener para todos los formularios
                    document.addEventListener("DOMContentLoaded", function() {
                        document.querySelectorAll("form").forEach(form => {
                            form.addEventListener("submit", function(event) {
                                event.preventDefault(); // Evita recargar la página
                                let formData = new FormData(this);

                                fetch("/save", {
                                    method: "POST",
                                    body: new URLSearchParams(formData) // Convierte FormData en formato URL
                                })
                                .then(response => response.json())
                                .then(data => {
                                    alert(data.message); // Muestra el mensaje de éxito o error
                                if (data.reload) {
                                        setTimeout(() => {
                                            window.location.reload(); // Recarga la página después de guardar
                                        }, 500);
                                    }
                                    })
                                .catch(error => {
                                    alert("Error saving data.");
                                });
                            });
                        });
                    });
                </script>
            </head>

          <body>
            <div class="container">
                <h1>ESP32-AP-Config 🚀</h1>

                <!-- Access Point Section -->
                <div class="section">
                    <div class="section-title" onclick="toggleSection('ap-config')">📶 Access Point Settings</div>
                    <div class="section-content" id="ap-config">
                        <form>
                            <div class="input-group">
                                <label>SSID:</label>
                                <input type="text" name="ap_ssid" value=")rawliteral" + storedSSID + R"rawliteral(" required>
                            </div>
                            <div class="input-group">
                                <label>Password:</label>
                                <input type="text" name="ap_password" value=")rawliteral" + storedPassword + R"rawliteral(" required>
                            </div>
                            <button class="save-btn" type="submit">Save</button>
                        </form>
                    </div>
                </div>

                <!-- Node WiFi Section -->
                <div class="section">
                    <div class="section-title" onclick="toggleSection('wifi-config')">🌐 Node WiFi Settings</div>
                    <div class="section-content" id="wifi-config">
                        <form>
                            <div class="input-group">
                                <label>WiFi Network:</label>
                                <input type="text" name="wifi_ssid" value=")rawliteral" + storedwifiSSID + R"rawliteral(" required>
                            </div>
                            <div class="input-group">
                                <label>Password:</label>
                                <input type="text" name="wifi_password" value=")rawliteral" + storedwifiPassword + R"rawliteral(" required>
                            </div>
                            <button class="save-btn" type="submit">Save</button>
                        </form>
                    </div>
                </div>

                <!-- Variables Settings Section -->
                <div class="section">
                    <div class="section-title" onclick="toggleSection('var-config')">⚙️ Variables Settings</div>
                    <div class="section-content" id="var-config">
                        <form method="POST" action="/save">
                            )rawliteral";

                            // Agregar dinámicamente los campos de variables almacenadas
                            for (const auto& pair : variables) {
                                html += "<div class='input-group'>";
                                html += "<label>" + pair.first + ":</label>";
                                html += "<input type='text' name='" + pair.first + "' value='" + pair.second + "' required>";
                                html += "</div>";
                            }

                            html += R"rawliteral(
                            <button class="save-btn" type="submit">Save</button>
                        </form>
                    </div>
                </div>

                <br>
                <a href="/cancel"><button class="cancel-btn">Cancel AP</button></a>
                <br>
                <div class="footer">© 2025 by Yerson001</div>
            </div>
        </body>
            </html>

        )rawliteral";

        server.send(200, "text/html", html);
    }

    void Config::handleSave()
    {
        if (server.hasArg("ap_ssid") && server.hasArg("ap_password"))
        {
            preferences.putString("ssid", server.arg("ap_ssid"));
            preferences.putString("password", server.arg("ap_password"));
            server.send(200, "application/json", "{\"status\":\"success\", \"message\":\"Saved successfully!\"}");
        }
        else if (server.hasArg("wifi_ssid") && server.hasArg("wifi_password"))
        {
            preferences.putString("wifissid", server.arg("wifi_ssid"));
            preferences.putString("wifipassword", server.arg("wifi_password"));
            server.send(200, "application/json", "{\"status\":\"success\", \"message\":\"Saved successfully!\"}");
        }
        else
        {
            bool saved = false;
    
            for (uint8_t i = 0; i < server.args(); i++)
            {
                String key = server.argName(i);
                String value = server.arg(i);
    
                if (!key.isEmpty() && !value.isEmpty())
                {
                    preferences.putString(key.c_str(), value);
                    //Serial.println("Key: " + key + " Value: " + value);
                    saved = true;
                }
            }
    
            if (saved)
            {
                server.send(200, "application/json", "{\"status\":\"success\", \"message\":\"Saved successfully!\"}");
            }
            else
            {
                server.send(400, "application/json", "{\"status\":\"error\", \"message\":\"Error: Incomplete data\"}");
            }
        }
    }


    void Config::addVariable(const String &key, const String &defaultValue) 
    {
        if (!preferences.isKey(key.c_str())) {  
            preferences.putString(key.c_str(), defaultValue.c_str());
        }
        variables[key] = preferences.getString(key.c_str(), defaultValue.c_str());
    }

    String Config::getVariable(const String& key) 
    {
        return preferences.getString(key.c_str(), "");
    }
    int Config::getVariableInt(const String& key) {
        return preferences.getString(key.c_str(), "0").toInt();  
    }
    
    double Config::getVariableDouble(const String& key) {
        return preferences.getString(key.c_str(), "0.0").toDouble(); 
    }

    void Config::setVariable(const String& key, const String& value) {
        preferences.putString(key.c_str(), value);
        variables[key] = value;
    }

    void Config::handleCancel()
    {
        server.send(200, "text/html", "<h1> RESTARTED ESP </h1>");
        delay(500);
        ESP.restart();
    }

    void Config::handleClient()
    {
        server.handleClient();
    }
}