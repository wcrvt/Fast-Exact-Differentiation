import optuna
import math
import numpy as np

def phi(i, t, s, L, eta, mu):
	n=1
	return eta[n-i]*math.pow(L, 1/(n-i+1))*math.pow(math.fabs(s), (n-i)/(n-i+1))*np.sign(s) + mu[n-1]*s;

def evaluate(L, eta, mu):
	t=0.0
	Ts=1e-4
	tlen=10.0
	tloop=int(tlen/Ts)
	f=[3.0,5.0,8.0]
	nu=[0.0, 0.0]
	z=[0.0, 0.0]
	score=0.0
	for i in range(tloop):
		x=+1.0-math.cos(2.0*math.pi*f[0]*t)
		x+=1.0-math.cos(2.0*math.pi*f[1]*t)
		y=+2.0*math.pi*f[0]*math.sin(2.0*math.pi*f[0]*t)
		y+=2.0*math.pi*f[1]*math.sin(2.0*math.pi*f[1]*t)
		nu[0] = -phi(0, t, z[0]-x, L, eta, mu) + z[1]
		nu[1] = -phi(1, t, z[1]-nu[0], L, eta, mu)
		z[0] += nu[0]*Ts
		z[1] += nu[1]*Ts
		t+=Ts
		score+=math.pow(y-z[1], 2.0)
	return score

def objective(trial):
	# Parameter desgin by the optimizer.
	L = trial.suggest_uniform('L', 10, 30)
	eta1 = trial.suggest_uniform('eta1', 1, 50)
	eta2 = trial.suggest_uniform('eta2', 1, 50)
	mu1 = trial.suggest_uniform('mu1', 1, 50)
	mu2 = trial.suggest_uniform('mu2', 1, 50)

	eta=[eta1,eta2]
	mu=[mu1,mu2]
	score = evaluate(L, eta, mu)

	# Return the score to the optimizer.
	return score


study = optuna.create_study()
study.optimize(objective, n_trials=100)

print("\n")
print("Parameters:", study.best_params)
print("Value:", study.best_value)
print("\n")

L=study.best_params['L']
eta=[study.best_params['eta1'], study.best_params['eta2']]
mu=[study.best_params['mu1'], study.best_params['mu2']]
t=0.0
Ts=1e-4
tlen=10.0
tloop=int(tlen/Ts)
f=[3.0,5.0,8.0]
nu=[0.0, 0.0]
z=[0.0, 0.0]
score=0.0
file= open('pydata.dat', 'w', encoding='UTF-8')
for i in range(tloop):
	x=+1.0-math.cos(2.0*math.pi*f[0]*t)
	x+=1.0-math.cos(2.0*math.pi*f[1]*t)
	y=+2.0*math.pi*f[0]*math.sin(2.0*math.pi*f[0]*t)
	y+=2.0*math.pi*f[1]*math.sin(2.0*math.pi*f[1]*t)
	nu[0] = -phi(0, t, z[0]-x, L, eta, mu) + z[1]
	nu[1] = -phi(1, t, z[1]-nu[0], L, eta, mu)
	z[0] += nu[0]*Ts
	z[1] += nu[1]*Ts
	result = "{:.7f} {:.7f} {:.7f}\n".format(t, y, z[1])
	file.write(result)
	t+=Ts
	score+=math.pow(y-z[1], 2.0)
