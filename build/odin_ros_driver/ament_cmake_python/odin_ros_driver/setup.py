from setuptools import find_packages
from setuptools import setup

setup(
    name='odin_ros_driver',
    version='0.14.2',
    packages=find_packages(
        include=('odin_ros_driver', 'odin_ros_driver.*')),
)
