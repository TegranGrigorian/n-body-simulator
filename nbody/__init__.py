"""N-body gravitational simulator.

A high-performance physics simulator for gravitational n-body problems,
with a C++ backend and Python interface.
"""

from ._version import __version__

try:
    from ._nbody_core import Body, Kosmos, G_CONST, AU
except ImportError as e:
    raise ImportError(
        "Could not import C++ extension module. "
        "Please build the package with: pip install ."
    ) from e

__all__ = ["Body", "Kosmos", "G_CONST", "AU", "__version__"]
