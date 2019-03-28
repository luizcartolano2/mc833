import os
import pdb

# entra com o IP se quiser
redes = ['localhost']
for rede in redes:
    for i in range(1,6):
        for k in range(0,1):
            linha_executavel = './client ' + rede + ' < input' + str(i) + ' > temp.txt'
            os.system(linha_executavel)
            pdb.set_trace()