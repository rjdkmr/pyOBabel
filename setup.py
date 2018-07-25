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
from setuptools import setup, find_packages
# To use a consistent encoding
from codecs import open
from os import path

here = path.abspath(path.dirname(__file__))

def read(fname):
    return open(path.join(path.dirname(__file__), fname)).read()

setup(
    name='pyOBabel',
    version='0.1.1',

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
