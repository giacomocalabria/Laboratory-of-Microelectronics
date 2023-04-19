close all;
clear all;
clc;
workspace;

C = 220E-9;
R = 220E3;

G = tf([R*C, 0],[R*C, 1]);
bode(G);
grid on;