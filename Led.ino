void setup_pins()
{
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(R_Pin, OUTPUT);
    pinMode(G_Pin, OUTPUT);
    pinMode(B_Pin, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    analogWrite(R_Pin, 0);
    analogWrite(G_Pin, 0);
    analogWrite(B_Pin, 0);
}

void color(unsigned char red, unsigned char green, unsigned char blue)
{
    Serial.printf("Coloring: R: %d G: %d B: %d\n", red, green, blue);
    analogWrite(R_Pin, red);
    analogWrite(G_Pin, green);
    analogWrite(B_Pin, blue);
}

void light_off()
{
    analogWrite(R_Pin, 0);
    analogWrite(G_Pin, 0);
    analogWrite(B_Pin, 0);
}

void light_white()
{
    analogWrite(R_Pin, 255);
    analogWrite(G_Pin, 255);
    analogWrite(B_Pin, 255);
}

void light_green()
{
    analogWrite(R_Pin, 0);
    analogWrite(G_Pin, 255);
    analogWrite(B_Pin, 0);
}

void light_red()
{
    analogWrite(R_Pin, 255);
    analogWrite(G_Pin, 0);
    analogWrite(B_Pin, 0);
}

void light_yellow()
{
    analogWrite(R_Pin, 255);
    analogWrite(G_Pin, 255);
    analogWrite(B_Pin, 0);
}

void activity_led()
{
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);                   
    digitalWrite(LED_BUILTIN, HIGH);
}
