Before retriving the data
=========================

**odb4py** provides two main modules:

- **odb4py.core** : A set of low-level functions interfacing Python with the ODB runtime libraries.
- **odb4py.utils**: A collection of pure Python helper utilities, for example to initialize the ODB environment, parse or sanitize SQL queries, and manage auxiliary tasks.

.. note::
   In the following examples, a CCMA ODB database is used.
   However, the same code is fully applicable to an ECMA.<obstype> database  where obstype can be : synop, radar, amdar iasi etc.


Opening an ODB Database
------------------------
To open a given database, the ``odbConnect`` function from the
``odb4py.core`` module must be used. This function returns a
positive value if the connection is successful and a negative
value if it fails.

.. code-block:: python

   #-*- coding: utf-8 -*-
   import sys
   from  odb4py.utils import OdbEnv  

   # Initialize the odb4py  environnment
   env= odbEnv()
   env.InitEnv()

   # Import method
   from odb4py.core import odbConnect

   # Path to a CCMA database
   dbpath = "/imaginary/path/CCMA"

   # Attempt to open the database
   iret = odbConnect(odbdir=dbpath, verbose=True)

   # Check the return code
   if iret < 0:
       print("Failed to open the ODB database:", dbpath)
       sys.exit(1)


Creating DCA Files (Direct Column Access)
-----------------------------------------
In order to retrieve rows and columns efficiently, ODB relies on
**DCA (Direct Column Access)** files.

DCA files contain structural metadata describing how the data are
physically stored on disk. This includes, for example:

- The starting and ending memory segments of a given table,
- Column sizes,
- Offsets between tables and columns,
- Internal layout information required for fast access.

DCA files can be created automatically when using ODB binaries such as
``odbdump.x`` or ``odbsql.x``. They can also be generated explicitly
using the ``dcagen`` script or the ``dcagen.x`` binary.

Within the **odb4py** package, a dedicated function ``odbDca`` is provided to
generate DCA files programmatically before executing a query.

Creating DCA files is straightforward: the user must provide the path
to the ODB database. The number of CPUs used for the task and the
verbosity level are optional parameters.

The generated DCA files are written into a subdirectory named
``dca`` inside the corresponding ``ECMA`` or ``CCMA`` directory.


.. code-block:: python 

   #-*- coding: utf-8 -*-
   import os , sys  
   from   odb4py.utils import OdbEnv 

   # Initialize the odb4py  environnment 
   env= odbEnv()
   env.InitEnv()
   
   # Import the  method
   from   odb4py.core  import odbDca 

   db_type  = "CCMA"
   db_path  = "/imaginary/path/"
   dca_path = "/".join( ( dbpath, db_type, "dca" ) )
   NCPU     = 8

   # Check if the files existe 
   if not os.path.isdir (dca_path ):
      ic =odbDca ( db_path=db_path, db= db_type, ncpu= NCPU  ) 
      if ic < 0 :
         print("Failed to create DCA files")
         sys.exist()


Database Attributes
-------------------

odb4py provides access to internal database metadata through the
``GetAttrib()`` method from ``utils`` module.

This method returns a collection of attributes describing the currently
opened ODB database, including structural and runtime information.

Example:
The CCMA ODB used here is provieded by some colleagues working with `MetCoOp <https://www.met.no/en/projects/metcoop>`_ limited area model. 

.. code-block:: python

   #-*-coding :utf-8 -*-
   from odb4py.utils import  OdbObject  

   # ODB Path  
   dbpath = "/imaginary/path/CCMA"

   # Instantiate 
   obj  = OdbObject( dbpath  )
   attr = db.GetAttrib()
   print(attrib)

Output:

.. code-block:: python

   type CCMA
   name CCMA
   obstype None 
   date_creation 20230821 070456
   last_modification 20230821 071418
   Observation_date 20230101 000000
   number_pools 64
   number_of_considered_tables 393
   odb_total_size 83140291
   poolmask ['1']
   tables ['body', 'conv', 'conv_body', 'desc', 'errstat', 'hdr', 'index', 'modsurf', 'poolmask', 'radar', 'radar_body', 'radar_station', 'radiance', 'radiance_body', 'sat', 'timeslot_index', 'update_1', 'update_10', 'update_2', 'update_3', 'update_4', 'update_5', 'update_6', 'update_7', 'update_8', 'update_9']
   ioassign_file examples/odb_samples/metcoop/CCMA//IOASSIGN
   flags_file examples/odb_samples/metcoop/CCMA//CCMA.flags
   iomap_file examples/odb_samples/metcoop/CCMA//CCMA.iomap
   odb_software_release 46 0.000 4

