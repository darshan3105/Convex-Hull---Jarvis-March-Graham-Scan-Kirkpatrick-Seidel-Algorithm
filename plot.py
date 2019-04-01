import matplotlib.pyplot as plt

t0 = [10,100,1000,10000,50000,70000]
s0 = [0,0,0,0,0,600]

t1=[10,100,1000,10000,50000,70000,100000,200000,500000,1000000]
s1=[0,0,0,0,0,0,1,1,4,8]

t2=[10,100,1000,10000,50000,70000,100000,200000]
s2=[0,0,0,0,1,1,1,1]

plt.subplot(3, 1, 1)
plt.plot(t0, s0, 'o-')
plt.title('Jarvis')
plt.xlabel('Numbre of points')
plt.ylabel('Time (sec)')
plt.grid(True)

plt.subplot(3, 1, 2)
plt.plot(t1, s1, '.-')
plt.title('Graham')
plt.xlabel('Numbre of points')
plt.ylabel('Time (sec)')
plt.grid(True)

plt.subplot(3, 1, 3)
plt.plot(t2, s2, '.-')
plt.title('KPS')
plt.xlabel('Numbre of points')
plt.ylabel('Time (sec)')
plt.grid(True)

plt.tight_layout()
plt.savefig("final_fig.png")
plt.show()
