# A-QT-gauge-speedometer-app-controlled-by-a-gaming-steering-wheel
My interest in the automotive industry led me to work on an exciting project entitled "A Qt gauge-speedometer app controlled by a gaming steering wheel."

I have chosen this project to simulate the real-world vehicle speedometer on an embedded Linux display.

The gaming steering wheel is a non-documented USB HID device recognized as a joystick type. So the first problem was how to get data out of it.
This was done by reading bytes from the Linux USB device file corresponding to the connected steering wheel.
However, the bytes looked random at first.
Thanks to the "Device Class Definition
for the "Human Interface Devices (HID)" specification, I have managed to get coherent input data from the bytes.

The project is a multithreaded Qt/C++ application. On the main thread, a basic GUI runs, waiting for incoming data from the second thread.
The second thread listens for any input events from the steering wheel.

The next step is to run the application on an embedded Linux platform. I have chosen the Raspberry Pi 3 for this project. Since the microprocessor of the Raspberry Pi is of ARM architecture, I had to cross-compile my application.

See the demo video in my LinkedIn profile.
 [A Qt gauge-speedometer app controlled by a gaming steering wheel
](https://www.linkedin.com/feed/update/urn:li:activity:7003080279795884032/)
