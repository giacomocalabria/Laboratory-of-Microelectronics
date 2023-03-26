close all;
clear all;
clc;
workspace;

F = [10,30,50,100,300,500,1000,3000,5000];

G = [0.01692, 0.01692, -0.03394, -0.03394, -0.4154, -1.1509, -3.401, -10.761, -14.614, -28];

P = [-179.42, -178.3, -177.16, -174.2, -162.3, -151.5, -133.3, -105.3, -99.3]; 

for i = 1:9
    P(i) = -180+(-180-P(i));
end

semilogx(F,G,'LineWidth',1.5);
grid on;
hold on;
title('Diagramma di Bode del modulo');
xlabel('Frequenza');
ylabel('Guadagno dB');


semilogx(F,P,'LineWidth',1.5);
grid on;
hold on;
title('Diagramma di Bode delle fasi');
xlabel('Frequenza');
ylabel('Fase');
