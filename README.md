# espix

The core library of Espix.

## About the Project

I always try to build a tiny system with user friendly UI from sketch, even when I was a 13 years old boy. In 1997, I implemented a MS-Editor-like console application by using Quick Basic.

### espix-core

Inspired by iOS and React.js, `espix-core` is a simple but powerful SDK for the IoT developers to make fast prototypes. It includes features like:

- [Application life cycle management](./src/espix-core/applications/Application.h)

- [A screen display](./src/espix-core/devices/Screen.h), OLED by default

- [A keyboard](./src/espix-core/devices/Keyboard.h) and a [jog dial](./src/espix-core/devices/JogDial.h) as input devices

- [WiFi Network](./src/espix-core/networking/WiFiNetwork.h)

- [Automatically synchronized NTP client](./src/espix-core/timing/TimeClient.h)

- [Drawing APIs](./src/espix-core/drawing/CanvasContext.h) similar to WebGL

- [Animations](./src/espix-core/animations/AnimationLoop.h) and [transitions](./src/espix-core/transitions/Transition.h)

- [Views](./src/espix-core/views/View.h), a mixed concept of View from iOS and Component in React.js

### espix-design

The `espix-design` library includes many [useful UI elements](./src/espix-design/views).

## How to install

In `platform.ini` add `espix-core` into your `lib-deps`.

```ini
lib_deps = espix-core
```

Or install via Platform CLI.

```sh
pio lib install espix-core
```
