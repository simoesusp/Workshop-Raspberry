Overclock Tips

- It is possible to overclock the RaspberryPi by editing the config.txt file that Rasp uses during boot.
- The file config.txt is in the /boot  folder
- To test it, we used an OpenCV program to detect faces, included in the software folder.
- We tested a RaspberryPi2 with a heat sink and an improvised 12v fan from an old 486 computer.
- To overclock the RaspberryPi2, just include these lines:

##Turbo Overclock
arm_freq=1000
core_freq=500
sdram_freq=500
over_voltage=6


- Do not forget also to allocate more memory to the gpu if you are using the graphical interface:


gpu_mem=320	


- If you decide to turn back to the default:

##None Overclock
#arm_freq=700
#core_freq=250
#sdram_freq=400
#over_voltage=0
