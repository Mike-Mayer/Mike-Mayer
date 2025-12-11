// Example sketch for ESP32-WROOM-32D targeting HiveMQ Cloud via TLS MQTT.
// Board selection in Arduino IDE: ESP32-WROOM-32D (ESP32 Dev Module works as well).
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Wi-Fi credentials (fill in your network)
const char *ssid = "<YOUR_WIFI_SSID>";
const char *password = "<YOUR_WIFI_PASSWORD>";

// HiveMQ Cloud endpoint (TLS)
const char *mqtt_server = "aef1a2efc8b74a1f87b6938fe3d169de.s2.eu.hivemq.cloud";
const uint16_t mqtt_port = 8883; // TLS port

// MQTT credentials
const char *mqtt_user = "sunny";
const char *mqtt_password = "pw4";

// Topics
const char *topic_active = "campermonitor/esp32/active";

WiFiClientSecure secureClient;
PubSubClient client(secureClient);

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  uint8_t retries = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (++retries >= 60)
    {
      Serial.println("\nRestarting due to WiFi timeout");
      ESP.restart();
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    String clientId = "ESP32-WROOM-32D-";
    clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      client.publish(topic_active, "online", true);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  // HiveMQ Cloud requires TLS on port 8883. No root certificate is added here
  // because this demo uses setInsecure(); for production pin the server cert.
  secureClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);

  setup_wifi();
  reconnect();
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // Placeholder for sensor publishing
  // Example: client.publish("campermonitor/<sensor>/<messwert>", "123");
}
