#include "buzzer.h"

/**
 * Initialize the buzzer.
 * Resets all fields to default values.
 * @param buzzer Pointer to the buzzer structure.
 */
void Buzzer_Init(Fuz_Buzzer_t *buzzer) {
    buzzer->BuzzEndTime = 0;
    buzzer->ActivePattern = (Fuz_BuzzerPattern_t){
        .IsActive = 0,
        .Length = 0
    };
}

/**
 * Start a non-blocking beep.
 * Sets the end time and starts the buzzer.
 * @param buzzer Pointer to the buzzer structure.
 * @param currentTime Current time in milliseconds.
 * @param duration Duration of the beep in milliseconds.
 */
void Buzzer_StartBeep(Fuz_Buzzer_t *buzzer, uint32_t currentTime, uint16_t duration) {
    buzzer->BuzzEndTime = currentTime + duration;
    buzzer->Start();
}

/**
 * Update the buzzer state for a single beep.
 * Stops the buzzer if the duration has elapsed.
 * @param buzzer Pointer to the buzzer structure.
 * @param currentTime Current time in milliseconds.
 */
void Buzzer_Update(Fuz_Buzzer_t *buzzer, uint32_t currentTime) {
    if (!buzzer) return;

    if (currentTime >= buzzer->BuzzEndTime) {
        buzzer->BuzzEndTime = 0;
        buzzer->Stop();
    }
}

/**
 * Start a pattern playback on the buzzer.
 * Copies the pattern structure into the buzzer.
 * @param buzzer Pointer to the buzzer structure.
 * @param pattern Pointer to the pattern structure.
 */
void Buzzer_StartPattern(Fuz_Buzzer_t *buzzer, Fuz_BuzzerPattern_t *pattern) {
    buzzer->ActivePattern = *pattern;
}

/**
 * Update the buzzer state for pattern playback.
 * Toggles the buzzer state based on the pattern timings.
 * @param buzzer Pointer to the buzzer structure.
 * @param currentTime Current time in milliseconds.
 */
void Buzzer_UpdatePattern(Fuz_Buzzer_t *buzzer, uint32_t currentTime) {
    if (!buzzer) return;

    if (!buzzer->ActivePattern.Length) {
        return;
    }
    if (!buzzer->ActivePattern.IsActive) {
        if (currentTime >= buzzer->ActivePattern.StartTime) {
            buzzer->ActivePattern.NextToggleTime = currentTime;
            buzzer->ActivePattern.CurrentIndex = 0;
            buzzer->ActivePattern.IsActive = 1;
        } else {
            return;
        }
    }

    if (currentTime >= buzzer->ActivePattern.NextToggleTime) {
        if (buzzer->ActivePattern.CurrentIndex < buzzer->ActivePattern.Length) {
            buzzer->Toggle();
            buzzer->ActivePattern.NextToggleTime = currentTime + buzzer->ActivePattern.Pattern[buzzer->ActivePattern.CurrentIndex];
            buzzer->ActivePattern.CurrentIndex++;
        } else {
            buzzer->ActivePattern.IsActive = 0;
            buzzer->Stop();
        }
    }
}
