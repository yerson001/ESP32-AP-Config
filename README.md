# ESP32-AP-Config 🚀

**ESP32-AP-Config** es una librería para configurar WiFi mediante un **Access Point** en ESP32. Permite modificar la configuración de la red WiFi y otros parámetros desde una interfaz web, guardando los cambios en la memoria del ESP32.

## 📦 Requisitos

Para utilizar esta librería necesitas:
- Un ESP32 (cualquier modelo compatible con WiFi).
- **Arduino IDE** (con la extensión ESP32) o **PlatformIO**.
- Librerías adicionales:
  - `WiFi.h` (incluida en ESP32 por defecto).
  - `Preferences.h` (para guardar datos en la memoria no volátil del ESP32).

## 📥 Instalación

### 🔹 Arduino IDE

1. Descarga el repositorio como `.zip` desde [GitHub](https://github.com/tu_usuario/ESP32-AP-Config).
2. Abre Arduino IDE y ve a **Sketch > Incluir librería > Añadir biblioteca .ZIP**.
3. Selecciona el archivo `.zip` y presiona **Aceptar**.

### 🔹 PlatformIO

Ejecuta en la terminal dentro de tu proyecto:
```sh
pio pkg install --library "https://github.com/tu_usuario/ESP32-AP-Config.git"
```

## 🚀 Uso

Ejemplo básico de uso:

```cpp
#include <ESP32-AP-Config.hpp>

ESP32AP::Config apConfig;

void setup() {
    Serial.begin(115200);
    apConfig.iniciar();
}

void loop() {
    apConfig.manejarCliente();
}
```

## ⚙️ Funcionamiento

1. El ESP32 crea un **Access Point** con un portal web.
2. Desde un dispositivo (PC, móvil), conéctate al WiFi del ESP32.
3. Abre un navegador y accede a `http://192.168.4.1`.
4. Modifica la configuración de WiFi y otros parámetros.
5. Los cambios se guardan en la memoria del ESP32.
6. El ESP32 se reinicia y se conecta a la red configurada.

## 📜 Licencia

Este proyecto está bajo la **licencia MIT**. Puedes usarlo y modificarlo libremente. 🎉

