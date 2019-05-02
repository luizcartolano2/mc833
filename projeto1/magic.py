import pandas as pd
import numpy as np
import pdb
import matplotlib.pyplot as plt
import math
import scipy.stats

# first we read the dfs
tempo_localhost = pd.read_csv('resultados/local.csv', sep=';', converters={'Tempo(ms)': float, 'Tempo Server': float, 'Tempo Comunicacao': float}).drop(['Unnamed: 0'],axis=1)
tempo_2_maquinas = pd.read_csv('resultados/nao_local.csv', sep=';', converters={'Tempo(ms)': float, 'Tempo Server': float, 'Tempo Comunicacao': float}).drop(['Unnamed: 0'],axis=1)

# s_f = open("server.txt","r+", encoding="ISO-8859-1")
# content = s_f.readlines()
# tempo_server = []
# for x in content:
#     if 'Tempo servidor:' in x:
#         tempo = str(x[x.find(':')+1 : -1])
#         tempo = tempo.strip()
#         tempo_server.append(float(tempo))
#
# tempo_2_maquinas['Tempo Server'] = tempo_server
#
# tempo_localhost['Tempo Comunicacao'] = tempo_localhost['Tempo(ms)'] - tempo_localhost['Tempo Server']
# tempo_2_maquinas['Tempo Comunicacao'] = tempo_2_maquinas['Tempo(ms)'] - tempo_2_maquinas['Tempo Server']
#
# tempo_localhost.to_csv('local.csv', sep=';')
# tempo_2_maquinas.to_csv('nao_local.csv', sep=';')

d = {'Opcao':[], 'Media':[], 'Desvio': [], 'Intervalo de confianca': [], 'Tipo':[]}
resultao_total = pd.DataFrame(data=d)
resultao_comunicacao = pd.DataFrame(data=d)

redes = ['localhost', 'ip']
for rede in redes:
    for i in range(1,7):
        if rede == 'localhost':
            temp = tempo_localhost[tempo_localhost['Opcao'] == i]
        else:
            temp = tempo_2_maquinas[tempo_2_maquinas['Opcao'] == i]

        tempo_total = temp['Tempo(ms)']
        media_total = temp['Tempo(ms)'].mean()
        desvio_total = temp['Tempo(ms)'].std()

        tempo_comunicacao = temp['Tempo Comunicacao']
        media_comunicacao = temp['Tempo Comunicacao'].mean()
        desvio_comunicacao = temp['Tempo Comunicacao'].std()

        intervalo_confianca_total = '(' + str(media_total - (1.96 * (desvio_total/math.sqrt(len(tempo_total))))) + ',' + str(media_total + (1.96 * (desvio_total/math.sqrt(len(tempo_total))))) + ')'
        intervalo_confianca_comunicacao  = '(' + str(media_comunicacao - (1.96 * (desvio_comunicacao/math.sqrt(len(tempo_comunicacao))))) + ',' + str(media_comunicacao + (1.96 * (desvio_comunicacao/math.sqrt(len(tempo_comunicacao))))) + ')'

        temp = pd.DataFrame(data={'Opcao':[str(i)], 'Media':[str(media_total)], 'Desvio': [str(desvio_total)], 'Intervalo de confianca': [intervalo_confianca_total], 'Tipo':[rede]})
        resultao_total = resultao_total.append(temp)

        temp = pd.DataFrame(data={'Opcao':[str(i)], 'Media':[str(media_comunicacao)], 'Desvio': [str(desvio_comunicacao)], 'Intervalo de confianca': [intervalo_confianca_comunicacao], 'Tipo':[rede]})
        resultao_comunicacao = resultao_comunicacao.append(temp)

        fig = plt.figure()
        tempo_total.hist(bins=10)
        # fig.suptitle('Tempo total gasto - Opcao ' + str(i))
        plt.xlabel('Tempo')
        plt.ylabel('Frequencia')
        fig.savefig('novos_graficos/tempo_total_' + rede + '_opcao' + str(i) + '.png')

        fig = plt.figure()
        tempo_comunicacao.hist(bins=10)
        #fig.suptitle('Tempo de Comunicacao - Opcao ' + str(i))
        plt.xlabel('Tempo')
        plt.ylabel('Frequencia')
        fig.savefig('novos_graficos/tempo_comunicacao_' + rede + '_opcao' + str(i) + '.png')


# resultao_total.to_csv('Resultado_total.csv', sep=';')
# resultao_comunicacao.to_csv('resultao_comunicacao.csv', sep=';')
