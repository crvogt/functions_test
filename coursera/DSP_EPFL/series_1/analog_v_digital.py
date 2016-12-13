import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import IPython as ipy
from scipy.io import wavfile

rate, s = wavfile.read('/home/carson/functions_test/coursera/DSP_EPFL/series_1/singing_44100.wav')
#plt.plot(s);

#ipy.display(s, rate=rate)

#the analog signal is simply rescaled between -100 and +100
# largest element in magnitude:
norm = 1.0 / max(np.absolute([min(s), max(s)]))
sA = 100.0 * s * norm

#the digital version is clamped to the integers
sD = np.round(sA)
#Show the signal to noise ratio
#plt.plot(sA-sD)

#we will be computing SNRs later as well, so let's define a function
def SNR(noisy, original):
	#power of the error
	err = np.linalg.norm(original-noisy)
	#power of the signal
	sig = np.linalg.norm(original)
	#SNR in dBs
	return 10 * np.log10(sig/err)

print('SNR = %f dB' % SNR(sD, sA))

wavfile.write("sD.wav", rate, sD.astype(np.dtype('i2')))
wavfile.write("sA.wav", rate, sA.astype(np.dtype('i2')))

plt.show()
