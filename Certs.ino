void load_mqtt_certificates()
{
    // Load certificate file
    File cert = SPIFFS.open("/cert.der", "r"); //replace cert.crt with your uploaded file name
    if (!cert)
    {
        Serial.println("Failed to open cert file");
    }
    else
        Serial.println("Successfully opened cert file");

    delay(1000);

    if (espWiFiClient.loadCertificate(cert)) // add the thing certificate to the client
        Serial.println("cert loaded");
    else
        Serial.println("cert not loaded");

    // Load private key file
    File private_key = SPIFFS.open("/private.der", "r"); //replace private with your uploaded file name
    if (!private_key)
    {
        Serial.println("Failed to open private cert file");
    }
    else
        Serial.println("Successfully opened private cert file");

    delay(1000);

    if (espWiFiClient.loadPrivateKey(private_key)) // add the private key to the client
        Serial.println("private key loaded");
    else
        Serial.println("private key not loaded");

    // Load CA file
    File ca = SPIFFS.open("/ca.der", "r"); //replace ca with your uploaded file name
    if (!ca)
    {
        Serial.println("Failed to open ca ");
    }
    else
        Serial.println("Successfully opened open ca");

    delay(1000);

    if (espWiFiClient.loadCACert(ca)) // add the AWS root certificate to the client
        Serial.println("ca loaded");
    else
        Serial.println("ca failed");

    print_heap();
}
