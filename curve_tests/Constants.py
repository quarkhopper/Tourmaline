from enum import Enum
from typing import *



class Columns(str, Enum):
    TIME = "t"
    EM_POS = "scopeInclRelSigned"
    IDM_POS = "actualPos14"
    IDM_FORCE = "actualForce14"
    PLANE = "targetPlane"
    ART = "targetIncl"