from distutils.core import setup, Extension
from os import path
from glob import glob


def split(_path: str):
    return _path.split(';')


source_files = glob(path.join(path.dirname(path.realpath(__file__)), "*.cpp"))

qt_include = map(split, ['${Qt5Core_INCLUDE_DIRS}', '${Qt5Gui_INCLUDE_DIRS}'])
stg_extension = Extension('${PROJECT_NAME}',
                          include_dirs=['${CMAKE_SYSTEM_INCLUDE_PATH}', '${Stg_SOURCE_DIR}'] + sum(qt_include, []),
                          library_dirs=['${CMAKE_SYSTEM_LIBRARY_PATH}', '${Stg_BINARY_DIR}'],
                          libraries=['Stg', 'Qt5Core', 'Qt5Gui'],
                          sources=source_files)

if __name__ == '__main__':
    setup(name='${PROJECT_NAME}',
          version='${PROJECT_VERSION}',
          description='',
          author='',
          author_email='',
          url='https://github.com/iccet/stego',
          long_description='''''',
          ext_modules=[stg_extension])
