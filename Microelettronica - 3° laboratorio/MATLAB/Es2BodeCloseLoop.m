close all;
clear all;
clc;
workspace;

L = 6.8e-4;
R = 50;
C = 2.0e-5;

a = L/R;
b = L*C;

Gvd = tf(1,[b, a, 1]);

W = 5;
V = 8;

Gpwm = tf(V,W);

Rf = 1e4;
Ri = 1e4;

Cf = 1e-8;
Ci = 1e-8;

k = - Rf / Ri;

tau1 = Rf * Cf;
tau2 = Ri * Ci;

Gr = tf([k*tau1*tau2, k*(tau1+tau2), k],tau1);

bode(Gr*Gpwm*Gvd);
grid on;