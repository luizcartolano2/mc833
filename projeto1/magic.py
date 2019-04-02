import pandas as pd
import numpy as np
import pdb

# first we read the dfs
tempo_localhost = pd.read_csv('local.csv', sep=';', converters={'Tempo(ms)': float, 'Tempo server': float}).drop(['Unnamed: 0'],axis=1)
tempo_2_maquinas = pd.read_csv('nao_local.csv', sep=';', converters={'Tempo(ms)': float}).drop(['Unnamed: 0'],axis=1)

s_f = open("server.txt","r+", encoding="ISO-8859-1")
content = s_f.readlines()
tempo_server = []
for x in content:
    if 'Tempo servidor:' in x:
        tempo = str(x[x.find(':')+1 : -1])
        tempo = tempo.strip()
        tempo_server.append(float(tempo))

tempo_2_maquinas['Tempo Server'] = tempo_server

tempo_localhost['Tempo Comunicacao'] = tempo_localhost['Tempo(ms)'] - tempo_localhost['Tempo server']
tempo_2_maquinas['Tempo Comunicacao'] = tempo_2_maquinas['Tempo(ms)'] - tempo_2_maquinas['Tempo Server']

pdb.set_trace()
