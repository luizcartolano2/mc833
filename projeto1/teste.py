import pandas as pd
import numpy as np
import pdb
import matplotlib.pyplot as plt
import math
import scipy.stats

# first we read the dfs
tempo_localhost = pd.read_csv('local.csv', sep=';', converters={'Tempo(ms)': float, 'Tempo Server': float}).drop(['Unnamed: 0'],axis=1)
tempo_localhost['Tempo Comunicacao'] = tempo_localhost['Tempo(ms)'] - tempo_localhost['Tempo Server']

for i in range(1,7):
    temp = tempo_localhost[tempo_localhost['Opcao'] == i]
    tempo_total = temp['Tempo(ms)']
    media_total = temp['Tempo(ms)'].mean()
    desvio_total = temp['Tempo(ms)'].std()

    tempo_comunicacao = temp['Tempo Comunicacao']
    media_comunicacao = temp['Tempo Comunicacao'].mean()
    desvio_comunicacao = temp['Tempo Comunicacao'].std()

    intervalo_confianca_total = '(' + str(media_total - (1.96 * (desvio_total/math.sqrt(len(tempo_total))))) + ',' + str(media_total + (1.96 * (desvio_total/math.sqrt(len(tempo_total))))) + ')'
    intervalo_confianca_comunicacao  = '(' + str(media_comunicacao - (1.96 * (desvio_comunicacao/math.sqrt(len(tempo_comunicacao))))) + ',' + str(media_comunicacao + (1.96 * (desvio_comunicacao/math.sqrt(len(tempo_comunicacao))))) + ')'

    fig = plt.figure()
    tempo_total.hist(bins=90)
    plt.plot(x_total)
    fig.suptitle('Tempo total gasto')
    plt.xlabel('Tempo')
    plt.ylabel('Frequencia')
    fig.savefig('tempo_total_opcao' + str(i) + '.png')

    fig = plt.figure()
    tempo_comunicacao.hist(bins=90)
    fig.suptitle('Tempo de Comunicacao')
    plt.xlabel('Tempo')
    plt.ylabel('Frequencia')
    fig.savefig('tempo_comunicacao_opcao' + str(i) + '.png')

    pdb.set_trace()
