void setup_wifi()
{
    espWiFiClient.setBufferSizes(512, 512);
    while (WiFi.status() != WL_CONNECTED)
    {
        light_off();
        delay(500);
        Serial.print(".");
        light_red();
    }

    timeClient.begin();
    while (!timeClient.update())
    {
        timeClient.forceUpdate();
    }
    espWiFiClient.setX509Time(timeClient.getEpochTime());
    delay(1500);
}
