close all;
clear all;
clc;
workspace;

L = 680e-6;
R = 50;
C = 20e-6;

a = L/R;
b = L*C;

V = 8;

Gvd = tf(1,[b, a, 1]);

W = 5;

Gpwm = 8/5;

Rf = 10000;
Ri = 10000;

Cf = 1e-8;
Ci = 1e-8;

k = - Rf / Ri;

tau1 = Rf * Cf;
tau2 = Ri * Ci;

Gr = tf([0.0001, 2, 10000],[1 0]);

bode(Gr*k*Gpwm*Gvd);
grid on;
hold on;

margin (Gr*k*Gpwm*Gvd);
grid on;
hold off