#include "mbed.h"

PwmOut LED(D6);
AnalogIn lightSensor(A0);
AnalogOut aout(PA_4);

Thread LEDThread; 
Thread sensorThread;
float sample[400];

void pwmLED()
{
    int cnt = 0;
    while (true)
    {
        LED.pulsewidth_us(4000 * sample[cnt]);
        cnt++;
        if (cnt == 400) cnt = 0;
        ThisThread::sleep_for(10ms);
    }
}

void sensor()
{
    while (true){
        aout = lightSensor;
        ThisThread::sleep_for(1ms);
    }
}

int main()
{
    for (int i = 0; i < 400; i++){
        if (i < 100)
            sample[i] = (float)i / 100;
        else if (i < 200)
            sample[i] = 1.;
        else if (i < 300)
            sample[i] = 1. - (i - 200.) / 100;
        else
            sample[i] = 0;
    }
    LED.period_ms(4);
    LEDThread.start(pwmLED);
    sensorThread.start(sensor);
    while (true){
        printf("%f\n", lightSensor.read());
        ThisThread::sleep_for(1ms);
    }
}