# Silver Nanoparticle Water Purification Simulation
# Author: Ayush Mahanta

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


initial_bacteria = 1_000_000
concentrations = [0, 5, 10, 15, 20] 


def reduction_percentage(conc):
    max_efficiency = 96 
    efficiency = max_efficiency * (1 - np.exp(-0.25 * conc))
    return efficiency


data = []
for conc in concentrations:
    reduction = reduction_percentage(conc)
    
    noise = np.random.uniform(-5, 5)
    reduction_noisy = max(0, min(100, reduction + noise))
    final_bacteria = initial_bacteria * (1 - reduction_noisy / 100)
    data.append([conc, initial_bacteria, int(final_bacteria), round(reduction_noisy, 2)])


df = pd.DataFrame(data, columns=[
    "Concentration (mg/L)",
    "Initial Bacteria Count (CFU/mL)",
    "Final Bacteria Count (CFU/mL)",
    "% Reduction"
])

df.to_csv("silver_nanoparticle_water_purification.csv", index=False)

print(df)


plt.figure(figsize=(6,4))
plt.plot(df["Concentration (mg/L)"], df["% Reduction"], marker='o')
plt.title("Effect of AgNP Concentration on Bacterial Reduction")
plt.xlabel("Concentration (mg/L)")
plt.ylabel("Bacterial Reduction (%)")
plt.grid(True)
plt.savefig("reduction_graph.png", dpi=300)
plt.show()

plt.figure(figsize=(6,4))
plt.plot(df["Concentration (mg/L)"], df["Final Bacteria Count (CFU/mL)"], marker='o', color='red')
plt.title("Final Bacteria Count vs AgNP Concentration")
plt.xlabel("Concentration (mg/L)")
plt.ylabel("Final Bacteria Count (CFU/mL)")
plt.grid(True)
plt.savefig("final_bacteria_graph.png", dpi=300)
plt.show()
