#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include <OneWire.h> 
#include <DallasTemperature.h>

// Display
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);

// Sensor
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

// Averaging variables
const int numReadings = 10;
float readings[numReadings] = {NULL};
int readIndex = 0;
float total = 0;
float average = 0;

bool init_ready = false;

void init_timer(){
    cli();
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    OCR1A = 15624;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

void setup(){
    init_timer();
    P.begin();
    sensors.begin(); 

    Serial.begin(9600); 
    Serial.println("Init"); 
    P.displayText("Wait", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
}

void loop(void)
{
    P.displayAnimate();
}

ISR(TIMER1_COMPA_vect){
    sensors.requestTemperatures();

    total = total - readings[readIndex];
    readings[readIndex] = sensors.getTempCByIndex(0);
    total = total + readings[readIndex];

    readIndex = readIndex + 1;

    if (readIndex >= numReadings) {
        readIndex = 0;
        init_ready |= 1;
    }

    average = total / numReadings;

    if(init_ready){
        char charVal[100];
        if(average >= 100 || average <= -100){
            dtostrf(average, 4, 1, charVal);
        }else{
            dtostrf(average, 4, 2, charVal);
        }
        P.displayText(charVal, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    }
}
