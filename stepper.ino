/*
Notes:

Timer Counter Control Register 1A
TCCR1A:      7       6       5       4       3       2       1       0
          COM1A1   COM1A0   COM1B1  COM1B0    -       -     WGM11    WGM10






*/



const byte LED = 13;

void setup(){
    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    // Turn off Interrupts so we can set one up:
    cli();

    //Set Timer/Counter Control Register 1 A and B to Zero as initialization:
    TCCR1A = 0;
    TCCR1B = 0;

    // Set Clock Prescaler to 1024. This turns our 16MHz clock to ~16KHz
    TCCR1B |= B00000101;

    // Set the Mode of the Counter to Clear on Compare Match (CTC)
    TCCR1B |= B00001000;
    // Enable this interrupt and use the OCR1A register to Compare.
    TIMSK1 |= B00000010;

    // Set the Compare Value for the MAX counter value 
    OCR1A = 16000;

    // Enable Interrupts:
    sei();
}

ISR(TIMER1_COMPA_vect){
    static boolean state = true;
    state = !state;
    digitalWrite(LED, state ? HIGH : LOW);
}


void printToScreen(){
    static int16_t count = 0;
    // count = (TCNT1H << 8) + TCNT1L; // Accessing the registers (compiler can do this for us)
    count = TCNT1;
    Serial.println(count, DEC);
    delay(250);
}


void loop() {
    printToScreen();
}