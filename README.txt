Project page: http://www.cs.tut.fi/~rinn/Projects.html

Compile and run using QtCreator (open: project.pro)

This base code shows how to use the project library (picture modifications)
in single threaded application.

Write all your code in this directory (you can change the main.cpp and
add any new files you need):
DO NOT make ANY changes to the library (concur2018lib-directory).
If you find a bug in the library, write a bug report to: rinn@tut.fi

'inputs' and 'outdir' are used if you run your program in TUT environment
(QtCreator and linux). They have only been testes @TUT, so do not 
expect them to work automatically if you try the code in some other
environment.

Qt libraries are used for some internal file handling in the library, but
DO NOT use Qt in concurrency code. Your should implement all your own
concurrency using standard C++.


