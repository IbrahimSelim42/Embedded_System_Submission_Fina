#include "Dio.h"
#include "DC_Motor.h"
#if !defined(__AVR_ATmega328P__)
#include <avr/iom328p.h>
#endif

unsigned char MotorArray[2][4] = {{DDRD_REG, PORTD_REG, 2, 3},
                                {DDRD_REG, PORTD_REG, 4, 5}};

void DC_Init(){
  unsigned char LoopIterator;
  for (LoopIterator = 0 ; LoopIterator < sizeof(MotorArray)/sizeof(MotorArray[0]);LoopIterator++)
  {
    Dio_SetPinDirection((volatile unsigned char*)MotorArray[LoopIterator][0],
                        MotorArray[LoopIterator][2], DIO_DIR_OUTPUT);
    Dio_SetPinDirection((volatile unsigned char*)MotorArray[LoopIterator][0],
                        MotorArray[LoopIterator][3], DIO_DIR_OUTPUT);
  }
}

void DC_Start(unsigned char MotorID, tenuDirection Direction, unsigned char Speed){
    if (Direction == DIRECTION_CW)
    {
      Dio_SetPinState((volatile unsigned char*)MotorArray[MotorID][1], MotorArray[MotorID][2], DIO_STATE_HIGH);
      Dio_SetPinState((volatile unsigned char*)MotorArray[MotorID][1], MotorArray[MotorID][3], DIO_STATE_LOW);
    } else{
      Dio_SetPinState((volatile unsigned char*)MotorArray[MotorID][1], MotorArray[MotorID][2], DIO_STATE_LOW);
      Dio_SetPinState((volatile unsigned char*)MotorArray[MotorID][1], MotorArray[MotorID][3], DIO_STATE_HIGH);
    }
}

void DC_Stop(unsigned char MotorID){
  Dio_SetPinState((volatile unsigned char*)MotorArray[MotorID][1], MotorArray[MotorID][2], DIO_STATE_HIGH);
  Dio_SetPinState((volatile unsigned char*)MotorArray[MotorID][1], MotorArray[MotorID][3], DIO_STATE_HIGH);
}