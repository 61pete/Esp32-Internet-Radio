#include <WiFi.h>
#include <VS1053.h>
#include <U8g2lib.h>

// Define the VS1053 pins
#define VS1053_CS     32
#define VS1053_DCS    33
#define VS1053_DREQ   35

// Button pins
#define BUTTON_NEXT  13
#define BUTTON_PREV  12

// OLED Display
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// WiFi settings example, substitute your own
const char *ssid = "ChomeYVR";
const char *password = "138138138";

// Radio station details
const char* stationNames[] = {"ERT Kosmos", "FFH Lounge", "FFH Summer"};
const char* stationHosts[] = {"radiostreaming.ert.gr", "mp3.ffh.de", "mp3.ffh.de"};
const char* stationPaths[] = {"/ert-kosmos", "/ffhchannels/hqlounge.mp3", "/ffhchannels/hqsummerfeeling.mp3"};
int currentStation = 0;
const int totalStations = sizeof(stationNames) / sizeof(stationNames[0]);

// VS1053 instance
VS1053 player(VS1053_CS, VS1053_DCS, VS1053_DREQ);
WiFiClient client;

int textPosition = 128;
unsigned long previousMillis = 0;  // Store the last time the display was updated
const long interval = 50;  // Interval for updating the display (50 ms)

void setup() {
    Serial.begin(115200);

    // Wait for VS1053 and PAM8403 to power up
    delay(3000);

    u8g2.begin();
    u8g2.setFlipMode(1);  // Flip the display 180 degrees
    u8g2.setFont(u8g2_font_ncenB08_tr);

    // Initial messages
    u8g2.clearBuffer();
    u8g2.drawStr(0, 16, "Starting Radio...");
    u8g2.sendBuffer();
    delay(2000);

    u8g2.clearBuffer();
    u8g2.drawStr(0, 16, "Starting Engine...");
    u8g2.sendBuffer();
    delay(2000);

    u8g2.clearBuffer();
    u8g2.drawStr(0, 16, "Connecting to WiFi...");
    u8g2.sendBuffer();

    Serial.println("\n\nSimple Radio Node WiFi Radio");

    SPI.begin();

    player.begin();
    if (player.getChipVersion() == 4) {
        player.loadDefaultVs1053Patches();
    }
    player.switchToMp3Mode();
    player.setVolume(100);

    Serial.print("Connecting to SSID ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    // Disable WiFi power save mode
    WiFi.setSleep(false);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());

        u8g2.clearBuffer();
        u8g2.drawStr(0, 16, "Connected Yay!");
        u8g2.sendBuffer();
        delay(2000);
    } else {
        Serial.println("WiFi not connected");

        u8g2.clearBuffer();
        u8g2.drawStr(0, 16, "Not Connected");
        u8g2.sendBuffer();
        delay(2000);
    }

    pinMode(BUTTON_NEXT, INPUT_PULLUP);
    pinMode(BUTTON_PREV, INPUT_PULLUP);

    // Change font for the main display
    u8g2.setFont(u8g2_font_profont17_mr);

    displayStation();
    connectToHost();
}

void loop() {
    if (!client.connected()) {
        Serial.println("Reconnecting...");
        connectToHost();
    }

    if (client.available() > 0) {
        uint8_t buffer[32];
        size_t bytesRead = client.readBytes(buffer, sizeof(buffer));
        player.playChunk(buffer, bytesRead);
    }

    handleButtons();
    scrollText();
}

void connectToHost() {
    Serial.print("Connecting to ");
    Serial.println(stationHosts[currentStation]);

    if (!client.connect(stationHosts[currentStation], 80)) {
        Serial.println("Connection failed");
        return;
    }

    Serial.print("Requesting stream: ");
    Serial.println(stationPaths[currentStation]);

    client.print(String("GET ") + stationPaths[currentStation] + " HTTP/1.1\r\n" +
                 "Host: " + stationHosts[currentStation] + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Skip HTTP headers
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
            break;
        }
    }

    Serial.println("Headers received");
}

void handleButtons() {
    static bool lastButtonNextState = HIGH;
    static bool lastButtonPrevState = HIGH;

    bool currentButtonNextState = digitalRead(BUTTON_NEXT);
    bool currentButtonPrevState = digitalRead(BUTTON_PREV);

    if (lastButtonNextState == HIGH && currentButtonNextState == LOW) {
        nextStation();
    }
    if (lastButtonPrevState == HIGH && currentButtonPrevState == LOW) {
        previousStation();
    }

    lastButtonNextState = currentButtonNextState;
    lastButtonPrevState = currentButtonPrevState;
}

void nextStation() {
    currentStation = (currentStation + 1) % totalStations;
    displayStation();
    connectToHost();
}

void previousStation() {
    currentStation = (currentStation - 1 + totalStations) % totalStations;
    displayStation();
    connectToHost();
}

void displayStation() {
    textPosition = 128;  // Reset text position to start from the right
    u8g2.clearBuffer();
    u8g2.drawLine(0, 0, 127, 0);
    u8g2.drawLine(0, 31, 127, 31);
    u8g2.setCursor(textPosition, 22);
    u8g2.print(stationNames[currentStation]);
    u8g2.sendBuffer();
}

void scrollText() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        textPosition--;  // Move text to the left
        if (textPosition < -u8g2.getUTF8Width(stationNames[currentStation])) {
            textPosition = 128;  // Reset position to start from the right again
        }

        u8g2.clearBuffer();
        u8g2.drawLine(0, 0, 127, 0);
        u8g2.drawLine(0, 31, 127, 31);
        u8g2.setCursor(textPosition, 22);
        u8g2.print(stationNames[currentStation]);
        u8g2.sendBuffer();
    }
}