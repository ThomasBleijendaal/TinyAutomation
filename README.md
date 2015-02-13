TinyAutomation 0.3 beta
==================

This 0.3 beta version.

---

Small scale process automation.

Basic layout of a project
---

A typical project using TinyAutomation consists of the following layers, starting at the top:

- Visualisation
- User code
- Devices
- Typicals
- IO Drivers
- Base IO Driver
- General object
- Arduino hardware

Each layer has its own purpose and are discribed below:

**Arduino hardware**
The base of each project is an Arduino controller. It can be any version, an Uno, or a Pro Micro. What ever your project demands.

**General object**
At the core of TinyAutomation there is the general object. This object deals with the required operations during each program cycle, maintains commnucations with external systems, and handles each typical and device used in the project.

**Base IO Driver**
To provides some abstraction from the Arduino controller, a Base IO Driver is needed. This driver removes the need of the layers above to exactly know on which Arduino it runs. It maps each IO address to the exact pin of the Arduino, and gives boundries to which addresses can be used and which not. 

The first IO driver that is being registered to the General object, is the Base IO driver. Any driver can be the Base IO driver, there is no special class for it.

**IO Drivers**
Every other IO driver that is registered to the General object, is an IO driver. An IO driver is used to communicate with an external chip, for example a shift register or an IO expander. The rest of the program can access these extra IO options as if it were part of the Arduino, there is no difference in how an onboard pin is accessed compared to accessing a pin on an IO expander.

**Typicals**
Typicals are objects that behave very typical. There are four different typicals: analog in and out, and digital in and out. These four object make up an abstract representation of almost any object used: for example, a temperature sensor is an analog in while an motor is a digital out.

These objects are assigned to one or more IO addresses and convert these IO addresses into objects that represent a physical value, or a controllable entity. 

**Devices**
These objects sit on top of typicals. They allow multiplce typicals to be controlled as one object. For example, a PID loop, in which an analog input is read, compares it to the required setpoint, and controls an analog output accordingly. 
