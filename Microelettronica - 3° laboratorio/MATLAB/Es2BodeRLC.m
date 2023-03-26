close all;
clear all;
clc;
workspace;

L = 6.8e-4;
R = 50;
C = 2.0e-5;

a = L/R;
b = L*C;

G = tf(1,[b, a, 1]);

bode(G);
grid on;