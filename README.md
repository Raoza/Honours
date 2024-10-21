# Honours
Variety of scripts and programs developed and edited during my honours thesis. These scripts were run on PAWSEY's Nimbus Supercomputer to obtain more computationally intensive results.

**1. Counting Hamilton Cycles** [C, vim]
This script counts the number of Hamilton cycles in a graph, taking g6 strings as input. 
The output is a text file containing SQL statements, which can be transformed using 
_transform_sql.vim_ into a batch insert format for computational efficiency, as direct 
database interactions were too slow for larger computations.

To compile the script run: 
gcc -I/[file path]/nauty2_8_6 -o [desired script name] HcycsSQLstring.c [file path]/nauty2_8_6/nauty.a


**2. Updating Graph Properties in SQL Database** [Sagemath, SQL]
Sage script which runs through a database with g6strings, calculates certain graph properties 
and updates the database accordingly.


**3. Visualising Complex Graphs** [Sagemath]
Example of a script which can breakdown complicated graphs and plots them in such a way
which makes them easier and cleaner to visualise and potentially derive counting methods
to enumerate the number of Hamilton cycles in them.


**4. Extending the Results of Royle and Pivotto - Counting Hamilton Cycles in Width 7 Nanotubes** [Python, Sagemath]
Program which utilises Royle and Pivottos transfer matrix method for caluclating Hamilton Cycles
in a family of planar graphs referred to as nanotubes. This program extends their results to width 7 nanotubes, from scratch. The problem and it's calculations were defined in section 5 to 7 in the paper: https://www.sciencedirect.com/science/article/pii/S0012365X19302705
