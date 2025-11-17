from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext
import sys

__version__ = "0.1.0"

# C++ source files
ext_modules = [
    Pybind11Extension(
        "nbody._nbody_core",
        [
            "src/bindings.cpp",
            "src/body/body.cpp",
            "src/kosmos/kosmos.cpp",
        ],
        include_dirs=["src"],
        cxx_std=11,
        define_macros=[("VERSION_INFO", __version__)],
    ),
]

setup(
    name="nbody-simulator",
    version=__version__,
    author="Tegran Grigorian",
    author_email="tegrgrigor@gmail.com",
    description="High-performance N-body gravitational simulator",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    packages=["nbody"],
    python_requires=">=3.7",
    install_requires=[
        "pybind11>=2.10.0",
        "numpy>=1.20.0",
    ],
    zip_safe=False,
)
