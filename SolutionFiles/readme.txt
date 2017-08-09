Complete isolated build for all roscpp libraris using log4cxx (that is another project that needs to be in repos).

All required libraries (so far as I know) are here, build here ok in debug and release 64 and are all STATIC LIBRARY 2015.   Testing is light, but kintetic project is an exe used for testing.

In building and assembling this, look for //greg1, etc in .cmake files and in source to see very minor changes.
Ivan added inline to a template multiply defined issue.

There are no pragma links here, all are in "References"


Note that the python msg_gen stuff needs to be at C:\Users\gbrill\Dropbox\Repos\kinetic\share\ROSPyTesting\ROSPyTesting.sln, because catkin has location dependencies.  SO that's the oddball project that will be outside
of the c:\ros directory and in c:\repos.



IMPORTANT PREPROCS:

APU_DECLARE_STATIC;LOG4CXX_STATIC;

otherwise, will get dllimport errors.


