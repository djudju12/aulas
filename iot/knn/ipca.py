import pandas as pd
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

def ipca(num_intervals, file_name):
    # Load data from file
    data = pd.read_csv(file_name)

    # Split data into intervals
    interval_size = len(data) // num_intervals
    intervals = [data[i:i+interval_size] for i in range(0, len(data), interval_size)]

    # Perform PCA on each interval and plot the results
    for i, interval in enumerate(intervals):
        pca = PCA(n_components=4)
        pca.fit(interval)
        transformed_data = pca.transform(interval)

        # Plot the transformed data
        fig, axs = plt.subplots(2, 2)
        fig.suptitle(f"Interval {i+1}")
        axs[0, 0].scatter(transformed_data[:, 0], transformed_data[:, 1])
        axs[0, 0].set_title("PC1 vs PC2")
        axs[0, 1].scatter(transformed_data[:, 0], transformed_data[:, 2])
        axs[0, 1].set_title("PC1 vs PC3")
        axs[1, 0].scatter(transformed_data[:, 0], transformed_data[:, 3])
        axs[1, 0].set_title("PC1 vs PC4")
        axs[1, 1].scatter(transformed_data[:, 1], transformed_data[:, 2])
        axs[1, 1].set_title("PC2 vs PC3")
        plt.show()