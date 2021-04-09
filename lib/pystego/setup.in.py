from typing import List

from distutils.core import setup, Extension
import sysconfig
from os import path
from glob import glob


def remove_namespace(f):
    def wrapper(p: str):
        return f(p.replace('::', ''))

    return wrapper


@remove_namespace
def split(_path: str) -> List[str]:
    return _path.split(';')


source_files = glob(path.join(path.dirname(path.realpath(__file__)), "*.cpp"))
libraries = split('${LINKED_LIBRARIES}')
extra_compile_args = ["-std=c++${CMAKE_CXX_STANDARD}"] + "${CMAKE_CXX_FLAGS}".strip().split(' ')
qt_include = map(split, ['${Qt5Core_INCLUDE_DIRS}', '${Qt5Gui_INCLUDE_DIRS}'])
stg_extension = Extension('${PROJECT_NAME}',
                          include_dirs=['${CMAKE_SYSTEM_INCLUDE_PATH}', '${Stg_SOURCE_DIR}'] + sum(qt_include, []),
                          library_dirs=['${CMAKE_SYSTEM_LIBRARY_PATH}', '${Stg_BINARY_DIR}'],
                          libraries=libraries,
                          extra_compile_args=extra_compile_args + sysconfig.get_config_var('CFLAGS').split(),
                          sources=source_files)

if __name__ == '__main__':
    setup(name='${PROJECT_NAME}',
          version='${PROJECT_VERSION}',
          description='',
          author='',
          author_email='',
          platforms=['Mac OSX', 'POSIX', 'Windows'],
          classifiers=[
              'Intended Audience :: Developers',
              'Operating System :: MacOS :: MacOS X',
              'Operating System :: Microsoft :: Windows',
              'Operating System :: POSIX',
              'Programming Language :: Python',
          ],
          url='https://github.com/iccet/stego',
          long_description='''''',
          license='MIT',
          ext_modules=[stg_extension])
