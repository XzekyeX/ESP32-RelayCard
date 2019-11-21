#include "IO.h"
#include "index.h"
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>
#include <esp_system.h>
// Set these to your desired credentials.

const char* ssid = "ESP32-RelayCard";
const char* password = "relaycard";
const unsigned int gpio_size = 6;
IO* gpio = new IO[gpio_size]{ { 16, true }, { 17, true }, { 5, true }, { 18, true }, { 19, true }, { 21, true } };

#define V_REF 1100
#define MAP_SENSOR_PIN ADC1_CHANNEL_0
esp_adc_cal_characteristics_t characteristics;

String header;

WebServer server(80);

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

void sendWebpage()
{
    String page = webpage;
    server.send(200, "text/html", page);
}

void sendGPIOS()
{
    String v;
    for (int i = 0; i < gpio_size; i++) {
        v += gpio[i].toStr();
        v += ";";
    }
    server.send(200, "text/plane", v);
}

/**
 * Receive server arguments and change io states 
*/
void sendGPIO()
{
    String value;
    if (server.args() > 0) {
        for (int i = 0; i < server.args(); i++) { // received html address arguments
            if (server.argName(i) == "io") {
                int pin = atoi(server.arg(i).c_str());
                for (int j = 0; j < gpio_size; j++) {
                    if (pin == gpio[j].pin) {
                        gpio[j].changeState();
                        value += gpio[j].toStr();
                    }
                }
            }
        }
    }
    server.send(200, "text/plane", value);
}

void setup()
{
    // for (int i = 0; i < gpio_size; i++) {
    //     pinMode(gpio[i].pin, gpio[i].output ? OUTPUT : INPUT);
    //     digitalWrite(gpio[i].pin, gpio[i].state ? HIGH : LOW);
    // }
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(MAP_SENSOR_PIN, ADC_ATTEN_DB_2_5);
    esp_adc_cal_get_characteristics(V_REF, ADC_ATTEN_DB_2_5, ADC_WIDTH_BIT_12, &characteristics);

    Serial.begin(115200);
    Serial.println();
    Serial.println("Configuring access point...");

    // You can remove the password parameter if you want the AP to be open.
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", sendWebpage);
    server.on("/gpio", sendGPIO); // Sends GPIO data to client
    server.on("/gpios", sendGPIOS);

    server.begin();
    Serial.println("Server started");
}

void loop()
{
    server.handleClient();
    delay(1);
}
