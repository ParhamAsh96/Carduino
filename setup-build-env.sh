#!/bin/bash

# Update apt
apt-get update
cd ~


# Install arduino-cli
apt-get install curl -y
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh   # Download and execute Arduino CLI install script from official GitHub
export PATH=$PATH:/root/bin
arduino-cli -version

# Add Seeed Studio boards to Arduino CLI (creates a config file)
echo "board_manager:
  additional_urls:
    - https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json" > .arduino-cli.yaml

arduino-cli core update-index --config-file .arduino-cli.yaml
arduino-cli core install Seeeduino:samd --config-file .arduino-cli.yaml

arduino-cli lib install "Grove Ultrasonic Ranger@1.0.1"

cd - # Return to previous working directory

