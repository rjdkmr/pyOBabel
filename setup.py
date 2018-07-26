#!/usr/bin/env python
#
# This file is part of pyOBabel
#
# Author: Rajendra Kumar
#
# pyOBabel is a python binding to openbabel chemical toolbox (http://openbabel.org).
# Please cite the original publication of the openbabel:
# O'Boyle et al (2011)
# Open Babel: An open chemical toolbox
# Journal of Cheminformatics 2011 3:33
# https://doi.org/10.1186/1758-2946-3-33 .
#
# pyOBabel is a free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# pyOBabel is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with pyOBabel.  If not, see <http://www.gnu.org/licenses/>.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
# TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#============================================================================

# Always prefer setuptools over distutils
from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext
import sys
import setuptools
from os import path
from codecs import open
import pkgconfig

here = path.abspath(path.dirname(__file__))

## Getting openbabel setting
openbabel = None
for ob in ['openbabel', 'openbabel-2.0']:
    if pkgconfig.exists(ob):
        openbabel = ob

if openbabel is None:
    raise LookupError("openbabel package not found")

pkgconfig.libs(openbabel)
openbabel_inc_dir = pkgconfig.cflags(openbabel)[2:]
openbabel_lib_dir = pkgconfig.re.split('\s+', pkgconfig.libs(openbabel))[0][2:]

class get_pybind_include(object):
    """Helper class to determine the pybind11 include path

    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


ext_modules = [
    Extension(
        'pyOBabel.pyOBabel',
        [   'src/pyOBabel.cpp',
            'src/base.cpp',
            'src/vector3.cpp',
            'src/atom.cpp',
            'src/bond.cpp',
            'src/mol.cpp',
            'src/residue.cpp',
            'src/obconversion.cpp',
            'src/plugin.cpp',
            'src/bitvec.cpp',
            'src/builder.cpp',
            'src/forcefield.cpp',
            'src/oberror.cpp',
        ],
        include_dirs=[
            get_pybind_include(),
            get_pybind_include(user=True),
            openbabel_inc_dir,
            'src',
        ],
        library_dirs=[openbabel_lib_dir],
        libraries=['openbabel'],
        language='c++',
        extra_compile_args=['-Wno-strict-prototypes']
    ),
]


# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.

    The c++14 is prefered over c++11 (when it is available).
    """
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }

    if sys.platform == 'darwin':
        c_opts['unix'] += ['-stdlib=libc++', '-mmacosx-version-min=10.7']

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
        for ext in self.extensions:
            ext.extra_compile_args += opts
        build_ext.build_extensions(self)


def read(fname):
    return open(path.join(path.dirname(__file__), fname)).read()

setup(
    name='pyOBabel',
    version='0.1.1',
    ext_modules=ext_modules,
    cmdclass={'build_ext': BuildExt},
    install_requires=['pkgconfig>=1.3', 'pybind11>=2.2'],
    # metadata for upload to pypi
    author = "Rajendra Kumar",	
    author_email = "rjdkmr@gmail.com",
    url = 'https://github.com/rjdkmr/pyOBabel',
    description = "A python binding to openbabel chemical toolbox (http://openbabel.org)",
    long_description = read('README.rst'),
    keywords = ["Molecular Modeling", "Chemoinformatics", "Computational Chemistry", "Computational Drug Design"],
    license = 'GNU General Public License v3 (GPLv3)',
    classifiers = [
        'Environment :: Console',
        'Intended Audience :: Developers',
        'Intended Audience :: End Users/Desktop',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
        'Natural Language :: English',
        'Operating System :: MacOS',
        'Operating System :: POSIX :: Linux',
        'Topic :: Scientific/Engineering :: Chemoinformatics',
        'Topic :: Scientific/Engineering :: Computational Chemistry',
        'Topic :: Scientific/Engineering :: Computational Drug Design',
    ],
)
