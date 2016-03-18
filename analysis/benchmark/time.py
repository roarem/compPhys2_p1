import matplotlib
font = {'family':'normal',\
	'weight':'normal',\
	'size'	:'22'\
	}
matplotlib.rc('font',**font)
import matplotlib.pyplot as plt
import numpy as np

	

anaHaste = np.asarray([0.018,0.024,0.075,0.312])
numHaste = np.asarray([0.023,0.099,2.868,61.191])
anaImp	 = np.asarray([0.03,0.038,0.111,0.451])
numImp	 = np.asarray([0.035,0.111,2.907,61.364])

NParticles = np.asarray([1,10,100,500])

fig, ax = plt.subplots(2,2,sharex=True,sharey=True,figsize=(15,12))
ax[0,0].plot(NParticles,np.divide(NParticles,anaHaste),marker='o',label="Analytical")
ax[0,0].set_title("Hastings Analytical")
ax[0,1].plot(NParticles,np.divide(NParticles,numHaste),marker='o',label="Numerical")
ax[0,1].set_title("Hastings Numerical")
ax[1,0].plot(NParticles,np.divide(NParticles,anaImp),marker='o',label="Analytical")
ax[1,0].set_title("Imp. Samp. Analytical")
ax[1,1].plot(NParticles,np.divide(NParticles,numImp),marker='o',label="Numerical")
ax[1,1].set_title("Imp. Samp. Numerical")
ax[0,0].set_xscale("log")
ax[0,1].set_xscale("log")
ax[1,0].set_xscale("log")
ax[1,1].set_xscale("log")
ax[0,0].set_yscale("log")
ax[0,1].set_yscale("log")
ax[1,0].set_yscale("log")
ax[1,1].set_yscale("log")
#ax[0,0].set_xlabel("Number of particles")
#ax[0,1].set_xlabel("Number of particles")
ax[1,0].set_xlabel("Number of particles")
ax[1,1].set_xlabel("Number of particles")
ax[0,0].set_ylabel("$\\frac{dN}{dt}$").set_rotation(0)
ax[0,1].set_ylabel("$\\frac{dN}{dt}$").set_rotation(0)
ax[1,0].set_ylabel("$\\frac{dN}{dt}$").set_rotation(0)
ax[1,1].set_ylabel("$\\frac{dN}{dt}$").set_rotation(0)
plt.savefig("Npart_time.pdf")
