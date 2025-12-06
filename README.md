# esp-idf-ds3231
DS3231 RTC Driver for esp-idf

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   
ESP-IDF V5.1 is required when using ESP32-C6.   

__Note for ESP-IDF V5.2.__   
A new i2c driver is now available in ESP-IDF V5.2.   
Under ESP-IDF V5.2 or later, this project uses a new i2c driver.   

# Installation
```Shell
git clone https://github.com/nopnop2002/esp-idf-ds3231
cd esp-idf-ds3231
idf.py menuconfig
idf.py flash
```

# Wireing  

|DS3231||ESP32|ESP32S2/S3/H2|ESP32Cn|
|:-:|:-:|:-:|:-:|:-:|
|SCL|--|GPIO22|GPIO02|GPIO06|
|SDA|--|GPIO21|GPIO01|GPIO05|
|GND|--|GND|GND|GND|
|VCC|--|3.3V|3.3V|3.3V|

You can change GPIO using menuconfig.   

# Set Clock Mode   

This mode set RTC initial value using NTP time Server.   
You have to set these config value using menuconfig.   

![Image](https://github.com/user-attachments/assets/cc69f8fb-bf6f-415c-b65d-3eb072efdd9c)
![Image](https://github.com/user-attachments/assets/0d1e38a2-1d8c-4e3e-b478-d4736c0b9134)

You have to set gpio & NTP Server using menuconfig.   

![Image](https://github.com/user-attachments/assets/7d1a3359-2de7-4139-b3f7-4f14e9b6b23d)
![Image](https://github.com/user-attachments/assets/376d2562-7517-4e11-a893-fd37c090f7b8)


# Get Clock Mode   

This mode take out the time from a RTC clock.   
You have to change mode using menuconfig.   

![Image](https://github.com/user-attachments/assets/7d1a3359-2de7-4139-b3f7-4f14e9b6b23d)
![Image](https://github.com/user-attachments/assets/f264591d-90fb-434d-9b1e-3c9fb8dc02ab)
![ds3231-13](https://user-images.githubusercontent.com/6020549/59557303-697aa580-9011-11e9-81ef-09c0b28ed5a9.jpg)


# Get the time difference of NTP and RTC   

This mode get time over NTP, and take out the time from a RTC clock.   
Calculate time difference of NTP and RTC.   
You have to change mode using menuconfig.   

![Image](https://github.com/user-attachments/assets/7d1a3359-2de7-4139-b3f7-4f14e9b6b23d)
![Image](https://github.com/user-attachments/assets/9c058d9e-50de-4e84-a9cd-0b62da2aa440)
![ds3231-14](https://user-images.githubusercontent.com/6020549/59557305-7f886600-9011-11e9-8b24-cf3a251e4bce.jpg)


# Time difference of 1 week later.   

![ds3231-1week](https://user-images.githubusercontent.com/6020549/59961772-2dff4000-9517-11e9-9368-2c3c085617c8.jpg)

# Time difference of 1 month later.   

![ds3231-1month](https://user-images.githubusercontent.com/6020549/61294194-3f82f180-a810-11e9-866a-5af73427cf12.jpg)


# References

https://github.com/nopnop2002/esp-idf-ds1302

https://github.com/nopnop2002/esp-idf-ds1307

https://github.com/nopnop2002/esp-idf-pcf8563
