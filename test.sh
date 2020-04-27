# construct a simple network
python simple.py
# convert it to the NNB format 
nnabla_cli convert -b 1 --api 6 net.nnp net.nnb
# build and execute the sample that uses the runtime engine
make
# now check the whether the outputs match
