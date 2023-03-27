#include "mbed.h"

PwmOut LED(D6);
AnalogIn lightSensor(A0);
AnalogOut aout(PA_4);

Thread LEDThread; 
Thread sensorThread;

float sample[20];
float sensorValue;

void pwmLED ()
{
    int cnt = 0;
    while (true)
    {
        LED.pulsewidth_us(5000 * sample[cnt]);
        cnt++;
        if (cnt == 20) cnt = 0;
        ThisThread::sleep_for(50ms);
    }
}

void sensor()
{
    while (true){
        sensorValue = lightSensor.read();
        aout = sensorValue;
        ThisThread::sleep_for(1ms);
    }
}

int main()
{
    for (int i = 0; i < 20; i++){
        if (i < 5)
            sample[i] = (float)i / 5;
        else if (i < 10)
            sample[i] = 1.;
        else if (i < 15)
            sample[i] = 1. - (i - 10.) / 5;
        else
            sample[i] = 0;
    }
    LED.period_ms(5);
    LEDThread.start(pwmLED);
    sensorThread.start(sensor);
    while (true){
        printf("%f\n", sensorValue);
        ThisThread::sleep_for(10ms);
    }
}