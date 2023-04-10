from typing import *

CurveTuple = Tuple[List[float], List[float]]
CurvePoint = Tuple[float, float]
CurveList = List[CurvePoint]


class Curve:
    def __init__(
        self,
        curve: Optional["Curve"] = None,
        curve_tuple: Optional[CurveTuple] = None,
        curve_list: Optional[CurveList] = None,
    ):
        self.points: List[CurvePoint] = []
        if curve is not None:
            self.points = curve.points
        if curve_tuple is not None:
            for i, x in enumerate(curve_tuple[0]):
                y = curve_tuple[1][i]
                self.points.append((x, y))
        if curve_list is not None:
            self.points = curve_list
        self._as_tuple: Optional[CurveTuple] = None
        self._r_square: Optional[CurveTuple] = None

    @property
    def as_tuple(self):
        if self._as_tuple is None:
            self._as_tuple = [p[0] for p in self.points], [p[1] for p in self.points]
        return self._as_tuple

    def r_square(self):
        if self._r_square is None:

        return self._r_square


