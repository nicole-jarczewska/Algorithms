import csv
import numpy as np
import matplotlib.pyplot as plt

matrix_results_size = {
    "dfs": [],
    "dijkstry": [],
    "bellman_ford": []
}

list_results_size = {
    "dfs": [],
    "dijkstry": [],
    "bellman_ford": []
}

matrix_results_density = {
    "dfs": [],
    "dijkstry": [],
    "bellman_ford": []
}

list_results_density = {
    "dfs": [],
    "dijkstry": [],
    "bellman_ford": []
}

OPERATIONS = list(matrix_results_size.keys())

SIZES = [10, 50, 100, 200, 500]
DENSITIES = [0.25, 0.50, 0.75, 1.0] 

SIZE = 200
DENSITY = 0.50

for operation in OPERATIONS:
    for size in SIZES:
            total_time = 0
            filename = f"results/{operation}_matrix_{size}_{DENSITY:.2f}.csv"

            with open(filename) as csvfile:
                reader = csv.reader(csvfile)

                for row in reader:
                    if row: 
                        total_time += float(row[0])

            mean_time = total_time / 100 /1000000
            matrix_results_size[operation].append(mean_time)

for operation in OPERATIONS:
    for density in DENSITIES:
            total_time = 0
            filename = f"results/{operation}_matrix_{SIZE}_{density:.2f}.csv"

            with open(filename) as csvfile:
                reader = csv.reader(csvfile)

                for row in reader:
                    if row: 
                        total_time += float(row[0])

            mean_time = total_time / 100 /1000000
            matrix_results_density[operation].append(mean_time)

for operation in OPERATIONS:
    for size in SIZES:
            total_time = 0
            filename = f"results/{operation}_list_{size}_{density:.2f}.csv"

            with open(filename) as csvfile:
                reader = csv.reader(csvfile)

                for row in reader:
                    if row: 
                        total_time += float(row[0])

            mean_time = total_time / 100 /1000000
            list_results_size[operation].append(mean_time)

for operation in OPERATIONS:
    for density in DENSITIES:
            total_time = 0
            filename = f"results/{operation}_list_{SIZE}_{density:.2f}.csv"

            with open(filename) as csvfile:
                reader = csv.reader(csvfile)

                for row in reader:
                    if row: 
                        total_time += float(row[0])

            mean_time = total_time / 100 /1000000
            list_results_density[operation].append(mean_time)


TITLES = {
    "dfs": "algorytmu DFS",
    "dijkstry": "algorytmu Dijkstry",
    "bellman_ford": "algorytmu Bellmana-Forda",
    }

def plot_comparison_for_operation(matrix_results, list_results, operation, PARAMETERS):
    plt.figure(figsize=(10, 6))

    matrix_times = matrix_results.get(operation, [])
    list_times = list_results.get(operation, [])
    

    if not matrix_times or not list_times:
        return  
    
    plt.plot(PARAMETERS, matrix_times, label=f'Macierz sąsiedztwa', marker='o', color='#fc0356')
    
    plt.plot(PARAMETERS, list_times, label=f'Lista sąsiedztwa', marker='o', color='#0318fc')
    

    title = TITLES.get(operation, operation)

    plt.title(f'Porównanie {title}')
    plt.xlabel('Rozmiar grafu')
    plt.ylabel('Średni czas wykonania [ms]')
    #plt.xscale("log")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)

    plt.legend()
    plt.grid(True)
    
    plt.show()


for operation in OPERATIONS:
    plot_comparison_for_operation(matrix_results_size, list_results_size, operation, SIZES)

for operation in OPERATIONS:
    plot_comparison_for_operation(matrix_results_density, list_results_density, operation, DENSITIES)