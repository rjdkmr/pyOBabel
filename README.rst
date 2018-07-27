.. image:: https://travis-ci.org/rjdkmr/pyOBabel.svg?branch=master
    :target: https://travis-ci.org/rjdkmr/pyOBabel

pyOBabel
========

It is a Python interface for `openbabel chemical toolbox <http://openbabel.org>`_.

It is not the official Python interface of openbabel and may lack many functionality of openbabel.
If you are looking for official Python, Please follow this
`link <http://openbabel.org/docs/dev/UseTheLibrary/Python_PybelAPI.html>`_.


Why another Python interface
----------------------------
The official Python interface to openbabel was built using `SWIG <http://www.swig.org/>`_.
However, I used `pybind11 <http://pybind11.readthedocs.io>`_ to built the Python interface.
It gives flexibility in building Python interface such that the obtained Python interface
can be used in pythonic way.


Please cite the original publication of the openbabel:
------------------------------------------------------
# O'Boyle et al (2011)
# Open Babel: An open chemical toolbox
# Journal of Cheminformatics 2011 3:33
# https://doi.org/10.1186/1758-2946-3-33 .
