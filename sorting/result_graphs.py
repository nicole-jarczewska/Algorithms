import csv
import numpy as np
import matplotlib.pyplot as plt


Heapsort = []
Timsort = []
Introsort = []

sorting_algorythm = ["heapsort", "timsort", "introsort"]
filename_start = [1000, 10000, 50000, 100000, 500000, 1000000]
filename_end = [0.000, 0.250, 0.500, 0.750, 0.950, 0.990, 0.997, 1.000, 2.000]

for sort in sorting_algorythm:
    for i in filename_end:
        sort_mean = []

        for j in filename_start:
            sum = 0
            filename = f"results/{sort}_{j}_{i:.3f}.csv"

            with open(filename) as csvfile:
                spamreader = csv.reader(csvfile, delimiter=';', quotechar='|')

                for row in spamreader:
                        sum+=float(row[0])

            sort_mean.append(sum / 100)

        if sort == "heapsort":
            Heapsort.append(sort_mean)
        elif sort == "timsort":
            Timsort.append(sort_mean)
        elif sort == "introsort":
            Introsort.append(sort_mean)


plot_percentage = [0, 25, 50, 75, 95, 99, 99.7, 100, 200]

print(Heapsort)
print(Timsort)
print(Introsort)

# heapsort
plt.figure(figsize=(8, 5))
for i, values in zip(plot_percentage, Heapsort):
    filtered_sizes = [x for x, y in zip(filename_start, values) if y is not None]
    filtered_times = [y for y in values if y is not None]
    if(i == 200):
         plt.plot(filtered_sizes, filtered_times, marker='o', linestyle='-', label=f"% posortowanych elementów = 100%(malejąco)")
    else:
        plt.plot(filtered_sizes, filtered_times, marker='o', linestyle='-', label=f"% posortowanych elementów = {i}%")

plt.xlabel("Rozmiar tablicy")
plt.ylabel("Średni czas wykonania [ms]")
plt.title("Sortowanie przez kopcowanie")
plt.xscale("log")
#plt.yscale("log")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("heapsort.pdf")
plt.show()

# timsort
plt.figure(figsize=(8, 5))
for i, values in zip(plot_percentage, Timsort):
    filtered_sizes = [x for x, y in zip(filename_start, values) if y is not None]
    filtered_times = [y for y in values if y is not None]
    if(i == 200):
         plt.plot(filtered_sizes, filtered_times, marker='o', linestyle='-', label=f"% posortowanych elementów = 100%(malejąco)")
    else:
        plt.plot(filtered_sizes, filtered_times, marker='o', linestyle='-', label=f"% posortowanych elementów = {i}%")

plt.xlabel("Rozmiar tablicy")
plt.ylabel("Średni czas wykonania [ms]")
plt.title("Timsort")
plt.xscale("log")
#plt.yscale("log")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("timsort.pdf")
plt.show()

# introsort
plt.figure(figsize=(8, 5))
for i, values in zip(plot_percentage, Introsort):
    filtered_sizes = [x for x, y in zip(filename_start, values) if y is not None]
    filtered_times = [y for y in values if y is not None]
    if(i == 200):
         plt.plot(filtered_sizes, filtered_times, marker='o', linestyle='-', label=f"% posortowanych elementów = 100%(malejąco)")
    else:
        plt.plot(filtered_sizes, filtered_times, marker='o', linestyle='-', label=f"% posortowanych elementów = {i}%")

plt.xlabel("Rozmiar tablicy")
plt.ylabel("Średni czas wykonania [ms]")
plt.title("Introsort")
plt.xscale("log")
#plt.yscale("log")
plt.legend()
plt.grid(True, which="both", linestyle="-", linewidth=0.5)
plt.savefig("introsort.pdf")
plt.show()

plt.figure(figsize=(8, 5))

plt.plot(filename_start, Heapsort[0], marker='o', linestyle='-', label="Heapsort")
plt.plot(filename_start, Timsort[0], marker='s', linestyle='-', label="Timsort")
plt.plot(filename_start, Introsort[0], marker='d', linestyle='-', label="Introsort")

plt.xlabel("Rozmiar tablicy")
plt.ylabel("Średni czas wykonania [ms]")
plt.title("Porównanie algorytmów, gdy 0% elementów jest posortowanych")
plt.xscale("log")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("comparison0.pdf")
plt.show()

plt.figure(figsize=(8, 5))

plt.plot(filename_start, Heapsort[2], marker='o', linestyle='-', label="Heapsort")
plt.plot(filename_start, Timsort[2], marker='s', linestyle='-', label="Timsort")
plt.plot(filename_start, Introsort[2], marker='d', linestyle='-', label="Introsort")

plt.xlabel("Rozmiar tablicy")
plt.ylabel("Średni czas wykonania [ms]")
plt.title("Porównanie algorytmów, gdy 50% elementów jest posortowanych")
plt.xscale("log")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("comparison50.pdf")
plt.show()

plt.figure(figsize=(8, 5))

plt.plot(filename_start, Heapsort[7], marker='o', linestyle='-', label="Heapsort")
plt.plot(filename_start, Timsort[7], marker='s', linestyle='-', label="Timsort")
plt.plot(filename_start, Introsort[7], marker='d', linestyle='-', label="Introsort")

plt.xlabel("Rozmiar tablicy")
plt.ylabel("Średni czas wykonania [ms]")
plt.title("Porównanie algorytmów, gdy 100% elementów jest posortowanych")
plt.xscale("log")
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.savefig("comparison100.pdf")
plt.show()