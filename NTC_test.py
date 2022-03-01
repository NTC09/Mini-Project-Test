import matplotlib.pyplot as plt
import numpy as np

plt.style.use('_mpl-gallery')
A = 0.001110864337533712
B = 0.0002402386598987505
C = -4.99706118262111e-007
D = 9.325597005727104e-008

# make data
R = np.linspace(100, 200000, 10000)
adc=np.linspace(0, 1023.0, 1024)
R2=10000.0 * ((1023.0/adc - 1.0 ))
T = 1.0 / (A + B*np.log(R) + C*np.log(R)*np.log(R) + D*np.log(R)*np.log(R)*np.log(R)) - 273.15
T2 = 1.0 / (A + B*np.log(R2) + C*np.log(R2)*np.log(R2) + D*np.log(R2)*np.log(R2)*np.log(R2)) - 273.15
# plot
fig, ax = plt.subplots()

ax.plot(R, T, linewidth=2.0)
ax.plot(R2, T2, linewidth=2.0)

plt.show()