import os
import pdb
import pandas as pd
import re

# entra com o IP se quiser
redes = ['localhost']
d = {'Opcao': [], 'Tempo(ms)': []}
tempo_local = pd.DataFrame(data=d)
tempo_2_maquinas = pd.DataFrame(data=d)

for rede in redes:
    for i in range(1,6):
        for k in range(0,1):
            linha_executavel = './client ' + rede + ' < input' + str(i) + ' > temp.txt'
            os.system(linha_executavel)
            f = open("temp.txt","r", encoding="ISO-8859-1")
            content = f.readlines()
            for x in content:
                if 'Tempo cliente:' in x:
                    tempo = str(x[x.find(':')+1 : -1])
                    tempo = tempo.strip()
                    if rede == 'localhost':
                        temp_df = pd.DataFrame(data={'Opcao': [str(i)], 'Tempo(ms)': [tempo]})
                        tempo_local = tempo_local.append(temp_df)
                    else:
                        temp_df = pd.DataFrame(data={'Opcao': [str(i)], 'Tempo(ms)': [tempo]})
                        tempo_2_maquinas = tempo_2_maquinas.append(temp_df)


tempo_local = tempo_local.reset_index(drop=True)
tempo_2_maquinas = tempo_2_maquinas.reset_index(drop=True)

pdb.set_trace()