Open and close an ODB
=====================

Since the original ODB system is written in C, handling its data requires
initializing several internal structures such as paths, handlers and pointers.
These operations must be performed in the backend before accessing the data.

To simplify this process, the **odb4py.core** module provides two functions
to open and close an ODB database.

Open an ODB database
--------------------
To open a database, the ``odbConnect`` function from the ``odb4py.core``
module must be used. This function returns **0** if the connection succeeds
or **-1** if it fails.

The function initializes the main ODB variables such as the database path,
the location of metadata files, and the maximum number of ODB handlers.

.. code-block:: python

   #-*- coding: utf-8 -*-
   
   # Import function
   from odb4py.core import odbConnect

   # Path to a CCMA database
   dbtype = "CCMA"
   dbpath = "/".join(("/path/to/odb", dbtype))

   # Open the database
   iret = odbConnect(odbdir=dbpath )

   # Check the return code
   if iret < 0:
       print("Failed to open the ODB database:", dbpath)
       sys.exit(1)


Close an ODB database
---------------------
Once the database is no longer needed, it should be closed using the
``odbClose`` function. This function releases allocated handlers,
poolmask arrays (if used), and reinitializes the internal ODB structures.

The function takes no arguments. It automatically looks for all variables
that were initialized during the connection phase.

The function returns **0** if the operation succeeds and **-1** otherwise.

.. code-block:: python

   #-*- coding: utf-8 -*-
   import sys

   # Import function
   from odb4py.core import odbClose

   # Close the database
   odbClose()
