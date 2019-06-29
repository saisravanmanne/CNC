


t=0.0000001
T=1600
a.pinMode(9,'output')
a.pinMode(8,'output')
a.servoAttach(10);
a.digitalWrite(8,0)
for i=0:T                          
    a.digitalWrite(9,1)
  pause(t)
    a.digitalWrite(9,0)
    pause(t)
end
a.digitalWrite(8,1)
for i=0:T                          
    a.digitalWrite(9,1)
  pause(t)
    a.digitalWrite(9,0)
    pause(t)
end

