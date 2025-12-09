#include <avr/io.h>
#include <util/delay.h>
#include "Register.h"
#include "Uart.h"
#include "Lcd.h"
#include "Adc.h"
#include "Dio.h"
#include "DC_Motor.h"
#include "Pwm.h"

#define MAX_POINT       100
#define MIN_POINT       1
unsigned char sw1;
unsigned char sw2;      

#define SPEED1      100
#define SPEED2      150
#define SPEED3      200
#define SPEED4      255

unsigned int set_value = 25;
unsigned short adc_value = 0;
char str[10];

int main(void)
{
    // Initialize pin D2 (PD2) as input button with no pull-up resistor
    Dio_SetPinDirection(DDR_D, PD2, DIO_DIR_INPUT);
    Dio_ResetRegisterBit(PORT_D, PD2);  // Disable pull-up resistor on PD2

    // Initialize pin D3 (PD3) as input button with no pull-up resistor
    Dio_SetPinDirection(DDR_D, PD3, DIO_DIR_INPUT);
    Dio_ResetRegisterBit(PORT_D, PD3);  // Disable pull-up resistor on PD3


    // Initialize pin BP2 and PB4 as outputs for IN1 and IN2
    Dio_SetPinDirection(DDR_B, PB2, DIO_DIR_OUTPUT);    // Set PB2 as output
    Dio_SetPinDirection(DDR_B, PB4, DIO_DIR_OUTPUT);    // Set PB4 as output
    Dio_SetPinDirection(DDR_B, PB3, DIO_DIR_OUTPUT);    // ENA on D11 (OC2A)


    // Set Motor Forward direction
    Dio_SetRegisterBit(PORT_B, PB2);    // Set PB2 High
    Dio_ResetRegisterBit(PORT_B, PB4);  // Set PB4 low

    // Initialize UART
    Uart_Init();
    Uart_SendString("Program Starts..!\n", 18);

    // Initialize ADC 
    Adc_Init();

    // Initialize and clear LCD
    LCD_Init();
    LCD_Clear();

    // display messgaes on LCD
    LCD_String_xy(0,  0, "S Temp:");
    LCD_String_xy(0, 13, "F: ");
    LCD_String_xy(1,  0, "R Temp: ");
    LCD_String_xy(1, 12, "C");

    // Initialize PWM channels on pin D11
    Pwm_InitChannel(PWM4_CH, PWM_MODE_FAST);
    Pwm_StartChannel(PWM4_CH);             //  on pin D11
    
    while(1)
    {
        // Read the current state of the switch on PD2 and PD3
        sw1 = Dio_GetPinState(PIN_D, PD3);
        sw2 = Dio_GetPinState(PIN_D, PD2);
        
        // Check if SW1 is pressed
        if(sw1 == 0x01 ){
            set_value = set_value + 1;          // value increment by 1
            if(set_value > MAX_POINT)
                set_value = MAX_POINT;          // keep below max value
            _delay_ms(100);                     // 100msec delay for debounce
        }

        // Check if SW2 is pressed
        if(sw2 == 0x01 ){
            set_value = set_value - 1;          // value decrement by 1
            if(set_value < MIN_POINT)
                set_value = MIN_POINT;          // keep above minumim value
            _delay_ms(100);
        }

        // Read Temperature Sensor LM35
        adc_value = Adc_ReadChannel(0);
        float voltage = adc_value * (5.0 / 1023.0);  // Convert ADC to voltage (in volts)
        int tempC = (int)(voltage * 100.0);          // LM35 scale factor (10 mV per °C)

        sprintf(str, "%3d", set_value);             // Print Set value by user on LCD
        LCD_String_xy(0, 8, str);
        
        sprintf(str, "%3d", tempC);                 // Print Temperature on LCD
        LCD_String_xy(1, 8, str);

        sprintf(str, "%03d %03d\n", set_value, tempC); 
        Uart_SendString(str, 8);


        if(tempC > set_value){

            Dio_SetRegisterBit(PORT_B, PB2);    // Set PB2 High
            Dio_ResetRegisterBit(PORT_B, PB4);  // Set PB4 low

            if(tempC <= (set_value+5) ){
                Pwm_SetDutyCycle(PWM4_CH, SPEED1);
                LCD_String_xy(0, 15, "1");
            }

            else if (tempC > (set_value+5) && tempC <= (set_value+10) ){
                Pwm_SetDutyCycle(PWM4_CH, SPEED2);
                LCD_String_xy(0, 15, "2");
            }

            else if (tempC > (set_value+10) && tempC <= (set_value+15) ){
                Pwm_SetDutyCycle(PWM4_CH, SPEED3);
                LCD_String_xy(0, 15, "3");
            }

            else if(tempC > (set_value+15)){
                Pwm_SetDutyCycle(PWM4_CH, SPEED4);
                LCD_String_xy(0, 15, "4");
            }
        }
        else{

            Dio_ResetRegisterBit(PORT_B, PB2);    // Set PB2 low
            Dio_SetRegisterBit(PORT_B, PB4);        // Set PB4 High

            if(tempC >= (set_value-5)){
                Pwm_SetDutyCycle(PWM4_CH, SPEED1);
                LCD_String_xy(0, 15, "1");
            }

            else if (tempC >= (set_value-10) && tempC < (set_value-5)){
                Pwm_SetDutyCycle(PWM4_CH, SPEED2);
                LCD_String_xy(0, 15, "2");
            }

            else if (tempC >= (set_value-15) && tempC < (set_value-10)){
                Pwm_SetDutyCycle(PWM4_CH, SPEED3);
                LCD_String_xy(0, 15, "3");
            }

            else if(tempC < (set_value-15)){
                Pwm_SetDutyCycle(PWM4_CH, SPEED4);
                LCD_String_xy(0, 15, "4");
            }

        }

        _delay_ms(100);
    }
    return 0;
}

