# MasterCaution.py

import pygame.mixer
from time import sleep
from sys import exit
import serial

pygame.mixer.pre_init(44100, 16, 2, 4096)
pygame.init()

soundA = pygame.mixer.Sound("/home/pi/Space/CWS.wav") 
soundB = pygame.mixer.Sound("/home/pi/Space/JFS.wav")  # SoundB and C unused; this code was borrowed from a 
soundC = pygame.mixer.Sound("/home/pi/Space/PU.wav")   # soundboard example and I was too lazy to take it out.

soundChannelA = pygame.mixer.Channel(1) 
soundChannelB = pygame.mixer.Channel(2)     # SoundB and C unused; this code was borrowed from a 
soundChannelC = pygame.mixer.Channel(3)     # soundboard example and I was too lazy to take it out.

print "Sampler Ready."
Cockpit = serial.Serial("/dev/ttyACM0",115200)
Cockpit.flush()

while True:
    try:
        val = ord(Cockpit.read())
        print(val)
        if (val == 2):
            soundA.play(loops = -1)
	    Cockpit.write('H')
        if (val == 4):
            soundA.stop()
        if (val == 3):                     # SoundB and C unused; this code was borrowed from a    
            soundChannelC.play(soundC)     # soundboard example and I was too lazy to take it out.
        val = 0
        sleep(.01)
    except KeyboardInterrupt: 
        exit()
