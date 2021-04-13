from typing import List

__version__ = '${PROJECT_VERSION}'
__readme__ = 'README.md'

import mimetypes
from distutils.core import setup, Extension
import sysconfig
from os import path
from glob import glob


mimetypes.init()
mimetypes.add_type('text/markdown', '.md')


def split(_path: str) -> List[str]:
    return _path.split(';')


with open(__readme__, "r", encoding="utf-8") as fh:
    long_description = fh.read()

source_files = glob(path.join(path.dirname(path.realpath(__file__)), "*.cpp"))
libraries = split('${LINKED_LIBRARIES}')
extra_compile_args = ["-std=c++${CMAKE_CXX_STANDARD}"] + "${CMAKE_CXX_FLAGS}".strip().split(' ')
qt_include = map(split, ['${Qt5Core_INCLUDE_DIRS}', '${Qt5Gui_INCLUDE_DIRS}'])
stg_extension = Extension('${PROJECT_NAME}',
                          define_macros=[('PROJECT_VERSION', '"${PROJECT_VERSION}"'),
                                         ('PROJECT_NAME', '"${PROJECT_NAME}"')],
                          include_dirs=['${CMAKE_SYSTEM_INCLUDE_PATH}', '${Stg_SOURCE_DIR}'] + sum(qt_include, []),
                          library_dirs=['${CMAKE_SYSTEM_LIBRARY_PATH}', '${Stg_BINARY_DIR}'],
                          libraries=libraries,
                          runtime_library_dirs=['${Stg_BINARY_DIR}'],
                          extra_compile_args=extra_compile_args + sysconfig.get_config_var('CFLAGS').split(),
                          sources=source_files)

if __name__ == '__main__':
    setup(name='${PROJECT_NAME}',
          version=__version__,
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
          long_description=long_description,
          long_description_content_type=mimetypes.guess_type(__readme__)[0],
          license='MIT',
          ext_modules=[stg_extension])
