void send_heartbeat()
{
    Serial.println("Sending heartbeat");
    mqttClient.publish(topicPub, (char *)"{\"status\": \"ALIVE\"}");
    Serial.println("Heartbeat sent");
    print_heap();
}

void mqtt_reconnect()
{
    // Loop until we're reconnected
    while (!mqttClient.connected())
    {
        light_yellow();
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect(mac))
        {
            Serial.println("Connected to AWS");
            light_green();
            delay(1000);
            light_white();
            // Once connected, publish an announcement...
            Serial.println("Sending first heartbeat");
            send_heartbeat();
            Serial.println("First heartbeat sent");
            // ... and resubscribe
            Serial.println("Subscribed to topic:");
            Serial.println(topicSub);
            mqttClient.subscribe(topicSub);
            light_off();
        }
        else
        {
            Serial.print("Failed to connect to AWS, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" Trying again in 5 seconds");
            light_red();

            char buf[256];
            espWiFiClient.getLastSSLError(buf, 256);
            Serial.print("WiFiClientSecure SSL error: ");
            Serial.println(buf);

            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
