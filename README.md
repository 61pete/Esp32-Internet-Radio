## ESP32 Internet Radio

# Overview

This project is an ESP32 Internet Radio inspired by the excellent work of educ8s.tv. Unlike traditional radios, which receive radio waves from the air, an internet radio streams radio stations via websites. It connects to the internet through a microcontroller, retrieves data from streaming websites, decodes it into audio signals using an MP3 decoder, amplifies the signals, and then plays them through a speaker.

This repository includes the code and instructions for building your own internet radio using an ESP32 microcontroller.

# Why I Made This Project

I built this project to learn more about radio waves and their applications. Radio waves are an integral part of our daily lives—whether it’s Wi-Fi, Bluetooth, or cell signals. By diving into this project, I explored how radio signals work, especially in the context of streaming, decoding, and playing internet radio stations.

# Components Used

Below is a list of materials I used to build the ESP32 Internet Radio, along with links to the components for your convenience:

	•	ESP32 Microcontroller: Buy it here
	•	PAM8403 Amplifier: Buy it here
	•	VS1053 MP3 Decoder: Buy it here
	•	2W Micro Speaker: Buy it here
	•	128x32 OLED Display: Buy it here
	•	TP4056 Charging Module: Buy it here
	•	3.7V 1100mAh LiPo Battery: Buy it here
	•	Potentiometer knob, Buttons, and Switch
	•	Black Cloth (Speaker Grill)
	•	Prototype PCB Board
	•	Wooden Enclosure: Custom-made using a laser cutter (you could also use a 3D printed enclosure, feel free to design one!)

# How It Works

The ESP32 microcontroller connects to the internet via Wi-Fi. It accesses the streaming websites that host radio stations, grabs the audio data, and sends it to the VS1053 MP3 decoder to decode the audio signal. The decoded signal is amplified using the PAM8403 amplifier and played through the 2W speaker. The 128x32 OLED screen displays the current station information.

	•	ESP32: Handles internet connection and data streaming.
	•	VS1053: Decodes audio signals.
	•	PAM8403: Amplifies the decoded audio for the speaker.
	•	TP4056: Manages battery charging.
	•	Buttons & Switch: Used for navigating between radio stations and turning the device on/off.

## Building the Project

# Step 1: Breadboard Testing

Before you start soldering, it’s important to connect all the components on a breadboard and test everything. During my build, I encountered an issue where the OLED display was broken after soldering. So, always test your components first to avoid reworking the circuit later.

# Step 2: Schematic

Refer to the schematic (provided in the repository) for connecting all the components. Ensure each connection is secure and correct before moving forward.

# Step 3: Uploading the Code

Initially, I used the code provided by educ8s.tv, but it didn’t work well for my setup—the audio was jittery. I found another improved version of the code, but it still had issues with the libraries. So, I decided to write my own code, using simpler libraries, and that solved the problem.

You can find the working code in this repository. I hope it will help you with your project!

# Step 4: Soldering

Once you’ve confirmed everything works on the breadboard, solder the components to the prototype PCB board. Be careful when soldering, as the ESP32 pins are small, and it’s easy to damage the board if you’re not precise. If you’re new to soldering, take extra care not to short any connections.

# Step 5: Enclosure and Final Assembly

I used a laser cutter to create a wooden enclosure for my internet radio. If you have access to a laser cutter, you can do the same, or alternatively, someone could design a 3D-printed enclosure to make it more accessible to others.

	•	The LiPo battery is placed behind the VS1053 MP3 decoder.
	•	The TP4056 charging module and the power switch are mounted underneath the ESP32.
	•	I designed and 3D-printed button caps to give the buttons a cleaner look.

# Step 6: Final Testing

After assembly, test the device to ensure that everything functions as expected. Check that:

	•	The radio streams smoothly without interruptions.
	•	The buttons switch between radio stations properly.
	•	The battery charges and powers the device correctly.

# Lessons Learned

	•	Always test components on a breadboard before soldering.
	•	Writing your own code can solve compatibility issues with libraries.
	•	Be careful when soldering small components like the ESP32 pins.
	•	It’s good to have a proper case for the device, even if it’s wooden. A 3D-printed case would be more accessible for most people.

# Future Improvements

I would love to see someone design a 3D-printed enclosure for this project. A custom, printable case would make it easier for others to replicate without the need for specialized tools like a laser cutter.

# Video Demonstration

Check out the video showcasing how the ESP32 Internet Radio works: Watch the video

# Contact

If you have any questions or need further clarification, feel free to reach out to me through my YouTube Channel - ZETRO Labs.
