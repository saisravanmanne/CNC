


t=0.0000001
T=800
a.pinMode(13,'output')
a.pinMode(12,'output')
a.servoAttach(10);
a.digitalWrite(12,0)
for i=0:T                          
    a.digitalWrite(13,1)
  pause(t)
    a.digitalWrite(13,0)
    pause(t)
end
a.digitalWrite(12,1)
for i=0:T                          
    a.digitalWrite(13,1)
  pause(t)
    a.digitalWrite(13,0)
    pause(t)
end

