import serial
import os
import time
import commands
import subprocess
import smtplib

import email
import email.mime.application




s=serial.Serial("/dev/tty.usbmodemfa1371",9600)




with open("Data.txt", "w") as text_file:
	text_file.write("<<< Save 1-2-3 Knocks >>> \n")
while True:
	message=s.readline()
	message = message.strip()

	print(message)
	
	if message != "Program start." and message != "Serial Start : 248" :
		with open("Data.txt", "a") as text_file:
   	 		text_file.write(message + "\n")


