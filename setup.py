from pathlib import Path
# setup file to compile C++ library
import setuptools
from setuptools import setup, Extension
import sys, os
import distutils

# from pybind11.setup_helpers import Pybind11Extension, build_ext
# print(sys.path)
sys.path = [os.path.dirname(os.path.abspath(sys.argv[0])) + '/bats'] + sys.path
# print(sys.path)
sys.path = sys.path[1:]
# print(sys.path)

this_dir = os.path.dirname(os.path.realpath(__file__))
# print(this_dir)

include_dirs = [
this_dir + '/include/',
this_dir + '/pybind11/include/'
]

print(include_dirs)

example_module = Extension(
    'example',
    ['rsa.cpp'],
    include_dirs=include_dirs,
    extra_compile_args=['-O3', '-std=c++17'],
    language='c++'
)

# rsa_module = Extension(
#     'example.rsa',
#     ['rsa.cpp'],
#     include_dirs=include_dirs,
#     extra_compile_args=['-O3', '-std=c++17'],
#     language='c++'
# )

setup(
    name='example',
    version=0.1,
    author='Yuan Luo',
    author_email='yuanluo@uchicago.edu',
    description='RSA project including modulus arithimetic',
    ext_modules=[example_module],
)