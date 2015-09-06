#include <bcm2835.h>

#define PIN RPI_V2_GPIO_P1_03

int lightLED(void){
    if (!bcm2835_init())
                  result = 1;
    else{
        bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

        bcm2835_gpio_write(PIN, LOW);

        bcm2835_delay(5000);

        bcm2835_gpio_write(PIN, HIGH);

        result = bcm2835_close();
    }
}