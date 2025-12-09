| Author  | Ibrahim Selim Abomosalam , Mohamed Khaled Ghobashy |
| ------- | -------------------------------------------------- |
| ID      | 202301024 , 202101628                              |
| Status  | Approved                                           |
| Version | 1.0                                                |
| Date    | 12/08/2025                                         |

**1. Introduction**
This document presents the design of an embedded monitoring and actuation system based on the ATmega328P microcontroller. The system acquires analog measurements through the on chip ten bit analog to digital converter, converts them into digital values, and evaluates these values against configurable thresholds defined by the user. The resulting information is reported locally on a sixteen by two character liquid crystal display and remotely through a universal asynchronous receiver transmitter interface connected to a host computer, thereby enabling both direct user interaction and external data observation.

In addition to monitoring, the system incorporates a pulse width modulation subsystem that drives a direct current motor through an appropriate power stage. By varying the duty cycle of the pulse width modulation signal, the firmware can regulate the motor speed or torque in response to the measured analog quantity or to derived control variables. The design therefore combines sensing, decision making, and actuation within a single microcontroller platform and aims to provide a clear, modular, and academically rigorous description of the required hardware abstraction and firmware structure.

**2. Architectural overview**
The architecture is organised in layers that separate direct hardware access from higher level application logic. At the lowest level, the ATmega328P microcontroller operates at sixteen megahertz and is supplied from a five volt source that is compatible with the liquid crystal display, the push buttons, and the motor driver circuitry. The device provides a ten bit analog to digital converter, several timers with pulse width modulation capability, universal asynchronous receiver transmitter hardware, and general purpose input and output pins. These hardware resources are used to sample analog signals, generate pulse width modulation waveforms, communicate with a host computer, scan user inputs, and drive the display.

On top of this hardware, the firmware is decomposed into driver modules for digital input and output, analog to digital conversion, serial communication, liquid crystal display handling, pulse width modulation generation, and direct current motor control. Each driver encapsulates the relevant microcontroller registers and exposes a concise and well documented interface to the rest of the system. Above the driver layer, an application module implements the main control loop and the system state machine. This module coordinates sensor acquisition, threshold evaluation, display updates, serial logging, and adjustment of the pulse width modulation duty cycle so that the behaviour of the monitoring and motor control functions remains coherent and predictable.

**3. Functional description**
From a functional perspective, the system alternates between normal monitoring, configuration, and alarm behaviour while continuously managing the pulse width modulation output applied to the motor. During monitoring, the firmware periodically triggers analog to digital conversions, converts the raw readings into meaningful engineering units when required, and compares them with the currently active thresholds. The measured value, together with the thresholds and the present system mode, is shown on the liquid crystal display in a compact and readable format, and a corresponding textual record is transmitted through the serial link to the host computer.

Configuration mode allows the user to modify system parameters, in particular the upper and lower thresholds that define acceptable operating ranges and any application specific constants that influence the mapping between measured quantities and pulse width modulation duty cycle. The user interacts with the system via push buttons, while the display provides immediate feedback on the parameter being edited and its new value. When an alarm condition is detected, for example when the measured quantity leaves the configured range or when an internal consistency check fails, the system activates an alarm state in which the display shows a clear warning, an alarm message is sent via the serial interface, and the motor control logic moves the pulse width modulation duty cycle to a safe value, typically corresponding to zero speed, until the user acknowledges the alarm and normal conditions are restored.

**4. Implementation of the modules**
The implementation adopts a modular structure in which each source file is responsible for a specific aspect of the system and exposes its functionality through a corresponding header file. The digital input and output module configures pins as inputs or outputs and provides operations to write and read logic levels, thereby serving the needs of the display interface, the push button inputs, and any discrete control lines required by the motor driver. The analog to digital converter module configures the reference voltage, prescaler, and input channel, initiates conversions, and returns ten bit conversion results in a consistent format, either through a blocking call or through an interrupt driven mechanism, depending on the timing requirements of the application.

The universal asynchronous receiver transmitter module configures the baud rate and frame format and offers routines for sending and receiving characters and strings, which are used by the application to communicate measurement and status information to the host computer. The liquid crystal display module implements the four bit interface to the sixteen by two character display, performing the initialisation sequence and providing higher level services such as clearing the screen, positioning the cursor, and printing formatted messages. The pulse width modulation module configures a timer in an appropriate pulse width modulation mode and exposes an operation for updating the duty cycle, whereas the direct current motor module builds on this service to implement higher level functions such as enabling or disabling the motor, setting its direction when supported, and ramping the duty cycle smoothly to avoid abrupt mechanical changes.

**5. Integration and configuration**
The integration process consists of compiling and linking the individual modules into a single executable image that is programmed into the microcontroller flash memory. During initialisation at run time, the main application configures the hardware abstraction layers in a defined order, ensuring that the digital input and output pins, the analog to digital converter, the serial interface, the liquid crystal display, the pulse width modulation peripheral, and the motor driver are brought into consistent states before the control loop begins operation. The control loop then executes repeatedly, invoking the services of the various modules in a deterministic pattern that respects the desired sampling period and the timing constraints of display and communication operations.

Configuration parameters that are expected to vary between deployments, such as the serial baud rate, the analog sampling interval, the pulse width modulation frequency and resolution, and the initial threshold values, are defined as constants within header files or within a dedicated configuration module. This approach allows the same code base to be reused in different scenarios by modifying only a small number of documented definitions without changing the overall structure of the firmware. For clarity, the static files that constitute the project are summarised in the following table, which links each file name to its conceptual role in the architecture.

| File name   | Contents                                                                  |
| ----------- | ------------------------------------------------------------------------- |
| Uart.c      | Initialisation and handling of serial communication                       |
| Uart.h      | Declarations of serial communication functions                            |
| Adc.c       | Configuration of the analog to digital converter and acquisition of data  |
| Adc.h       | Declarations of analog to digital converter functions                     |
| Dio.c       | Configuration and control of digital input and output pins                |
| Dio.h       | Declarations and definitions for digital input and output                 |
| Lcd.c       | Initialisation and control of the liquid crystal display in four bit mode |
| Lcd.h       | Declarations of liquid crystal display functions                          |
| registers.h | Low level hardware register definitions and mappings                      |
| main.c      | Core application logic integrating all modules                            |
| PWM.h       | Declarations and configuration parameters for pulse width modulation      |
| PWM.ino     | Implementation of pulse width modulation routines for the target platform |
| DC_Motor.h  | Interface for direct current motor control using pulse width modulation   |
| DC_Motor.c  | Implementation of direct current motor control logic                      |
