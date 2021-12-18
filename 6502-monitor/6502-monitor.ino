#define CLOCK 2
#define RW 39

const char ADDR[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
const char DATA[] = { 23, 25, 27, 29, 31, 33, 35, 37 };


void setup()
{
    // put your setup code here, to run once:
    for (byte i = 0; i < 16; i++) pinMode(ADDR[i], INPUT);
    for (byte i = 0; i < 8; i++) pinMode(DATA[i], INPUT);
    pinMode(CLOCK, INPUT);
    pinMode(RW, INPUT);
    Serial.begin(57600);
    
    attachInterrupt(digitalPinToInterrupt(CLOCK), OnClock, RISING);
}


// Only print address and data values on clock pulse
void OnClock()
{
    char addrStr[16];
    unsigned int address = 0;
    for (byte i = 0; i < 16; i++)
    {
        int bit = digitalRead(ADDR[i]);
        Serial.print(bit);
        address = (address << 1) + bit;
    }
    sprintf(addrStr, "  %04x    %c    ", address, digitalRead(RW) ? 'R' : 'W');
    Serial.print(addrStr);

    char dataStr[5];
    unsigned int data = 0;
    for (byte i = 0; i < 8; i++)
    {
        int bit = digitalRead(DATA[i]);
        Serial.print(bit);
        data = (data << 1) + bit;
    }
    sprintf(dataStr, "  %02x", data);
    Serial.println(dataStr);
}


void loop()
{
    // put your main code here, to run repeatedly:
    
}
