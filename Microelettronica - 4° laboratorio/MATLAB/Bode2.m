close all;
clear all;
clc;
workspace;

F = [1,3,5,10,30,50,100,300,500,1000];

M = [15.119,21.954,23.919,24.987,25.389,25.389,25.389,25.433,25.476,25.562];

loglog(F,M,'*-',"linewidth",1.5);
grid on;
xlabel('Frequenza (Hz)','Interpreter','latex');
ylabel('$V_a/V_{in}$ (dB)','Interpreter','latex');
title("Diagramma di Bode del modulo",'Interpreter','latex');