import csv

with open('100itpow07not.log', 'r') as f, open('100itpow07not.csv', 'w', newline='') as csvfile:
    fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    data = {'Solucion Empleada': 'Simu 70 iteraciones pow 0.7'}
    for line in f:
        if "random seed:" in line:
            data['Seed'] = line.split()[-1]
        elif "file loaded:" in line:
            data['Problema'] = line.split('/')[-1].split('.')[0]
        elif "cpu time used:" in line:
            data['Tiempo'] = line.split()[-1][:-1]  # remove 's' from the end
        elif "number of cells:" in line:
            data['Nodos'] = line.split()[-1]
            writer.writerow(data)  # write data to csv and reset for next set
            data = {'Solucion Empleada': 'Simu 70 iteraciones pow 0.7'}

# Path: Data/average.py
import pandas as pd

# Leer el archivo CSV
df = pd.read_csv('100itpow07not.csv')

# Agrupar por nombre del problema y calcular promedios
df_avg = df.groupby('Problema').agg({'Tiempo': 'mean', 'Nodos': 'mean'})

# Guardar en un nuevo archivo CSV
df_avg.to_csv('100itpow07notmean.csv')
