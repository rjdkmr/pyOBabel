.. |openbabel| raw:: html

   <a href="http://openbabel.org" target="_blank">openbabel chemical toolbox</a>

.. |pybel link| raw:: html

   <a href="http://openbabel.org/docs/dev/UseTheLibrary/Python_PybelAPI.html" target="_blank">pybel link</a>

.. |SWIG| raw:: html

   <a href="http://www.swig.org/" target="_blank">SWIG</a>

.. |pybind11| raw:: html

   <a href="http://pybind11.readthedocs.io" target="_blank">pybind11</a>


pyOBabel
========

It is a Python interface for |openbabel|.

It is not the official Python interface of openbabel and may lack many functionality of openbabel.
If you are looking for official Python, Please follow this |pybel link|.


Why another Python interface
----------------------------
The official Python interface to openbabel was built using |SWIG|.
However, I used |pybind11| to built the Python interface.
It gives flexibility in building Python interface such that the obtained Python interface
can be used in pythonic way.


Please cite the original publication of the openbabel:
------------------------------------------------------
* O'Boyle et al (2011)
    Open Babel: An open chemical toolbox
    Journal of Cheminformatics 2011 3:33
    https://doi.org/10.1186/1758-2946-3-33 .


Contents
--------
.. toctree::
   :maxdepth: 2
   :caption: Contents

    Summary <interface_summary>
    Module Documentation <module/index>



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
