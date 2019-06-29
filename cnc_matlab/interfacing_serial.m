clc
clear all
arsend=serial('com4')
set(arsend,'BaudRate',9600)
set(arsend,'Parity','none')
set(arsend,'StopBit',1)
set(arsend,'DataBits',8)
disp(get(arsend,{'port','type','name','BaudRate','StopBit','DataBits','Parity'}))
fopen(arsend)
int t=1000
for i=0:1:10
fprintf(arsend,'%d',t)
%fprintf(arsend,'a')
end

fclose(arsend)

