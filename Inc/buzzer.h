#ifndef BUZZER_H
#define	BUZZER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

    /**
     * Structure representing a buzzer pattern.
     * Contains the pattern timings and state information for non-blocking playback.
     */
    typedef struct {
        const uint16_t *Pattern;
        uint8_t Length;
        uint8_t CurrentIndex;
        uint32_t NextToggleTime;
        uint32_t StartTime;
        uint8_t IsActive;
    } Fuz_BuzzerPattern_t;

    /**
     * Structure representing a buzzer.
     * Includes state information and platform-specific function pointers for controlling the buzzer.
     */
    typedef struct {
        uint32_t BuzzEndTime;
        Fuz_BuzzerPattern_t ActivePattern;
        void (*Start)(void);
        void (*Stop)(void);
        void (*Toggle)(void);
    } Fuz_Buzzer_t;

    /**
     * Initialize the buzzer.
     * @param buzzer Pointer to the buzzer structure.
     */
    void Buzzer_Init(Fuz_Buzzer_t *buzzer);

    /**
     * Start a non-blocking beep.
     * @param buzzer Pointer to the buzzer structure.
     * @param currentTime Current time in milliseconds.
     * @param duration Duration of the beep in milliseconds.
     */
    void Buzzer_StartBeep(Fuz_Buzzer_t *, uint32_t, uint16_t);

    /**
     * Update the buzzer state for a single beep.
     * Should be called periodically.
     * @param buzzer Pointer to the buzzer structure.
     * @param currentTime Current time in milliseconds.
     */
    void Buzzer_Update(Fuz_Buzzer_t *, uint32_t);

    /**
     * Start a pattern playback on the buzzer.
     * @param buzzer Pointer to the buzzer structure.
     * @param pattern Pointer to the pattern structure.
     */
    void Buzzer_StartPattern(Fuz_Buzzer_t *, Fuz_BuzzerPattern_t *);

    /**
     * Update the buzzer state for pattern playback.
     * Should be called periodically.
     * @param buzzer Pointer to the buzzer structure.
     * @param currentTime Current time in milliseconds.
     */
    void Buzzer_UpdatePattern(Fuz_Buzzer_t *, uint32_t);

#ifdef	__cplusplus
}
#endif

#endif	/* BUZZER_H */
