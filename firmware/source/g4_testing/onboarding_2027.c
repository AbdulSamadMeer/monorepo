#include "g4_testing.h"
#if (G4_TESTING_CHOSEN == TEST_ONBOARDING_2027)

#include <stdint.h>

#include "common/phal_G4/gpio/gpio.h"
#include "common/phal_G4/rcc/rcc.h"
#include "common/utils/countof.h"
#include "common/rtos/rtos.h"
#include "main.h"


// Hmmm... something may go here
#define LED_USER_PORT GPIOA
#define LED_USER_PIN  5


PHAL_GPIO_InitConfig_t gpio_config[] = {
    // Hmmm... something may go here
    PHAL_GPIO_INIT_OUTPUT(LED_USER_PORT, LED_USER_PIN, GPIO_OUTPUT_HIGH_SPEED)
};

void HardFault_Handler();

void heartbeat_LED() { PHAL_GPIO_toggle(LED_USER_PORT, LED_USER_PIN); }

// Hmmm... something(s) may go here
RTOS_DEFINE_TASK(heartbeat_LED, 800, TASK_PRIORITY_NORMAL, STACK_256);



int main() {
    // NUCLEO-G474RE does not have an external oscillator so use the internal 16MHz HSI clock
    PHAL_RCC_init(PHAL_RCC_HSI_16MHZ);

    if (!PHAL_GPIO_init(gpio_config, countof(gpio_config))) {
        HardFault_Handler();
    }

    // Hmmm... something(s) may go here
    RTOS_START_TASK(heartbeat_LED);

    return 0;
}


void HardFault_Handler() {
    while (1) {
        __asm__("nop");
    }
}

#endif // G4_TESTING_CHOSEN == TEST_ONBOARDING_2027
