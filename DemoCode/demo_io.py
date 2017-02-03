# Lecture/Ecriture en texte et binaire d'ne variable
import numpy as np
import time

NN = 256
velocity = np.random.rand(NN, NN, NN)

txtfile = open('out_txt', 'w')
binfile = open('out_bin', 'wb')


# texte
tinit = time.clock()
for v in velocity.flat:
    val = "{:.10f}".format(v) + "\t"
    txtfile.write(val)

txtfile.close()

print 'Ecriture du fichier txt:', time.clock() - tinit

# binaire
tinit = time.clock()
for v in velocity.flat:
    #%print velocity[i, j, k]
    #val = "{:.10f}".format(v) + "\t"
    binfile.write(v)

binfile.close()
print 'Ecriture du fichier txt:', time.clock() - tinit

