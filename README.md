## Intelinium Techninal Test

Romain Margheriti

- [x] 1. Create a driver to get data from the GY-521 sensor (Acceleromter x, y, z)
- [x] 2. Fetches the sensor data every 200ms
- [x] 3. In the same program, make the LED blink every 500 ms
- [x] 4. Define a GATT service where the user can fetch the sensor data defined in step 3. To do so, create 3 read-only characteristics
- [x] 5. Define a GATT service where the user can stop/start the LED blink
- [x] 6. Set up a static passkey for the Bluetooth connection: 2569
- [x] 7. Protect the GATT service defined in step 5 to ensure that only a paired device can read the GATT characteristics
- [x] 8. Define a digital interrupt on one of your digital GPIO and connect a button on this GPIO. Each time the user presses the button, change the LED blinking period to 500ms, 1s, 2s and back to 500ms.

## Advanced steps

- [ ] 9. Set up the motion interrupt of the GY-521
- [ ] 10. Add a notify only characteristic in the GATT service defined in step 5. This characteristic shall notify the device connected by Bluetooth that the GY-521 is moving
- [ ] 11. Each time an interrupt is fired by the GY-521, notify the device connected by Bluetooth
