import matplotlib

matplotlib.use("Qt5Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

from Constants import *
from Curve import Curve

if __name__ == "__main__":

    df = pd.read_csv(r"data/plot_data.csv")
    df = df.dropna()
    df = df[df[Columns.PLANE].astype(str) == "0"]

    raw_points = {}
    for i, row in df.iterrows():
        art = abs(row[Columns.ART])
        if art not in raw_points.keys():
            raw_points[art] = ([], [])
        y = row[Columns.EM_POS]
        raw_points[art][0].append(i)
        raw_points[art][1].append(y)

    base_curves = {}
    for art, points in raw_points.items():
        curve = Curve(curve_tuple=raw_points[art])
        base_curves[art] = curve

    plt.figure()
    plt.title("Base")
    for art, curve in base_curves.items():
        plt.plot(curve.x, curve.y)
    plt.show()
