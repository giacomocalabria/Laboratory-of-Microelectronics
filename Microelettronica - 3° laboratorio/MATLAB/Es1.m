close all;
clear all;
clc;
workspace;

dutycycle = 20:10:80;
Vout = [1.0149, 1.8014, 2.6089, 3.4165, 4.2398, 5.0630, 5.2021];

plot(dutycycle,Vout,"LineWidth",1.5);
grid on;
hold on;
title("Dipendenza tra duty cycle e tensione di uscita V_o")
xlabel("Duty cycle");
ylabel("Tensione di uscita V_o");