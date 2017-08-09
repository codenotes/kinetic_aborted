// kintetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef _DEBUG
#pragma message ("explicitly linking with log4 apr stuff because otherwise they constantly rebuild...")					   


#pragma region("test")
//test region


//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr\x64\Debug\libapr-1.lib)") //WHY IS THIS SO IMPORTANT????  THIS IS ESSENTIAL, it is also linkable with dll

//For reference: all are implicitly linked now
//#pragma comment(lib, R"(C:\Users\gbrill\Dropbox\Projects\Apache\Log\apr\x64\LibD\apr-1.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr-util\x64\LibD\aprutil-1.lib)")
//#pragma comment(lib, R"(C:\Users\gbrill\Dropbox\Projects\Apache\Log\apr\x64\Debug\libapr.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\libexpat\expat\x64\bin\Debug\libexpatMT.lib)")

//For reference: all are implicitly linked now
#else


//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr_later\apr\.\x64\LibR\apr-1.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr-util\.\x64\LibR\aprutil-1.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\libexpat\expat\x64\bin\Release\libexpatMT.lib)")
#endif


#pragma endregion


#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")

#include "tuplelog.h"

#ifdef TEST_MAIN
int main()
{
    return 0;
}
#endif
//C:\Users\gbrill\Dropbox\Projects\Apache\Log\apr\.\x64\Debug\libapr.lib //Do I need to rebuild only this and it builds other things or something? has start.c in it which has apr_initialize, one of the things I am hunting as unresolved
//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr-util\x64\LibD\aprutil-1.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr-util\x64\Debug\libaprutil.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr\x64\Debug\libapr.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr\x64\Debug\libapr-1.lib)")
//#pragma comment(lib, R"(C:\repos\log4cxx\apache-log4cxx-0.10.0\apr-util\x64\Debug\libaprutil-1.lib)")






