#define STRING2(x) #x
#define STRING(x) STRING2(x)
#pragma message("Linking against boost Version->" STRING(_MSC_PLATFORM_TOOLSET)) //value is 120 or 140


//link 2015 boost binary

#pragma comment(lib, "Ws2_32.lib")
 
#ifndef _DEBUG


#if _MSC_PLATFORM_TOOLSET == 140


#ifndef _WIN64

#pragma message("->Linking with Boost libraries from 2015 at path " STRING(_BOOSTLIB_2015 ))
#pragma comment(lib , STRING(_BOOSTLIB_2015 )"/boost_signals-vc140-mt-1_58.lib" )
#pragma comment(lib , STRING(_BOOSTLIB_2015 )"/boost_regex-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015 )"/boost_filesystem-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015 )"/boost_system-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015 )"/boost_serialization-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015 )"/boost_thread-vc140-mt-1_58.lib")

#else
#pragma message("->Linking with Boost libraries from 2015 at path " STRING(_BOOSTLIB_2015_64 ))
#pragma comment(lib , STRING(_BOOSTLIB_2015_64 )"/boost_signals-vc140-mt-1_58.lib" )
#pragma comment(lib , STRING(_BOOSTLIB_2015_64 )"/boost_regex-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015_64 )"/boost_filesystem-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015_64 )"/boost_system-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015_64 )"/boost_serialization-vc140-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2015_64 )"/boost_thread-vc140-mt-1_58.lib")


#endif

#else


//#if _PROCESSOR_ARCH == x86
#ifndef _WIN64
#pragma message("->Linking with Boost libraries from 2013 at path " STRING(_BOOSTLIB_2013 ))
#pragma comment(lib , STRING(_BOOSTLIB_2013 )"/boost_signals-vc120-mt-1_58.lib" )
#pragma comment(lib , STRING(_BOOSTLIB_2013 )"/boost_regex-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013 )"/boost_filesystem-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013 )"/boost_system-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013 )"/boost_serialization-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013 )"/boost_thread-vc120-mt-1_58.lib")

#else
#pragma message("->Linking with Boost libraries from 2013 at path " STRING(_BOOSTLIB_2013_64 ))
#pragma comment(lib , STRING(_BOOSTLIB_2013_64 )"/boost_signals-vc120-mt-1_58.lib" )
#pragma comment(lib , STRING(_BOOSTLIB_2013_64 )"/boost_serialization-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013_64 )"/boost_filesystem-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013_64 )"/boost_regex-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013_64 )"/boost_system-vc120-mt-1_58.lib")
#pragma comment(lib , STRING(_BOOSTLIB_2013_64 )"/boost_thread-vc120-mt-1_58.lib")



#endif
#endif


#endif
