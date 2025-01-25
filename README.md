# Buzzer Library

A portable and platform-agnostic library for controlling buzzers in embedded systems. This library allows for both simple single beeps and playback of custom patterns in a non-blocking manner. It abstracts platform-specific GPIO operations, making it easy to integrate with different microcontroller platforms (e.g., PIC, STM32).

---

## Features
- **Non-blocking design**: Uses periodic updates to control the buzzer without halting the main program.
- **Custom patterns**: Play configurable on/off patterns with precise timing.
- **Platform-independent**: Requires user-defined hardware abstraction functions for GPIO operations.

---

## Directory Structure
```
project_root/
|-- Inc/buzzer.h        # Header file defining the library's API
|-- Src/buzzer.c        # Source file implementing the library logic
|-- Src/main.c          # Example usage of the library
|-- README.md           # This file
```

---

## Usage

### 1. Define Hardware Abstraction Functions
Implement the GPIO control functions specific to your hardware platform:

**For PIC platform:**
```c
void __Fuzyonel_Buzzer_Interface_Start() {
    BUZZER_LAT = 1;
}

void __Fuzyonel_Buzzer_Interface_Stop() {
    BUZZER_LAT = 0;
}

void __Fuzyonel_Buzzer_Interface_Toggle() {
    BUZZER_LAT ^= 1;
}
```

**For STM32 platform:**
```c
void __Fuzyonel_Buzzer_Interface_Start() {
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
}

void __Fuzyonel_Buzzer_Interface_Stop() {
    HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
}

void __Fuzyonel_Buzzer_Interface_Toggle() {
    HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);
}
```

### 2. Initialize the Library
In your `main.c`, set up the buzzer:
```c
Fuz_Buzzer_t buzzer = {
    .Start = __Fuzyonel_Buzzer_Interface_Start,
    .Stop = __Fuzyonel_Buzzer_Interface_Stop,
    .Toggle = __Fuzyonel_Buzzer_Interface_Toggle
};

Buzzer_Init(&buzzer);
App.Outputs.Buzzer = &buzzer;
```

### 3. Start a Beep or Pattern
- **Single Beep:**
```c
Buzzer_StartBeep(App.Outputs.Buzzer, App.Time, 100); // 100ms beep
```
- **Pattern Playback:**
```c
const uint16_t patternData[] = {200, 100, 200, 100, 200};
Fuz_BuzzerPattern_t pattern = {
    .Pattern = patternData,
    .Length = 5,
    .StartTime = App.Time + 1000 // Start after 1 second
};

Buzzer_StartPattern(App.Outputs.Buzzer, &pattern);
```

### 4. Periodically Update the Buzzer
Call the update functions in a periodic task (e.g., 1ms timer interrupt or main loop):
```c
void App_Task_1ms() {
    if (App.Outputs.Buzzer) {
        Buzzer_Update(App.Outputs.Buzzer, App.Time);
        Buzzer_UpdatePattern(App.Outputs.Buzzer, App.Time);
    }
}
```

---

## API Reference

### Structures
- `Fuz_Buzzer_t`: Represents a buzzer with its state and control functions.
- `Fuz_BuzzerPattern_t`: Represents a pattern with timings for on/off states.

### Functions
#### Initialization
- `void Buzzer_Init(Fuz_Buzzer_t *buzzer);`
  Initializes the buzzer structure.

#### Single Beep
- `void Buzzer_StartBeep(Fuz_Buzzer_t *buzzer, uint32_t currentTime, uint16_t duration);`
  Starts a single beep for the specified duration.

- `void Buzzer_Update(Fuz_Buzzer_t *buzzer, uint32_t currentTime);`
  Updates the buzzer state for a single beep.

#### Pattern Playback
- `void Buzzer_StartPattern(Fuz_Buzzer_t *buzzer, Fuz_BuzzerPattern_t *pattern);`
  Starts a custom pattern playback.

- `void Buzzer_UpdatePattern(Fuz_Buzzer_t *buzzer, uint32_t currentTime);`
  Updates the buzzer state for pattern playback.

---

## Example
Complete example combining single beep and pattern playback:
```c
void main() {
    Fuz_Buzzer_t buzzer = {
        .Start = __Fuzyonel_Buzzer_Interface_Start,
        .Stop = __Fuzyonel_Buzzer_Interface_Stop,
        .Toggle = __Fuzyonel_Buzzer_Interface_Toggle
    };

    Buzzer_Init(&buzzer);
    App.Outputs.Buzzer = &buzzer;

    Buzzer_StartBeep(App.Outputs.Buzzer, App.Time, 100); // Buzz for 100ms.

    const uint16_t patternData[] = {200, 100, 200, 100, 200};
    Fuz_BuzzerPattern_t pattern = {
        .Pattern = patternData,
        .Length = 5,
        .StartTime = App.Time + 1000 // Start after 1 second
    };
    Buzzer_StartPattern(App.Outputs.Buzzer, &pattern);

    while (1) {
        App_Task_1ms();
    }
}
```

---

## License
The MIT License is a permissive open-source license. Here's a short summary:

* **You can** => Use, copy, modify, merge, publish, distribute, sublicense, and sell the software.
* **You must** => Include the original license notice in any copies or substantial portions of the software.
* **No Warranty** => The software is provided "as is," without any warranty, and the author is not liable for any damages.

---

Feel free to submit issues or feature requests via GitHub!

