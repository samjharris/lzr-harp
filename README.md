# lzr-harp
A harp, with lasers.

##What is it?
A theremin is an electronic musical instrument that can be played without physical contact. Here, users can “pluck” the laser beams by breaking them with their fingers. LZR HARP will play various musical notes corresponding to those broken beams.

Watch a demo by clicking here: 
[![demo video](https://img.youtube.com/vi/8gqOdAnWyWA/0.jpg)](https://youtu.be/8gqOdAnWyWA)

##How does it work?
Unsurprisingly, LZR HARP is comprised of both hardware and software. Let’s talk about that:

The hardware used in LZR HARP is shown in the [circuit diagram](circuit.png). Here is a summary of what it does: Five laser-diodes, wired in parallel, are aimed directly at the surfaces of five cadmium sulfide photoresistors. The photons leaving the laser-diodes will either hit the surface of the photoresistors or hit a user’s finger. Photoresistors are photoconductive, which means that photons striking the surfaces of each photoresistor reduces their respective resistances. To leverage this property, a voltage-divider is formed at each of these photoresistors. Each of these 5 voltage outputs are connected to GPIO pins of an LPC1768 Microcontroller. The LPC1768 has a Digital-to-Analog-Converter onboard, so we connect this DAC to a simple, low-power audio-amplifier-circuit (using an LM386N op-amp).

The software runs on the aforementioned LPC1768 Microcontroller. All of the code can be found in [main.cpp](main.cpp). In summation, the program loops infinitely, checking GPIO pins for broken beams in each iteration. When beams are broken, sounds are played. Specifically, each of the 32 possible combinations of broken lasers are mapped to one of the 36 notes we define, which are C3 through B5, computed by manipulating the A4 (440Hz) pitch standard. Using the [SoundWaveGenerator](https://os.mbed.com/users/osmeest/code/SoundWaveGenerator/) library by Olivier Smeesters, those notes are converted to sine waves and sent through the microcontroller’s DAC.

