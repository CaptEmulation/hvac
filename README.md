README
====

Zoned HVAC (Heating, Ventilation and Air Conditioning) controller using [qphidgets](https://github.com/CaptEmulation/qphidget) and [qtwebapp](https://github.com/CaptEmulation/QWebApp) intended to be used to build a web-connected HVAC controller for my personal use.

No support is offered or implied-- but don't let that stop you from taking a look!

Building
-----------
1. First install phidget21 library for the platform of your choosing
2. Clone qphidget repo: ```git clone git@github.com:CaptEmulation/qphidget.git```
3. Go into qphidget repo: ```cd qphidget```
4. Clone qtwebapp: ```git clone git@github.com:CaptEmulation/QWebApp.git```
5. Now clone this repo: ```git clone git@github.com:CaptEmulation/hvac.git```
6. Build in this order: qphidget-lib, QWebApp, hvac/hvac-service-lib

This will get you the core library files.  See hvac/hvac-service-test for unit tests and some of the usages.  The various "mock" classes are built to work with qphidget-mock which is a replacement qphidget-lib which emulates an InterfaceKit888 phidget in software.  They are a whole different beast who's usage is left as an exercise to the reader.
