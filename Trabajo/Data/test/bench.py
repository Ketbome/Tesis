import csv

with open('25it.log', 'r') as f, open('25it.csv', 'w', newline='') as csvfile:
    fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    data = {'Solucion Empleada': 'Simu 25 iteraciones'}
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
            data = {'Solucion Empleada': 'Simu 25 iteraciones'}

with open('50it.log', 'r') as f, open('50it.csv', 'w', newline='') as csvfile:
    fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    data = {'Solucion Empleada': 'Simu 50 iteraciones'}
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
            data = {'Solucion Empleada': 'Simu 50 iteraciones'}

with open('75it.log', 'r') as f, open('75it.csv', 'w', newline='') as csvfile:
    fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    data = {'Solucion Empleada': 'Simu 75 iteraciones'}
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
            data = {'Solucion Empleada': 'Simu 75 iteraciones'}

with open('100it.log', 'r') as f, open('100it.csv', 'w', newline='') as csvfile:
    fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    data = {'Solucion Empleada': 'Simu 100 iteraciones'}
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
            data = {'Solucion Empleada': 'Simu 100 iteraciones'}

with open('200it.log', 'r') as f, open('200it.csv', 'w', newline='') as csvfile:
    fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    data = {'Solucion Empleada': 'Simu 200 iteraciones'}
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
            data = {'Solucion Empleada': 'Simu 200 iteraciones'}

# Path: Data/average.py
import pandas as pd

# Leer el archivo CSV
df = pd.read_csv('25it.csv')

# Agrupar por nombre del problema y calcular promedios
df_avg = df.groupby('Problema').agg({'Tiempo': 'mean', 'Nodos': 'mean'})

# Guardar los resultados en un nuevo archivo CSV
df_avg.to_csv('25itmean.csv')

# Leer el archivo CSV
df = pd.read_csv('50it.csv')

# Agrupar por nombre del problema y calcular promedios
df_avg = df.groupby('Problema').agg({'Tiempo': 'mean', 'Nodos': 'mean'})

# Guardar los resultados en un nuevo archivo CSV
df_avg.to_csv('50itmean.csv')

# Leer el archivo CSV
df = pd.read_csv('75it.csv')

# Agrupar por nombre del problema y calcular promedios
df_avg = df.groupby('Problema').agg({'Tiempo': 'mean', 'Nodos': 'mean'})

# Guardar los resultados en un nuevo archivo CSV
df_avg.to_csv('75itmean.csv')

# Leer el archivo CSV
df = pd.read_csv('100it.csv')

# Agrupar por nombre del problema y calcular promedios
df_avg = df.groupby('Problema').agg({'Tiempo': 'mean', 'Nodos': 'mean'})

# Guardar los resultados en un nuevo archivo CSV
df_avg.to_csv('100itmean.csv')

# Leer el archivo CSV
df = pd.read_csv('200it.csv')

# Agrupar por nombre del problema y calcular promedios
df_avg = df.groupby('Problema').agg({'Tiempo': 'mean', 'Nodos': 'mean'})

# Guardar los resultados en un nuevo archivo CSV
df_avg.to_csv('200itmean.csv')
