#include <ESP32-AP-Config.hpp>
#include <ctime> 

ESP32AP::Config apConfig;  

// Global variables 
String api_url;   
int timeout;     
double threshold; 

void setup() {
    Serial.begin(115200);
    apConfig.setupAccesPoint();  

    // Store default values if they do not exist
    apConfig.addVariable("api_url", "http://colecheck/attendance/api/");
    apConfig.addVariable("timeout", "5000");  
    apConfig.addVariable("threshold", "3.14"); 
    
    // Retrieve stored values and convert them if needed
    api_url = apConfig.getVariable("api_url");
    timeout = apConfig.getVariable("timeout").toInt();  
    threshold = apConfig.getVariable("threshold").toDouble();  
    Serial.println("Configuration initialized");
}

void loop() {
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    char timeString[9]; 
    strftime(timeString, sizeof(timeString), "%H:%M:%S", timeinfo);

    // Print stored 
    Serial.print("[");
    Serial.print(timeString);
    Serial.print("] API_URL: ");
    Serial.print(api_url);
    Serial.print(" | Timeout: ");
    Serial.print(timeout);
    Serial.print(" | Threshold: ");
    Serial.println(threshold);


    delay(2000);
    apConfig.handleClient();  
}