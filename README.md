# **Piroi-Madalin-George - Interactive Katana**

## **Introduction**

An interactive katana project that blends modern technology with traditional design, powered by an **Arduino Nano**, a **WS2812B LED strip**, and a **DY-SV5W MP3 player module**. The katana displays dynamic lighting effects activated by motion, using an **MPU-6050 accelerometer and gyroscope sensor** for precise movement detection. It features a button to enhance interactivity and a speaker system to play sound effects. Powered by a **9V battery** or an external power bank via USB cable, the katana is coated with epoxy resin for durability.

---

## **General Description**

The interactive katana uses a combination of hardware components to achieve a responsive system:

- The **Arduino Nano** acts as the brain of the system, coordinating all components.
- A **WS2812B LED strip** provides dynamic and customizable lighting effects.
- The **MPU-6050 accelerometer/gyroscope** detects tilt and sharp movements (e.g., slashes) to trigger LED patterns.
- The **DY-SV5W MP3 player module** plays sound effects synchronized with motion or lighting modes.
- A **push button** allows switching between modes, such as static lighting, tilt-based effects, or special lighting patterns.
- A **switch button** allows turning on and off the powers for the 9 V battery
- The system is powered by a **9V battery** for portability or a USB-connected power bank for extended use.

---

## **Hardware Design**

### **Components and Their Roles**

| **Component**          | **Role**                                                                         |
| ---------------------- | -------------------------------------------------------------------------------- |
| **Arduino Nano**       | Main microcontroller, processes input and controls the LED strip and MP3 player. |
| **WS2812B LED Strip**  | Displays lighting effects based on input and movement.                           |
| **MPU-6050**           | Detects tilt and sudden movement (slashing motions).                             |
| **DY-SV5W MP3 Module** | Plays sound effects triggered by motion or button interactions.                  |
| **Push Button**        | User input for switching between modes.                                          |
| **9V Battery**         | Powers the entire system via Arduino Nano.                                       |
| **Power Bank**         | Provides alternative power via USB connection.                                   |
| **Switch Button**      | Used to control the 9V battery power supply to the Arduino Nano.                 |
|**9V Battery connector**| Connect teh 9v batteri and the arduino                                           |

---

### **Connections**

#### **1. Power Connections**


- **9V Battery**:
  - Connect to → 9V Battery connector

- **9V Battery connector**:
  - Positive terminal → One terminal **Switch Button**  
  - Negative terminal → **GND** on Arduino Nano.

- **USB Power Bank**:
  - Connected via the Arduino Nano's USB port for alternative power.

- **WS2812B LED Strip**:
  - **VCC** → **5V** pin on Arduino Nano.
  - **GND** → **GND** pin on Arduino Nano.

- **DY-SV5W MP3 Module**:
  - **VCC** → **5V** pin on Arduino Nano.
  - **GND** → **GND** pin on Arduino Nano.

#### **2. LED Control**

- **WS2812B LED Strip**:
  - **DI (Data Input)** → **D8** pin on Arduino Nano.

#### **3. MPU-6050 (Motion Sensor)**

- **VCC** → **3.3V** pin on Arduino Nano.
- **GND** → **GND** on Arduino Nano.
- **SDA** → **A4** pin on Arduino Nano (I2C data line).
- **SCL** → **A5** pin on Arduino Nano (I2C clock line).

#### **4. DY-SV5W MP3 Module**

- **RX** → **D3** pin on Arduino Nano.
- **TX** → **D4** pin on Arduino Nano.
- **Speaker** connected to the module’s speaker output terminals.

#### **5. Push Button**

- One terminal → **D10** pin on Arduino Nano.
- Other terminal → **GND**.

#### **6. Swicth Button**
- One terminal → **VIN** pin on Arduino Nano.
---

### **Bill of Materials (BOM)**

1. **Arduino Nano**

   - **Quantity**: 1

2. **WS2812B LED Strip**

   - **Quantity**: 1 

3. **MPU-6050 Sensor**

   - **Quantity**: 1

4. **DY-SV5W MP3 Player Module**

   - **Quantity**: 1

5. **Push Button**

   - **Quantity**: 1

6. **9V Battery + Connector**

   - **Quantity**: 1

7. **Power Bank + USB Cable**

   - **Quantity**: 1

8. **Speaker**

   - **Quantity**: 1

5. **Switch Button**

   - **Quantity**: 1
---

### **Block Diagram**

```
                  +-----------------+        +-------------------+
                  |  9V Battery     |        |  USB Power Bank    |
                  |  (Power Source) |        |  (Alt. Power)      |
                  +-----------------+        +-------------------+
                            |                         |
                     +------v------+                 |
                     | Switch Button|                 |
                     +------+-------+                 |
                            |                         |
                            +-------------------------+
                                      |
                           +----------v----------+
                           |    Arduino Nano     |
                           | (Microcontroller)   |
                           +----------+----------+
                                      |
           +--------------------------+--------------------------+
           |                          |                          |
   +-------v--------+                 |                 +--------v-------+
   |  MPU-6050      |                 |                 | DY-SV5W MP3    |
   | (Gyro/Accel)   |                 |                 |   Module       |
   +----------------+                 |                 +--------+-------+
                                      |                          |
                             +--------v---------+        +-------v-------+
                             |   Push Button    |        |   Speaker     |
                             | (Mode Control)   |        | (Sound Output)|
                             +------------------+        +---------------+

```

---

## **Software Design**

1. **Modes of Operation**:

   - **Static Mode**: Displays a single color on the LED strip.
   - **Motion Mode**: Uses data from the MPU-6050 to detect slashing movements and dynamically change the LED patterns.
   - **Sound Effects**: Plays preloaded sound effects triggered by specific motion patterns or button presses.
   - **Special Effects**: Combines lighting and sound effects for unique sequences.

2. **Code Structure**:

   - **Initialization**: Sets up I2C communication, LED control, MP3 module, and button input.
   - **Main Loop**: Continuously checks the button state, sensor data, and updates the LED and sound effects accordingly.
   - **Functions**:
     - **`readSensorData()`**: Reads and processes data from MPU-6050.
     - **`updateLEDs()`**: Updates the LED strip based on the detected motion or mode.
     - **`playSound()`**: Sends commands to the DY-SV5W to play specific sound effects.
     - **`handleButtonPress()`**: Manages mode switching based on button input.

3. **Libraries Used**:

   - **Adafruit\_NeoPixel**: Controls the WS2812B LED strip.
   - **Adafruit\_MPU6050**: Interfaces with the MPU-6050 sensor.
   - **SoftwareSerial**: Communicates with the DY-SV5W MP3 module.

---

## **Results Achieved**

1. **Motion Detection**:

   - Successfully detects tilt and slashing motions using the MPU-6050.
   - Generates responsive lighting effects based on motion intensity.

2. **Dynamic Lighting and Sound Effects**:

   - Smooth transitions and bright colors displayed on the LED strip.
   - Sound effects synchronized with motion patterns for an immersive experience.

3. **User Interaction**:

   - Button input reliably switches between modes.
   - The system is responsive to quick mode and sound changes.

4. **Power Efficiency**:

   - The 9V battery provides sufficient power for portability.
   - USB power bank enables extended operation for longer sessions.

---

## **Conclusions**

The Interactive Katana project successfully integrates hardware and software to create a responsive and immersive system. The addition of the DY-SV5W MP3 module enhances the project with synchronized sound effects. The dual power supply option (9V battery and USB power bank) ensures flexibility and extended usability. Future improvements could include:

- Enhanced motion algorithms for more precise detection.
- Additional lighting and sound effects.
- Integration of advanced features like Bluetooth for remote control or configuration.

---

## **Media**

![P_20250112_210952](https://github.com/user-attachments/assets/454d3480-31dc-4f79-a922-a1d22cc5393a)

![P_20250113_212746](https://github.com/user-attachments/assets/80737a1e-3b6e-4a95-8a8d-a1af8922ea95)

![P_20250113_212646](https://github.com/user-attachments/assets/f3b3021d-bd93-4ff0-9566-167657e64a9c)

https://github.com/user-attachments/assets/d051d717-21d6-4d6c-b9b2-af11a9cf88ec

https://github.com/user-attachments/assets/7cfee3e6-ca1d-4a89-aff6-e57aaff1e89a



---

## **Electric  schematics**



---

## **Journal**

1. **Phase 1**: Component selection and initial testing.
2. **Phase 2**: Hardware assembly and connectivity validation.
3. **Phase 3**: Implementation of motion detection, LED control, and sound integration.
4. **Phase 4**: Final integration and system testing.

---

## **Bibliography/Resources**

- [Arduino Nano Documentation](https://www.arduino.cc/en/Guide/ArduinoNano)
- [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
- [MPU-6050 Datasheet](https://cdn-reichelt.de/documents/datenblatt/A300/ME024.pdf)
- [DY-SV5W MP3 Module Documentation](https://grobotronics.com/images/companies/1/datasheets/DY-SV5W%20Voice%20Playback%20ModuleDatasheet.pdf?1559812879320=&srsltid=AfmBOorhiEmqe2ar5Fkf1KsBC55Jhyxj1rFRRIvpkuhsyZrCOwvQKPrH)


## **Strores**

- [ConexElectrionic](https://www.conexelectronic.ro/)
- [Emag](https://www.emag.ro/)
- [Sigmanortec](https://www.sigmanortec.ro/)
