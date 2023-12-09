# ESP32 RFID Firebase Integration

This project demonstrates how to use an ESP32 microcontroller with an RFID sensor and Firebase for seamless data communication.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project utilizes an ESP32 microcontroller to interface with an RFID sensor, allowing the system to read RFID tags. The collected data is then sent to Firebase for storage and retrieval. The project is designed for applications that require RFID-based authentication and cloud-based data storage.

## Features

- RFID tag reading using ESP32
- Firebase integration for data storage
- Simple and extensible codebase

## Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 development board
- RFID sensor compatible with ESP32
- Firebase account and project

## Setup

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/esp32-rfid-firebase.git
    ```

2. Open the Arduino IDE and install the ESP32 board support. Refer to the [official ESP32 Arduino core installation guide](https://github.com/espressif/arduino-esp32#installation-instructions) for instructions.

3. Install the required libraries using the Arduino Library Manager:

    - RFID Library
    - Firebase Arduino Library

4. Configure the project:

    - Open `config.h` and enter your WiFi credentials and Firebase project details.

5. Connect the RFID sensor to the ESP32.

6. Upload the code to your ESP32 board.

## Usage

1. Power up the ESP32 with the RFID sensor connected.

2. Open the Arduino IDE Serial Monitor to view RFID tag data and Firebase communication logs.

3. Scan RFID tags in the vicinity of the RFID sensor.

4. Check your Firebase project's database for the stored RFID tag data.

## Contributing

Contributions are welcome! Feel free to open issues, submit pull requests, or provide feedback.

## License

This project is licensed under the [MIT License](LICENSE).
