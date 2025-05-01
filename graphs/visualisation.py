import csv
import numpy as np
import matplotlib.pyplot as plt

matrix_results = {
    "dfs": [],
    "dijkstry": [],
    "bellman_ford": []
}

list_results = {
    "dfs": [],
    "dijkstry": [],
    "bellman_ford": []
}

OPERATIONS = list(matrix_results.keys())


SIZES = [10, 50, 100, 200]
DENSITIES = [0.25,0.50, 0.75, 1.0] # 

for operation in OPERATIONS:
    for size in SIZES:
        for density in DENSITIES:
            total_time = 0
            filename = f"results/{operation}_matrix_{size}_{density:.2f}.csv"

            with open(filename) as csvfile:
                reader = csv.reader(csvfile)

                for row in reader:
                    if row: 
                        total_time += float(row[0])

            mean_time = total_time / 100 
            matrix_results[operation].append(mean_time)

for operation in OPERATIONS:
    for size in SIZES:
        for density in DENSITIES:
            total_time = 0
            filename = f"results/{operation}_list_{size}_{density:.2f}.csv"

            with open(filename) as csvfile:
                reader = csv.reader(csvfile)

                for row in reader:
                    if row: 
                        total_time += float(row[0])

            mean_time = total_time / 100 
            list_results[operation].append(mean_time)

def plot_comparison_for_operation(matrix_results, list_results, operation, SIZES):
    TITLES = {
    "dfs": "Algorytm DFS",
    "dijkstry": "Algorytm Dijkstry",
    "bellman_ford": "Algorytm Bellmana-Forda",
    }

    plt.figure(figsize=(10, 6))

    matrix_times = matrix_results.get(operation, [])
    list_times = list_results.get(operation, [])
    

    if not matrix_times or not list_times:
        return  
    
    plt.plot(SIZES, matrix_times, label=f'Macierz sąsiedztwa', marker='o', color='#fc0356')
    
    plt.plot(SIZES, list_times, label=f'Lista sąsiedztwa', marker='o', color='#0318fc')
    

    title = TITLES.get(operation, operation)

    plt.title(f'Porównanie operacji {title} ')
    plt.xlabel('Rozmiar zbioru')
    plt.ylabel('Średni czas wykonania [ns]')
    #plt.xscale("log")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)

    plt.legend()
    plt.grid(True)
    
    plt.show()


for operation in OPERATIONS:
    plot_comparison_for_operation(matrix_results, list_results, operation, SIZES)