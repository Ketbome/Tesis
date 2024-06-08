import os
import csv
import pandas as pd

# Define the folders containing the log files
folders = [
    "hill-climbing-parallel"
]

# Define a function to convert log files to txt files and process them
def process_log_files(folder):
    log_file_path = os.path.join("..", folder, f"{folder}.log")

    # Process the .txt file and save the results to .csv file
    csv_file_path = f"{folder}.csv"
    with open(log_file_path, 'r') as f, open(csv_file_path, 'w', newline='') as csvfile:
        fieldnames = ['Seed', 'Solucion Empleada', 'Problema', 'Tiempo', 'Nodos']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()

        data = {'Solucion Empleada': folder.capitalize().replace("Joacapital", "JOA Capital")}
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
                data = {'Solucion Empleada': folder.capitalize().replace("Joacapital", "JOA Capital")}
    return csv_file_path

# Process all folders and collect csv file paths
csv_files = [process_log_files(folder) for folder in folders]

# Combine all CSV files into one and calculate averages
combined_df = pd.concat([pd.read_csv(csv_file) for csv_file in csv_files])

# Calculate averages
df_avg = combined_df.groupby(['Solucion Empleada', 'Problema']).agg({'Tiempo': 'mean', 'Nodos': 'mean'}).reset_index()

# Save the combined averages to a single CSV file
df_avg.to_csv('combined_averages.csv', index=False)

print("Averages calculated and saved to combined_averages.csv")

#docker-compose up simulated-annealing simulated-annealing-joa hill-climbing abstaylor -d --build
#docker-compose up hill-climbing-parallel -d --build
#docker-compose up simulated-annealing-parallel -d --build
#docker-compose up simulated-annealing-joa-parallel -d --build

