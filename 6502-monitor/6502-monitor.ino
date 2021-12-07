const char ADDR[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
const char DATA[] = { 39, 41, 43, 45, 47, 49, 51, 53 };
#define CLOCK 2
#define RW 3


void setup()
{
    // put your setup code here, to run once:
    for (int i = 0; i < 16; i++)
    {
        pinMode(ADDR[i], INPUT);
    }
    for (int i = 0; i < 8; i++)
    {
        pinMode(DATA[i], INPUT);
    }
    pinMode(CLOCK, INPUT);
    pinMode(RW, INPUT);
    Serial.begin(57600);
    
    attachInterrupt(digitalPinToInterrupt(CLOCK), OnClock, RISING);
}


// Only print address and data values on clock pulse
void OnClock()
{
    char output[15];
    
    unsigned int address = 0;
    for (int i = 0; i < 16; i++)
    {
        int bit = digitalRead(ADDR[i]);
        Serial.print(bit);
        address = (address << 1) + bit;
    }
    
    Serial.print("   ");
    
    unsigned int data = 0;
    for (int i = 0; i < 8; i++)
    {
        int bit = digitalRead(DATA[i]);
        Serial.print(bit);
        data = (data << 1) + bit;
    }

    sprintf(output, "   %04x  %c %02x", address, digitalRead(RW) ? 'R' : 'W', data);
    Serial.println(output);
}


void loop() {
    // put your main code here, to run repeatedly:
    
}
