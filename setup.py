from setuptools import setup, Extension

module = Extension('hermes',
                   sources=['src/hermes.c'],
                   extra_compile_args=['-std=c99'])

setup(
    name='Hermes',
    version='1.0',
    description='Hermes --> Tool for Interacting and extracting data from the SHM',
    ext_modules=[module],
    packages=['hermes']
)

