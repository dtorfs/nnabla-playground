import pprint
import numpy as np

import nnabla as nn
import nnabla.parametric_functions as PF
import nnabla.functions as F
from nnabla.utils.save import save

#
# construct a super simple network:
#   - one full-dense layer
#   - followed by softmax

x = nn.Variable((1, 5))          # input tensor is just a vector of 5 floats
y = F.softmax(PF.affine(x, 3))   # output is probs for 3 classes

nn.get_parameters()['affine/W'].d = np.random.randn(5, 3)   # fill the dense layer with random weights
nn.get_parameters()['affine/b'].d = [0, 0, 0]               # no bias

pprint.pprint(nn.get_parameters())
pprint.pprint(nn.get_parameters()['affine/W'].d)

x.d = range(5)
# Execute a forward pass
y.forward()
# Showing results
print("**** nnabla (python runtime): predictions: {}".format(y.d))  # we will later check this output with the output of the runtime engine


contents = {
        'networks': [
            {'name': 'main',
             'batch_size': 1,
             'outputs': {'y': y},
             'names': {'x': x}}],
        'executors': [
            {'name': 'runtime',
             'network': 'main',
             'data': ['x'],
             'output': ['y']}]}

save('net.nnp', contents)   # save the network

