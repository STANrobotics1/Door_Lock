This folder contains simple tests used to debug running the piezo sensor pins through DIGITALREAD instead of ANALOGREAD. 
AnalogRead() on an arduino takes 100 microseconds to complete, which is very poor resolution for the average door and 
the speed of sound in wood. This folder shows some random code we used to take a hardware usually built for analog data, 
and switching it to digital, with the help of an LM339 comparator.

Note:
DigitalTest.ino uses DigitalReadFast, implemented from the following library:
https://code.google.com/p/digitalwritefast/downloads/list

Thanks to Paul Stoffregen for developing this library!


