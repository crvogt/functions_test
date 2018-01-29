from skadata.mnist.views import OfficialVectorClassification
from tqdm import tqdm
import numpy as np 
import tensorflow as tf 

data = OfficialVectorClassification()

trIdx = data.se1_idxs[:]