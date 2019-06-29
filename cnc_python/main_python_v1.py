#importing required libraries
import serial
import numpy as np
import matplotlib.pyplot as p
import time
import pylab
arduino=serial.Serial('COM3', 9600)
arduino.bytesize = serial.EIGHTBITS #number of bits per bytes
arduino.parity = serial.PARITY_NONE #set parity check: no parity
arduino.stopbits = serial.STOPBITS_ONE #number of stop bits
m=[]
x=[]
y=[]
z=[]
g=[]
f=[]
output=[]
dirX=1
dirY=7
#reading the gcode and storing in a list array
gcode = open('hot.txt','r')              
lines=gcode.readlines()                  
for line in lines:                       
    m.append(line.split())  #splitting at spaces and storing in multi dimension matrix
gcode.close()        #justy to separate the lines           
i=3
b=len(m)-3         
#separating x,y,z values
while i!=b:
    a=len(m[i])       #a indicates corresponding column size.
    if 'G00' in m[i][1]:
        g.append(0)
        if a>=3:    #includes x,y,z values 
            if 'X' in m[i][2]:
                x.append(m[i][2])
                z.append(3)
            elif 'Z' in m[i][2]:
                z.append(9)
                x.append('0')
                y.append('0')
            else:
                x.append('0')
                y.append('0')
        if a>=4:   #will only include x,y
            if 'Y' in m[i][3]:
                y.append(m[i][3])
            else:
                y.append('0')
        
    elif 'G01' in m[i][1]:
        g.append(1)
        if a>=3:
            if 'X' in m[i][2]:
                x.append(m[i][2])
                z.append(3)
            elif 'Z' in m[i][2]:
                z.append(9)
                x.append('0')
                y.append('0')
            else:
                x.append('0')
                y.append('0')
        if a>=4:
            if 'Y' in m[i][3]:
                y.append(m[i][3])
            elif 'F' in m[i][3]:
                f.append(1)  
            else:
                y.append('0')
    else:
        g.append(2)
    i+=1
#removing 'X' from each sting in matrix and converting into float
s=1
while s!=len(x)+1:         #minor error only 1st line missing
    if 'X' in x[s-1]:
        x[s-1]=x[s-1].strip('X')
    x[s-1]=float(x[s-1])
    #if x[s]==0:
        #x[s]=float(x[s-1])
    s+=1
    
#removing 'Y' from each sting in matrix y and converting into float
s=1
while s!=len(y)+1:
    if 'Y' in y[s-1]:
        y[s-1]=y[s-1].strip('Y')
    y[s-1]=float(y[s-1])
    #if y[s]==0:
        #y[s]=float(y[s-1])
    s+=1
#x[0]=float(x[0])
#y[0]=float(y[0])
#no of steps each axis should move
step=0.08 #leastdistance each axis could move
s=0
c=0
while s!=len(x)-1:
    xx=x[s+1]-x[s] #Finding delta x
    yy=y[s+1]-y[s] #Finding delta Y
    zz=z[s]        
    output.append(zz)
    xsteps=round(xx/step) #Finding number of steps for x
    ysteps=round(yy/step) #Finding number of steps for y
    if xsteps<0:
        dirX=4
    elif xsteps>0:
        dirX=1
    if ysteps<0:
        dirY=10
    elif ysteps>0:
        dirY=7       
    ax=abs(xsteps)
    ay=abs(ysteps)
    if ax!=0 and ay!=0:
        if ax>ay:
            rat=ax//ay
            rem=ax%ay
            A=dirX*1000+1
            B=dirY*1000+1
            C=dirX*1000+rat
            D=dirY*1000+rat
            E=dirX*1000+rem
            F=dirY*1000+rem
            G=dirX*1000+ax
            H=dirY*1000+ay
            c=0
            while c!=ay:  #since c initially zero
                output.append(B)#here we need to send the data serially to y axis for 1 step with direction
                output.append(C)#here we need to send the data serially to x axis for rat steps with direction
                c+=1                      
            output.append(E)#here we need to send the data serially to x axis for rem steps with direction
        elif ay>ax:
            rat=ay//ax
            rem=ay%ax
            A=dirX*1000+1
            B=dirY*1000+1
            C=dirX*1000+rat
            D=dirY*1000+rat
            E=dirX*1000+rem
            F=dirY*1000+rem
            #G=dirX*ax
            #H=dirY*ay
            c=0
            while c!=ax:
                output.append(A)#here we need to send the data serially to x axis for 1 step with direction
                output.append(D)#here we need to send the data serially to y axis for rat steps with direction
                c+=1
            output.append(F)#here we need to send the data serially to y axis for rem steps with direction
        else:
            c=0
            while c!=ax:
                A=dirX*1000+1
                B=dirY*1000+1
                output.append(A)#here we need to send the data serially to x axis for 1 step with direction
                output.append(B)#here we need to send the data serially to y axis for 1 step with direction
                c+=1
    else:
        if ax==0:
            H=dirY*1000+ay
            #c+=1
            output.append(H)#here we need to send the data serially to y axis for ay steps with direction
            
        else:
            G=dirX*1000+ax
            #c+=1
            output.append(G)#here we need to send the data serially to x axis for ax steps with direction
           
    #print(xsteps,',\t',ysteps)
    s+=1
s=0
#output=[9, 4000, 3, 4000, 9, 1875, 3, 4875, 3, 1875, 3, 4875, 3, 4000, 9, 4000]
output=np.absolute(output)
print(output)
length=len(output)
print(length)
p.plot(x,y)
p.show()
arduino.flushOutput()
#time.sleep(1)
while s!=length:
    
    word=float(output[s])
    #print("2")
    arduino.flushOutput()
    arduino.write(bytearray(str(word).encode()))
    
    #arduino.flushInput()
    #print("dude")
    arduino.readline()
   
    print(s)
    s+=1
  
print('done')

input('press enter to exit')
