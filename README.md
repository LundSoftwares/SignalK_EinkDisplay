## SignalK E-ink Display
**Custom project for sending Signal data to ESP32 based Waveshare E-ink Display from MQTT**

The idea was to create a custom hardware setup that easily could show whatever data that doesn't need to be updated in realtime, like battery voltage, battery SOC, temperatures and similar.
I ended up with en ESP32 based project, connected to a Waveshare 4,2" E-Ink Display. All data is picked up by SignalK (can ofcourse be any source of data) handled in NodeRed and sent via MQTT. All necessary data goes from NodeRed, even column width, row height, refresh rate and a possibility to clear the screen. Two hardware switces was also installed, one for switching between Page 1 and Page 2, the second one puts the ESP32 in DeepSleep to save power.
Pins used for both Display and switches is found in e-paper_esp32_mqtt.ino file.

![image](https://github.com/LundSoftwares/SignalK_EinkDisplay/assets/23386303/101895a5-18b2-4874-a87b-b9e1cdfe5509)

# Hardware

**ESP32 MH-ET Live (will most likely work with most ESP32 based boards):**

https://www.aliexpress.com/item/1005002715554339.html


**Waveshare 4,2" 400x300 E-Ink display module, SPI:**

https://www.waveshare.com/4.2inch-e-paper-module.htm

![image](https://github.com/LundSoftwares/SignalK_EinkDisplay/assets/23386303/ee49d238-509b-420a-8c92-e8a4347c9b00)
