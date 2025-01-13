#Piroi-Madalin-George - Interactive Katana

Introduction

An interactive katana project that blends modern technology with traditional design, powered by an Arduino Nano, a WS2812B LED strip, and a DY-SV5W MP3 player module. The katana displays dynamic lighting effects activated by motion, using an MPU-6050 accelerometer and gyroscope sensor for precise movement detection. It features a button to enhance interactivity and a speaker system to play sound effects. Powered by a 9V battery or an external power bank via USB cable, the katana is coated with epoxy resin for durability.

General Description

The interactive katana uses a combination of hardware components to achieve a responsive system:

The Arduino Nano acts as the brain of the system, coordinating all components.

A WS2812B LED strip provides dynamic and customizable lighting effects.

The MPU-6050 accelerometer/gyroscope detects tilt and sharp movements (e.g., slashes) to trigger LED patterns.

The DY-SV5W MP3 player module plays sound effects synchronized with motion or lighting modes.

A push button allows switching between modes, such as static lighting, tilt-based effects, or special lighting patterns.

The system is powered by a 9V battery for portability or a USB-connected power bank for extended use.

Hardware Design

Components and Their Roles

Component

Role

Arduino Nano

Main microcontroller, processes input and controls the LED strip and MP3 player.

WS2812B LED Strip

Displays lighting effects based on input and movement.

MPU-6050

Detects tilt and sudden movement (slashing motions).

DY-SV5W MP3 Module

Plays sound effects triggered by motion or button interactions.

Push Button

User input for switching between modes.

9V Battery

Powers the entire system via Arduino Nano.

Power Bank

Provides alternative power via USB connection.

Connections

1. Power Connections

9V Battery:

Positive terminal → VIN pin on Arduino Nano.

Negative terminal → GND on Arduino Nano.

USB Power Bank:

Connected via the Arduino Nano's USB port for alternative power.

WS2812B LED Strip:

VCC → 5V pin on Arduino Nano.

GND → GND pin on Arduino Nano.

DY-SV5W MP3 Module:

VCC → 5V pin on Arduino Nano.

GND → GND pin on Arduino Nano.

2. LED Control

WS2812B LED Strip:

DI (Data Input) → D6 pin on Arduino Nano.

3. MPU-6050 (Motion Sensor)

VCC → 3.3V pin on Arduino Nano.

GND → GND on Arduino Nano.

SDA → A4 pin on Arduino Nano (I2C data line).

SCL → A5 pin on Arduino Nano (I2C clock line).

4. DY-SV5W MP3 Module

RX → D3 pin on Arduino Nano.

TX → D4 pin on Arduino Nano.

Speaker connected to the module’s speaker output terminals.

5. Push Button

One terminal → D10 pin on Arduino Nano.

Other terminal → GND.

Bill of Materials (BOM)

Arduino Nano

Quantity: 1

WS2812B LED Strip

Quantity: 1 (30 LEDs)

MPU-6050 Sensor

Quantity: 1

DY-SV5W MP3 Player Module

Quantity: 1

Push Button

Quantity: 1

9V Battery + Connector

Quantity: 1

Power Bank + USB Cable

Quantity: 1

Speaker

Quantity: 1

Block Diagram

                  +-----------------+        +-------------------+
                  |  9V Battery     |        |  USB Power Bank    |
                  |  (Power Source) |        |  (Alt. Power)      |
                  +-----------------+        +-------------------+
                            |                         |
                            +-------------------------+
                                      |
                           +----------v----------+
                           |    Arduino Nano     |
                           | (Microcontroller)   |
                           +----------+----------+
                                      |
           +--------------------------+--------------------------+
           |                                                     |
   +-------v--------+                                   +--------v-------+
   |  MPU-6050      |                                   | DY-SV5W MP3    |
   | (Gyro/Accel)   |                                   |   Module       |
   +----------------+                                   +--------+-------+
                                                                |
                                                        +-------v-------+
                                                        |   Speaker     |
                                                        | (Sound Output)|
                                                        +---------------+


Software Design

Modes of Operation:

Static Mode: Displays a single color on the LED strip.

Motion Mode: Uses data from the MPU-6050 to detect slashing movements and dynamically change the LED patterns.

Sound Effects: Plays preloaded sound effects triggered by specific motion patterns or button presses.

Special Effects: Combines lighting and sound effects for unique sequences.

Code Structure:

Initialization: Sets up I2C communication, LED control, MP3 module, and button input.

Main Loop: Continuously checks the button state, sensor data, and updates the LED and sound effects accordingly.

Functions:

readSensorData(): Reads and processes data from MPU-6050.

updateLEDs(): Updates the LED strip based on the detected motion or mode.

playSound(): Sends commands to the DY-SV5W to play specific sound effects.

handleButtonPress(): Manages mode switching based on button input.

Libraries Used:

Adafruit_NeoPixel: Controls the WS2812B LED strip.

Adafruit_MPU6050: Interfaces with the MPU-6050 sensor.

SoftwareSerial: Communicates with the DY-SV5W MP3 module.

Results Achieved

Motion Detection:

Successfully detects tilt and slashing motions using the MPU-6050.

Generates responsive lighting effects based on motion intensity.

Dynamic Lighting and Sound Effects:

Smooth transitions and bright colors displayed on the LED strip.

Sound effects synchronized with motion patterns for an immersive experience.

User Interaction:

Button input reliably switches between modes.

The system is responsive to quick mode and sound changes.

Power Efficiency:

The 9V battery provides sufficient power for portability.

USB power bank enables extended operation for longer sessions.

Conclusions

The Interactive Katana project successfully integrates hardware and software to create a responsive and immersive system. The addition of the DY-SV5W MP3 module enhances the project with synchronized sound effects. The dual power supply option (9V battery and USB power bank) ensures flexibility and extended usability. Future improvements could include:

Enhanced motion algorithms for more precise detection.

Additional lighting and sound effects.

Integration of advanced features like Bluetooth for remote control or configuration.

GitHub Repository

Link to the project: Interactive Katana GitHub Repository

Journal

Phase 1: Component selection and initial testing.

Phase 2: Hardware assembly and connectivity validation.

Phase 3: Implementation of motion detection, LED control, and sound integration.

Phase 4: Final integration and system testing.

Bibliography/Resources

Arduino Nano Documentation

Adafruit NeoPixel Library

MPU-6050 Datasheet

DY-SV5W MP3 Module Documentation

