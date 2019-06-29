function []=stepd(steps,pin,pindir,dir,speed,a)
a.pinMode(pin,'output');
a.pinMode(pindir,'output')
a.digitalWrite(pindir,dir);



for i=0:steps
    a.digitalWrite(pin,1)
  pause(speed)
    a.digitalWrite(pin,0)
    pause(speed)

end
