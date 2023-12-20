import csv
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.backends.backend_pdf import PdfPages


class Graph:

    def __init__(self):

        self.count = np.array([])
        self.time = np.array([])

    def readFile(self, fileName):
        with open(fileName) as file:
            spamreader = csv.reader(file, delimiter=',')
            for values in spamreader:
                self.count = np.append(self.count, int(values[0]))
                self.time = np.append(self.time, float(values[1]))

    def buildGraph(self):
        with PdfPages('./measures.pdf') as pdf:
            fig = plt.figure(figsize=(12, 8))
            splt = fig.add_subplot()
            plt.xlabel("Препятствия (кол.)")
            plt.ylabel("Время генерации кадра (мкс)")

            splt.plot(self.count, self.time, color="purple", marker="D", linestyle="--", linewidth=2) 
            splt.grid(True, linestyle='--', linewidth=0.5, color='gray')
            splt.grid(True)

            pdf.savefig()

            plt.close()


if __name__ == "__main__":

    files = ['measures.csv']

    for file in files:
        graph = Graph()
        graph.readFile(file)
        graph.buildGraph()
