# WifiDustSensor
Project working with Sharp GP2Y1014AU0F and an Arduino MKR WiFi 1000
-------------
Overview:
    In the wake of the major fires in California and a record breaking fire season across the west coast, it was hard to know exactly how poor the air quality was inside my home. I live in a typical bay area apartment with old windows and no central heating or air. My partner and I made an emergency purchase of an air filter to try and keep ourselves safe, but I oftened wondered how long it should be on for, and when was it bad enough to warrant its use?
    After brief research I saw I could use my newly acquired skills in IoT programming to build an inexpensive indoor air filter! This is a record of what I learned along the way.
    
   Initially I worked on a premade module from Waveshare, but ran into trouble when I tried adapting it from it's intended 5V board use to the 3.3V MKR 1000 board. 
    
   The dust sensor works by sensing the diffraction of an IR LED due to dust and smoke. The sensor put out a higher voltage reading relative to the amount of reflected IR light. It is recorded to pick up particles up to 2.5 microns in size (detecting PM2.5 concentration levels). To read consitent and calibrated measurements, the datasheet calls for a LED pulse (which is driven *LOW*) of 320 microseconds, and the sense voltage to be read at 280 microseconds within that pulse. The pulses should occur on a 10 millisecond cycle. While the sensor is powered by a 5V source the output never exceed 3.3 V, which makes it save to use for a board like the MKR1000.
    
   I use the MKR1000 to drive the pulse and read the V_sensem then process it via a buffer function in order to smooth out the readings over a few seconds time. The density reading is calculated through a conversion function which can be found on the Adafruit website, and uses common ADC conversion (system_voltage/ADC_resolution) and a density to voltage ratio specified in the datasheet of 0.18 volts/mg_dust.
    
    
    
-------------
Materials:
1. Sharp Dust Sensor, 220 uF capacitor, 150 Ohm Resister: https://www.adafruit.com/product/4649
2. Arduino MKR 1000: https://store.arduino.cc/usa/arduino-mkr1000
3. Powerbank: https://www.amazon.com/gp/product/B07MKM4QSJ/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1
4. Soldering station / Solder / PCB prototyping board / Wire
Total cost (sans solder equipment): $50

-------------
Useful Reference Material:
 - Learn about programming a telegram bot: https://create.arduino.cc/projecthub/Arduino_Genuino/telegram-bot-library-ced4d4
 - Sharp GP2Y10104AU0F Data sheet: https://www.mouser.com/datasheet/2/365/GP2Y1014AU0F_SPEC-1288381.pdf
 - Building the circuit: https://www.adafruit.com/product/4649
