close all;
clear all;
clc;
workspace;

Vref = 2:0.5:6;

dutycycle = [30.49, 36.53, 42.68, 48.72, 54.76, 60.78, 66.80, 72.76, 78.77];
Vout = [1.9414, 2.4433, 2.9355, 3.4372, 3.9304, 4.2222, 4.9176, 5.4018, 5.9040];

plot(Vref,dutycycle,"LineWidth",1.5);
grid on;
hold on;
title("Dipendenza tra tensione di riferimento V_r e duty cycle")
ylabel("Duty cycle");
xlabel("Tensione di riferimento V_r");

