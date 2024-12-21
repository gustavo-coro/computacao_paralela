import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Simulate reading data (replace with actual CSV file)
data = pd.read_csv("testes/dense/time_dense.csv", sep=";")

# Calculate speedups
data["OMP 2 THREADS Speedup"] = data["Sequential Time"] / data["OMP 2 THREADS"]
data["OMP 3 THREADS Speedup"] = data["Sequential Time"] / data["OMP 3 THREADS"]
data["OMP 4 THREADS Speedup"] = data["Sequential Time"] / data["OMP 4 THREADS"]

data = data.sort_values(by='Sequential Time', ascending=False)

# Create a new DataFrame for the speedup table
speedup_table = data[["Nodes", "Edges", "OMP 2 THREADS Speedup", "OMP 3 THREADS Speedup", "OMP 4 THREADS Speedup"]]

speedup_table = speedup_table.head(20)

# Plot the table as an image
fig, ax = plt.subplots(figsize=(8, 3))
sns.heatmap(speedup_table.set_index(["Nodes", "Edges"]), annot=True, fmt=".2f", cmap="Blues", cbar=False, ax=ax)
ax.set_title("Speedup Table")
plt.tight_layout()

# Save as an image file and display
output_path = "peedup_table.png"
plt.savefig(output_path)
plt.show()
