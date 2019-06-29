clc

close all
%a.pinMode(13,'OUTPUT')
a.servoAttach(11);
a.servoWrite(11,180);
fid = fopen('square.txt');
piny=9;
pindy=8;
pinx=13;
pindx=12;
resox=0.0692;
resoy=0.0692;
tline = fgets(fid);
lo=1;
x1=0;
y1=0;
sumx1=0;
sumy1=0;
j=1;
empline=sprintf('\r\n');
hold;
while ischar(tline)
    
    gline = fgets(fid);
     disp(gline);
    if gline==-1
        disp('Task Complete');
        break;
    end
     if strcmp(gline,empline)
            break;
     end
        
    if ~isempty(find(gline=='Z'))
    Z=sscanf(gline,'N%f G%f Z%f');
    if(Z(3)>0)
        disp('up');
        a.servoWrite(11,180);
    end
    if(Z(3)<0)
        disp('down');
        a.servoWrite(11,155);
        
    end
    end
    
    if (isempty(find(gline=='Z')))&&(isempty(find(gline=='M')))
        
        A=sscanf(gline,'N%f G%f X%f Y%f');
        if(A(2)~=90)
        x=A(3);
        y=A(4);
        px(j)=x;
        py(j)=y;
        
        plot(px(j),py(j),'r.');
       % drawline([x1 y1],[x y]);
        axis([0 140 0 140]);
        
        j=j+1;
        dx=x-x1;
        dy=y-y1;
        stepx=dx/resox;
        stepy=dy/resoy;
        if (stepx>0)
            dirx=0;
            dirx1=1;
        else
            dirx=1;
            dirx1=-1;
        end
        if (stepy>0)
            diry=1;
            diry1=1;
        else
            diry=0;
            diry1=-1;
        end
        stepx=abs(stepx);
        stepy=abs(stepy);
        sumx=x1;
        sumy=y1;
        if(round(stepx)==0)
            stepx=1;
        end
        if(round(stepy)==0)
            stepy=1;
        end
            
            
            
        if (stepx>stepy)
        
          istep=stepx/stepy;
          istep=round(istep);
          stepy=round(stepy);
          for n=1:stepy
          stepd(istep,pinx,pindx,dirx,0.000000001,a);
          stepd(1,piny,pindy,diry,0.000000001,a);
          sumx=sumx+istep*resox*dirx1;
          sumy=sumy+1*resoy*diry1;
          drawline([sumx1 sumy1],[sumx sumy]);
         
          sumx1=sumx;
          sumy1=sumy;
          end
        end
        
        if (stepy>stepx)
            istep=stepy/stepx;
            istep=round(istep);
            stepx=round(stepx);
            for n=1:stepx
            stepd(istep,piny,pindy,diry,0.000000001,a);
            stepd(1,pinx,pindx,dirx,0.000000001,a);
            sumx=sumx+1*resox*dirx1;
          sumy=sumy+istep*resoy*diry1;
          drawline([sumx1 sumy1],[sumx sumy]);
         
          sumx1=sumx;
          sumy1=sumy;
            end
        end
            
       % stepd(stepx,11,0.000000001,a)
        
        
        x1=x;
        y1=y;
        end
        
        %disp('sravan')
    end
    
    
end
%stem(px,py);

%plot(px,py,'r.');hold
%plot(px,py);
fclose(fid);