import csv
import os
import matplotlib.pyplot as plt

ALGORYTHM = ["dfs", "dijkstry", "bellman_ford"]
SIZES = [10, 50, 100, 200, 500]
DENSITIES = [0.25, 0.50, 0.75, 1.0]
FIXED_SIZE = 100
FIXED_DENSITY = 1.0

TITLES = {
    "dfs": "Algorytm DFS",
    "dijkstry": "Algorytm Dijkstry",
    "bellman_ford": "Algorytm Bellmana-Forda",
}

os.makedirs("plots", exist_ok=True)

# Store results
matrix_size = {op: [] for op in ALGORYTHM}
list_size = {op: [] for op in ALGORYTHM}
matrix_density = {op: [] for op in ALGORYTHM}
list_density = {op: [] for op in ALGORYTHM}

def read_mean_time(filepath):
    try:
        total_time = 0
        with open(filepath) as f:
            reader = csv.reader(f)
            for row in reader:
                if row:
                    total_time += float(row[0])
        return total_time / 100 / 1_000_000 
    except FileNotFoundError:
        print(f"[Missing] {filepath}")
        return 0

# --- Load data ---
for op in ALGORYTHM:
    for size in SIZES:
        matrix_file = f"results/{op}_matrix_{size}_{FIXED_DENSITY:.2f}.csv"
        list_file = f"results/{op}_list_{size}_{FIXED_DENSITY:.2f}.csv"
        matrix_size[op].append(read_mean_time(matrix_file))
        list_size[op].append(read_mean_time(list_file))

    for density in DENSITIES:
        matrix_file = f"results/{op}_matrix_{FIXED_SIZE}_{density:.2f}.csv"
        list_file = f"results/{op}_list_{FIXED_SIZE}_{density:.2f}.csv"
        matrix_density[op].append(read_mean_time(matrix_file))
        list_density[op].append(read_mean_time(list_file))

def plot_structure_comparison(x_vals, y_matrix, y_list, op, x_label, title_suffix, file_suffix):
    plt.figure(figsize=(10, 6))
    plt.plot(x_vals, y_matrix, label="Macierz sąsiedztwa", marker='o', color="#fc0356")
    plt.plot(x_vals, y_list, label="Lista sąsiedztwa", marker='o', color="#0318fc")
    plt.title(f"{TITLES[op]} – {title_suffix}")
    plt.xlabel(x_label)
    plt.ylabel("Średni czas wykonania [ms]")
    plt.grid(True, linestyle="--", linewidth=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"plots/{op}_{file_suffix}.png")
    plt.close()

for op in ALGORYTHM:
    plot_structure_comparison(SIZES, matrix_size[op], list_size[op], op,
                              "Rozmiar grafu", f"dla grafu o gęstości {int(FIXED_DENSITY*100)}%", "size")
    
    plot_structure_comparison(DENSITIES, matrix_density[op], list_density[op], op,
                              "Gęstość grafu", f"dla grafu o {FIXED_SIZE} wierzchołkach", "density")


def plot_densities_by_structure(structure_type, op):
    plt.figure(figsize=(10, 6))

    for density in DENSITIES:
        times = []
        for size in SIZES:
            filename = f"results/{op}_{structure_type}_{size}_{density:.2f}.csv"
            times.append(read_mean_time(filename))
        
        plt.plot(SIZES, times, marker='o', label=f"Gęstość {int(density*100)}%")

    title = f"{TITLES[op]} – {('dla macierzy sąsiedztwa' if structure_type == 'matrix' else 'dla listy sąsiedztwa')}"
    plt.title(title)
    plt.xlabel("Rozmiar grafu")
    plt.ylabel("Średni czas wykonania [ms]")
    plt.grid(True, linestyle="--", linewidth=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"plots/{op}_{structure_type}_densities.png")
    plt.close()

for op in ALGORYTHM:
    plot_densities_by_structure("matrix", op)
    plot_densities_by_structure("list", op)