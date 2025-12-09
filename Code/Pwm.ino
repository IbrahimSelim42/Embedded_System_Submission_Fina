#include "Dio.h"
#include "Pwm.h"

#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif


unsigned char PwmChannelRegisters [3][6] = {
  {TCCR0A_REG, TCCR0B_REG,  0x00,           TCNT0_REG, OCR0A_REG, OCR0B_REG},
  {TCCR1A_REG, TCCR1B_REG,  TCCR1C_REG,     TCNT1_REG, OCR1A_REG, OCR1B_REG},
  {TCCR2A_REG, TCCR2B_REG,  0x00,           TCNT2_REG, OCR2A_REG, OCR2B_REG},
};

void Pwm_InitChannel(unsigned char Channel, tenuPwmMode Mode){
    unsigned char TimerIndex = Channel/2;
    if (Mode == PWM_MODE_FAST){
      Dio_SetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 0); //FAST MODE
      Dio_SetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 1); //FAST MODE
    }
    Dio_SetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][1], 0); //No-Prescalar
}

void Pwm_StartChannel(unsigned char Channel){
  unsigned char TimerIndex = Channel/2;
  unsigned char PwmIndex = Channel%2;
  if (PwmIndex == 0 ){
    Dio_ResetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 6);    //COMxA0
    Dio_SetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 7);      //COMxA1
  } else{
    Dio_ResetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 4);    //COMxB0
    Dio_SetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 5);      //COMxB1
  }
}

void Pwm_StopChannel(unsigned char Channel){
  unsigned char TimerIndex = Channel/2;
  unsigned char PwmIndex = Channel%2;

  if (PwmIndex == 0 ){
    Dio_ResetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 6);    //COMxA0
    Dio_ResetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 7);      //COMxA1
  } else{
    Dio_ResetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 4);    //COMxB0
    Dio_ResetRegisterBit((volatile unsigned char *)PwmChannelRegisters[TimerIndex][0], 5);      //COMxB1
  }
}


void Pwm_Init(){
  Pwm_InitChannel(PWM1_CH, PWM_MODE_FAST);
  Pwm_StartChannel(PWM1_CH);
  Pwm_InitChannel(PWM5_CH, PWM_MODE_FAST);
  Pwm_StartChannel(PWM5_CH);
}

void Pwm_SetDutyCycle(unsigned char Channel, unsigned char DutyCycle){
  unsigned char TimerIndex = Channel/2;
  unsigned char PwmIndex = Channel%2;
  *(volatile unsigned char *)PwmChannelRegisters[TimerIndex][4+PwmIndex] = DutyCycle;
}