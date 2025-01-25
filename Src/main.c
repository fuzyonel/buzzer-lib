#include "buzzer.h"

Fuz_Buzzer_t buzzer;

uint32_t counter = 0;
void main() {
    buzzer = (Fuz_Buzzer_t){
        .Start = __Fuzyonel_Buzzer_Interface_Start,
        .Stop = __Fuzyonel_Buzzer_Interface_Stop,
        .Toggle = __Fuzyonel_Buzzer_Interface_Toggle
    };

    Buzzer_Init(&buzzer);

    Buzzer_StartBeep(&buzzer, counter, 100); // Buzz for 100ms.
    const uint16_t patternData[] = {200, 100, 200, 100, 200};
    Fuz_BuzzerPattern_t pattern = {
        .Pattern = patternData,
        .Length = 5,
        .StartTime = counter + 1000
    }; // Start --_--_-- pattern with 1s delay
    Buzzer_StartPattern(&buzzer, &pattern);

    while(1) {
        counter++;
        Buzzer_Update(&buzzer);
        Buzzer_UpdatePattern(&buzzer);
    }
}

/**
 * @brief Starts the buzzer.
 *
 * This function is part of the user-provided hardware abstraction layer and must
 * be implemented for the target hardware platform.
 *
 * For PIC platform:
 *
 * void __Fuzyonel_Buzzer_Interface_Start() {
 *     BUZZER_LAT = 1;
 * }
 *
 * For ST platform:
 *
 * void __Fuzyonel_Buzzer_Interface_Start() {
 *     HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
 * }
 */
void __Fuzyonel_Buzzer_Interface_Start() {
    BUZZER_LAT = 1;
}

/**
 * @brief Stops the buzzer.
 *
 * This function is part of the user-provided hardware abstraction layer and must
 * be implemented for the target hardware platform.
 *
 * For PIC platform:
 *
 * void __Fuzyonel_Buzzer_Interface_Stop() {
 *     BUZZER_LAT = 0;
 * }
 *
 * For ST platform:
 *
 * void __Fuzyonel_Buzzer_Interface_Stop() {
 *     HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
 * }
 */
void __Fuzyonel_Buzzer_Interface_Stop() {
    BUZZER_LAT = 0;
}

/**
 * @brief Toggles the buzzer state.
 *
 * This function is part of the user-provided hardware abstraction layer and must
 * be implemented for the target hardware platform.
 *
 * For PIC platform:
 *
 * void __Fuzyonel_Buzzer_Interface_Toggle() {
 *     BUZZER_LAT ^= 1;
 * }
 *
 * For ST platform:
 *
 * void __Fuzyonel_Buzzer_Interface_Toggle() {
 *     HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);
 * }
 */
void __Fuzyonel_Buzzer_Interface_Toggle() {
    BUZZER_LAT ^= 1;
}

