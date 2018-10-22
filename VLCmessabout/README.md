The line under properties->toolchain->Misc. must be updated to this for the project to flash properly...

-Tsamd21g18a_flash.ld  -Wl,--section-start=.text=0x2000

Run this line in a command line window to make the project run.

You'll have to update the arduino install location and project .bin location
C:\Users\techi\AppData\Local\Arduino15\packages\arduino\tools\bossac\1.7.0/bossac -i -d --port=COM12 -U true -i -e -w -v "C:\Users\techi\Documents\Senior Project Repo\-LED\VLCmessabout\VLCmessabout\Debug\VLCmessabout.bin" -R 

Also, you will have to figure out what port the Feather is on.
Press the feathers button twice quickly to go into progrmaming mode.  The LED will fade up and down slowly.

Run the python program on the Raspberry Pi, with the ground pin attached at pin 6, and the TX pin attached at Pin 10.  Nothing is sent from the pi, so attaching the RX pin is unnecessary.