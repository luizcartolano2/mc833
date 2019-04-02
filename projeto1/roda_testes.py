import os
import pdb
import pandas as pd
import re

# entra com o IP se quiser
redes = ['localhost', '177.220.85.54']
d = {'Opcao': [], 'Tempo(ms)': []}
tempo_local = pd.DataFrame(data=d)
tempo_2_maquinas = pd.DataFrame(data=d)

for rede in redes:
    for i in range(1,7):
        for k in range(0,25):
            linha_executavel = './client ' + rede + ' < input' + str(i) + ' > temp.txt'
            os.system(linha_executavel)
            f = open("temp.txt","r+", encoding="ISO-8859-1")
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
            f.truncate(0)

tempo_local = tempo_local.reset_index(drop=True)
tempo_2_maquinas = tempo_2_maquinas.reset_index(drop=True)
tempo_server = []

input("Pressione alguma coisa")

s_f = open("server.txt","r+", encoding="ISO-8859-1")
content = s_f.readlines()
for x in content:
    if 'Tempo servidor:' in x:
        tempo = str(x[x.find(':')+1 : -1])
        tempo = tempo.strip()
        tempo_server.append(tempo)

for rede in redes:
    if rede == 'Localhost':
        tempo_local['Tempo Server'] = tempo_server
    else:
        pass

tempo_local.to_csv('local.csv',sep=';')
tempo_2_maquinas.to_csv('naolocal.csv',sep=';')
