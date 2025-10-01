# Weather Station v1.0 
![20250127_181248](https://github.com/user-attachments/assets/9ffabefa-ed49-41a1-971d-715ebc8c37f8)

 It is part of a dual-axis solar tracking system, and this weather station performs the following functions:

1. Generates accurate time.
2. Calculates the predicted solar elevation and azimuth based on the date, time, and location coordinates.
3. Adjusts the calculated solar elevation and azimuth angles considering local weather conditions.
4. Sends the calculated data directly to solar tracking towers, which serve as the power plants.

## Wiring Diagram: 
![wiring](https://github.com/user-attachments/assets/328f570f-d7c0-4e19-9dfa-d3c50d33e01a)

This program module is responsible for collecting data from the following sources:

1. The SUN clock: Data collected includes the year, month, day, hour, minute, second, 0.1 second, calculated azimuth and elevation at sea level (0 meters), and the calculated daily maximum solar elevation.
2. BMP280 and SHT21 sensors: Temperature, atmospheric pressure, and relative humidity.
3. Wind data: Wind speed (m/s) and direction (total of 8 directions).
4. Ambient light level: Data obtained from a phototransistor measuring average light intensity.
Using the collected data, the solar elevation angle is adjusted to account for local meteorological conditions, primarily affecting atmospheric refraction. This means the largest correction is applied when the sun is rising, while the smallest correction is applied when the solar elevation angle reaches 90 degrees. The correction range varies from 0.50 to 0.00 degrees.

Additionally, this program module is responsible for displaying the collected data on the screen and allowing data modifications using a 3x4 keypad. The display is updated only when the values of the displayed parameters change. Update thresholds are as follows:

* **Angles:** 0.01 degrees
* **Time:** 1 second
* **Pressure:** 0.01 hPa
* **Temperature:** 0.1°C
* **Humidity:** 0.1%

1 - Window for setting location and time.
![20250127_184610](https://github.com/user-attachments/assets/eab7b75e-29b2-4a36-b8c6-70c311469bb5)

2 - Window for viewing time and angle parameters.
![20250127_184630](https://github.com/user-attachments/assets/aa86c6ac-1101-458f-a718-78d70673cd7b)

3 - Window for viewing location data.
![20250127_184655](https://github.com/user-attachments/assets/299cddbf-1fc3-40bf-8cd5-adf11dce9e86)

4 - Window for viewing environmental parameters.
![20250127_183805](https://github.com/user-attachments/assets/21d123b4-4c80-43f6-9c3b-a607e1c70eb7)


In all windows, the asterisk symbol * means "go back." (In the location and time setting window, if the cursor is not at the beginning, you must press and hold the asterisk symbol  to return to the previous window.)
The hash symbol # is only functional in the location and time setting window, where it signifies moving forward or saving if the hash symbol was pressed after entering the last adjustable number.
Any other button pressed and held will return to the main window, where the most relevant information is displayed.
![20250127_184554](https://github.com/user-attachments/assets/a8a43bb7-e887-4505-8b6d-3d4fdfd20c6d)





**2025-10-01 Update (FIR part for wind data are also not tested)**

The data transmission format for columns has been changed. Also added CRC8 cdma2000 for transmitted data



Before (float data type + data splitter simbol):

```
{AAA.AA|BB.BB|CC.CC|DD|E|FFF}
```
**Where:**

* **AAA.AA** – Azimuth angle

* **BB.BB** – Elevation angle

* **CC.CC** – Day Top Elevation angle

* **DD** – Wind speed

* **E** – Wind direction

* **FFF** – Light Level
  
* **|** – Data token splitter


After (unsigned int (hex) + constant data length + crc8 ):


```
{AAAABBBBCCCCDDEFFFGG}
```
**Where:**

* **AAAA** – Azimuth angle

* **BBBB** – Elevation angle

* **CCCC** – Day Top Elevation angle

* **DD** – Wind speed

* **E** – Wind direction

* **FFF** – Light Level

* **GG** – CRC-8 value


