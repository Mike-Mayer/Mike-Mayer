# ESP32-WROOM-32D → HiveMQ TLS MQTT starter

Beispielsketch für die Arduino IDE, um einen ESP32-WROOM-32D stabil per TLS an HiveMQ Cloud anzubinden und erste Test-Topics zu senden. Sensordaten sollen später nach `campermonitor/<sensor>/<messwert>` publiziert werden; als Test wird `campermonitor/esp32/active` mit dem Wert `"online"` gesetzt.

## Voraussetzungen
- Arduino IDE mit installiertem ESP32 Board-Paket (Board-Auswahl: **ESP32-WROOM-32D** bzw. generisch "ESP32 Dev Module")
- Bibliotheken: `PubSubClient` (über den Arduino Library Manager)
- WLAN-Zugangsdaten (2.4 GHz) eintragen

## Sketch nutzen
1. Datei [`esp32_hivemq_example.ino`](./esp32_hivemq_example.ino) in der Arduino IDE öffnen.
2. Im Kopf des Sketches `ssid` und `password` auf dein WLAN anpassen.
3. Hochladen. Die serielle Ausgabe zeigt Verbindungsstatus und den Publish auf `campermonitor/esp32/active`.

### TLS-Hinweis
Der Sketch nutzt `WiFiClientSecure::setInsecure()` und verzichtet damit auf die Validierung des HiveMQ-Zertifikats – ausreichend für dieses nicht-sensitive Szenario. Für Produktion solltest du stattdessen das HiveMQ-Root-CA-Zertifikat inline hinterlegen und **kein** `setInsecure()` verwenden.

### Topics für Sensordaten
Spätere Messwerte sollten diesem Muster folgen:
```
campermonitor/<sensor>/<messwert>
```
Beispiele: `campermonitor/oria/temp` oder `campermonitor/oria/humidity`.

## MQTT Zugangsdaten
- Broker: `aef1a2efc8b74a1f87b6938fe3d169de.s2.eu.hivemq.cloud`
- Port: `8883` (TLS)
- Benutzer: `sunny`
- Passwort: `pw4`
