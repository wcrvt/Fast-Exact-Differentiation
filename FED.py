import optuna
import math
import numpy as np

def phi(i, t, s, L, eta, mu):
	n=1
	return eta[n-i]*math.pow(L, 1/(n-i+1))*math.pow(math.fabs(s), (n-i)/(n-i+1))*np.sign(s) + mu[n-1]*s;

def evaluate(L, eta, mu):
	t=0.0
	Ts=1e-4
	tlen=3.0
	tloop=int(tlen/Ts)
	f=3.0
	nu=[0.0, 0.0]
	z=[0.0, 0.0]
	score=0.0
	for i in range(tloop):
		x=1.0-math.cos(2.0*math.pi*f*t)
		y=2.0*math.pi*f*math.sin(2.0*math.pi*f*t)
		nu[0] = -phi(0, t, z[0]-x, L, eta, mu) + z[1];
		nu[1] = -phi(1, t, z[1]-nu[0], L, eta, mu);
		z[0] += nu[0]*Ts;
		z[1] += nu[1]*Ts;
		t+=Ts
		score+=math.pow(y-z[1], 2.0)
	return score
