import serial
import os
import time
import commands
import subprocess
import smtplib


def sendEmail(s,b):
	smtp_client = smtplib.SMTP('smtp.gmail.com', 587)
	smtp_client.starttls()
	smtp_client.ehlo()
	smtp_client.login('email', 'password')
	print smtp_client.sendmail('to','from','Subject: ' + s + '\r\n' + b + '\n\n')
	smtp_client.quit()

s=serial.Serial("/dev/tty.usbmodemfd1231",9600)
badEntry = 0
with open("Output.txt", "w") as text_file:
	text_file.write("<<< Beginning Knock Sequence >>> \n")
while True:
	message=s.readline()
	message = message.strip()
	print(message + "\n");
	if (message == "Door unlocked!"):
		""" Interaction here """ 
		badEntry = 0
		sendEmail('Door Unlocked',"Your door has been unlocked at time " + time.strftime("%Y-%m-%d %I:%M:%S"))
	if (message == "Secret knock failed."):
		badEntry=badEntry + 1
		if (badEntry>=3):
			print("Attempted Entry Detected");
			sendEmail('Attempted Entry', "Someone has attempted to open your door " + str(badEntry) + " times at " + time.strftime("%Y-%m-%d %I:%M:%S"))
	with open("KnockLog.txt", "a") as text_file:
   	 text_file.write(message + "\n")


