
#importing required libraries
import serial
import numpy as np
import matplotlib.pyplot as p
import time
import pylab
arduino=serial.Serial('COM5', 9600)
arduino.bytesize = serial.EIGHTBITS #number of bits per bytes
arduino.parity = serial.PARITY_NONE #set parity check: no parity
arduino.stopbits = serial.STOPBITS_ONE #number of stop bits
output=[]
s=100
k=1200
while s!=0:
    output.append(k)
    k=k-1
    s=s-1

output=[1200]
s=0
length=len(output)
print(output)

arduino.write(output)
