import csv

with open('commands2.txt', 'r') as f, open('output2.csv', 'w', newline='') as csvfile:
    fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    data = {'Solucion Empleada': 'Simulates Annealing'}
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
            data = {'Solucion Empleada': 'Simulates Annealing'}
