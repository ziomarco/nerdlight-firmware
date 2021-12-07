#include <ArduinoJson.h>

void control_light_from_json(char *json_string)
{
    StaticJsonDocument<128> payload;

    DeserializationError error = deserializeJson(payload, json_string);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    int r = payload["r"];
    int g = payload["g"];
    int b = payload["b"];
    int msTimeout = payload["msTimeout"];

    color(r, g, b);

    if (msTimeout > 0)
    {
        delay(msTimeout);
        light_off();
    }
}
