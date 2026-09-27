from setuptools import find_packages
from setuptools import setup

setup(
    name='super_lio',
    version='2.0.0',
    packages=find_packages(
        include=('super_lio', 'super_lio.*')),
)
