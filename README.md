# esp-idf-ds3231
DS3231 RTC Driver for esp-idf

I forked from [here](https://github.com/UncleRus/esp-idf-lib/tree/master/components/ds3231).   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-ds3231
cd esp-idf-ds3231
idf.py menuconfig
idf.py flash
```

# Wireing  

|DS3231||ESP32|
|:-:|:-:|:-:|
|SCL|--|GPIO15(*1)|
|SDA|--|GPIO16(*1)|
|GND|--|GND|
|VCC|--|3.3V|

(*1) You can change using menuconfig.   

# Set Clock Mode   

This mode set RTC initial value using NTP time Server.   
You have to set these config value using menuconfig.   

![config-ds3231-1](https://user-images.githubusercontent.com/6020549/59557293-346e5300-9011-11e9-9106-6256bd5c8a7e.jpg)

![config_ds3231-2](https://user-images.githubusercontent.com/6020549/59557292-346e5300-9011-11e9-9070-fe281eed0398.jpg)

You have to set gpio & NTP Server using menuconfig.   

![config-ds3231-11](https://user-images.githubusercontent.com/6020549/59557295-4bad4080-9011-11e9-96dc-b42702929542.jpg)

![config-ds3231-12](https://user-images.githubusercontent.com/6020549/59557296-4fd95e00-9011-11e9-842c-7c81469244af.jpg)


# Get Clock Mode   

This mode take out the time from a RTC clock.   
You have to change mode using menuconfig.   

![config-ds3231-11](https://user-images.githubusercontent.com/6020549/59557295-4bad4080-9011-11e9-96dc-b42702929542.jpg)

![config-ds3231-13](https://user-images.githubusercontent.com/6020549/59557300-5ec01080-9011-11e9-9ca2-94067ab8df28.jpg)

![ds3231-13](https://user-images.githubusercontent.com/6020549/59557303-697aa580-9011-11e9-81ef-09c0b28ed5a9.jpg)


# Get the time difference of NTP and RTC   

This mode get time over NTP, and take out the time from a RTC clock.   
Calculate time difference of NTP and RTC.   
You have to change mode using menuconfig.   

![config-ds3231-11](https://user-images.githubusercontent.com/6020549/59557295-4bad4080-9011-11e9-96dc-b42702929542.jpg)

![config-ds3231-14](https://user-images.githubusercontent.com/6020549/59557304-77302b00-9011-11e9-8694-5c9fa47f6352.jpg)

![ds3231-14](https://user-images.githubusercontent.com/6020549/59557305-7f886600-9011-11e9-8b24-cf3a251e4bce.jpg)


# Time difference of 1 week later.   

![ds3231-1week](https://user-images.githubusercontent.com/6020549/59961772-2dff4000-9517-11e9-9368-2c3c085617c8.jpg)

# Time difference of 1 month later.   

![ds3231-1month](https://user-images.githubusercontent.com/6020549/61294194-3f82f180-a810-11e9-866a-5af73427cf12.jpg)


# References

https://github.com/nopnop2002/esp-idf-ds1302

https://github.com/nopnop2002/esp-idf-ds1307

https://github.com/nopnop2002/esp-idf-pcf8563
