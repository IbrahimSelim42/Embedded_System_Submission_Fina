
#ifndef __PWM__
#define __PWM__

#define TCCR0A_REG                              0x44
#define TCCR0B_REG                              0x45
#define TCNT0_REG                               0x46
#define OCR0A_REG                               0x47
#define OCR0B_REG                               0x48

#define TCCR1A_REG                              0x80
#define TCCR1B_REG                              0x81
#define TCCR1C_REG                              0x82
#define TCNT1_REG                               0x84
#define OCR1A_REG                               0x88
#define OCR1B_REG                               0x8A

#define TCCR2A_REG                              0xB0
#define TCCR2B_REG                              0xB1
#define TCNT2_REG                               0xB2
#define OCR2A_REG                               0xB3
#define OCR2B_REG                               0xB4

#define PWM0_CH         0
#define PWM1_CH         1
#define PWM2_CH         2
#define PWM3_CH         3
#define PWM4_CH         4
#define PWM5_CH         5

typedef enum {
    PWM_MODE_FAST = 0,
    PWM_MODE_PHASE_CORRECT
} tenuPwmMode;

void Pwm_InitChannel(unsigned char Channel, tenuPwmMode Mode);
void Pwm_StartChannel(unsigned char Channel);
void Pwm_StopChannel(unsigned char Channel);
void Pwm_Init();
void Pwm_SetDutyCycle(unsigned char Channel, unsigned char DutyCycle);

#endif
