## Embedded Systems Project Report: [Automotive Air Conditioning Control Panel] , Ibrahim Selim Abomosalam 202301024 , Mohamed Khaled Ghobashy 202101628 

## 1. Introduction
This project contains the implementation of an automotive air conditioning control panel. The project realises a complete embedded climate control system in which an ATmega based controller communicates with temperature sensing and non volatile memory devices over an I2C bus, drives a bidirectional direct current fan motor at different speeds using pulse width modulation, and presents system information on a liquid crystal display. A keypad is employed to configure the desired cabin temperature and other input parameters, while the system continuously monitors the environment, updates the display with current operating conditions, and adjusts the fan behaviour accordingly. The work is intended to demonstrate the full embedded systems engineering workflow, from requirements and architectural design through to implementation, testing, and final presentation of a functioning industrial style application.

## 2. Project Code
**GitHub Repository:**
[Submission_Repo](https://github.com/IbrahimSelim42/Embedded_System_Submission_Fina)

**Local Root Directory**
[Uart.ino](./Code/Uart.ino)
[Uart.h](./Code/Uart.h)
[Adc.ino](./Code/Adc.ino)
[Adc.h](./Code/Adc.h)
[LCD.ino](./Code/Lcd.ino)
[LCD.h](./Code/Lcd.h)
[Dio.ino](./Code/Dio.ino)
[Dio.h](./Code/Dio.h)
[Register.h](./Code/Register.h)
[Main.ino](./Code/Main.ino)
[DC_Motor.h](./Code/DC_Motor.h)
[DC_Motor.ino](./Code/DC_Motor.ino)
[PWM.h](./Code/Pwm.h)
[PWM.ino](./Code/Pwm.ino)

## 3. Bill of Materials (BOM)
**BOM**
[Bom_File](./Bom/Bill_Of_Material.csv)

**Optimized BOM**
[Optimized_Bom_File](./Bom/Optimized_Bill_Of_Material.csv)

## 4. Design
[Design_Document](./Design/Project_Design.Md)
[TinkerCad](./Design/Screenshot%202025-12-09%20025550.png)