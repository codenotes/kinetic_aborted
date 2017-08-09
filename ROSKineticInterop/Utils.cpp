#include "stdafx.h"

using namespace std;



long CreateSafeArrayFromBSTRArray(BSTR* pBSTRArray, ULONG ulArraySize, SAFEARRAY** ppSafeArrayReceiver)

{ 
	HRESULT hrRetTemp = S_OK;
	SAFEARRAY* pSAFEARRAYRet = NULL;
	SAFEARRAYBOUND rgsabound[1];
	ULONG ulIndex = 0;
	long lRet = 0;

	// Initialise receiver.
	if (ppSafeArrayReceiver)
	{
		*ppSafeArrayReceiver = NULL;
	}

	if (pBSTRArray)
	{
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = ulArraySize;

		pSAFEARRAYRet = (SAFEARRAY*)SafeArrayCreate
			(
				(VARTYPE)VT_BSTR,
				(unsigned int)1,
				(SAFEARRAYBOUND*)rgsabound
				);
	}

	for (ulIndex = 0; ulIndex < ulArraySize; ulIndex++)
	{
		long lIndexVector[1];

		lIndexVector[0] = ulIndex;

		// Since pSAFEARRAYRet is created as a SafeArray of VT_BSTR,
		// SafeArrayPutElement() will create a copy of each BSTR
		// inserted into the SafeArray.
		SafeArrayPutElement
			(
				(SAFEARRAY*)pSAFEARRAYRet,
				(long*)lIndexVector,
				(void*)(pBSTRArray[ulIndex])
				);
	}

	if (pSAFEARRAYRet)
	{
		*ppSafeArrayReceiver = pSAFEARRAYRet;
	}

	return lRet;
}



//converts regular std::string to wide string
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}



void getLaunchParams(std::string path, std::map<string, string> & params)
{

	boost::property_tree::ptree pt;
	boost::property_tree::read_xml(path, pt);

	boost::property_tree::ptree sub_pt;

	for (const boost::property_tree::ptree::value_type &v : pt.get_child("launch"))
	{
		if (v.first == "node")
		{
			//std::cout << v.first << ":";// << std::endl;

			for (const boost::property_tree::ptree::value_type &v2 : v.second)
			{
				//	std::cout << v2.first << ":";// << std::endl;


				for (const boost::property_tree::ptree::value_type &v3 : v2.second)
				{
					if (v2.first != "param")
					{
						//	std::cout << v3.first << "->" << v3.second.get<string>("") << std::endl;
					}
					else if (v2.first == "param")
					{
						string name;
						string value;


						for (const boost::property_tree::ptree::value_type &v4 : v3.second)
						{

							if (v4.first == "name")
							{
								name = v4.second.get<string>("");

							}
							else
							{
								value = v4.second.get<string>("");
								params[name] = value;
								//	std::cout << v4.first << "->" << v4.second.get<string>("") << std::endl;
							}



							//params.insert(std::pair<string, string>(v4.first, v4.second.get<string>("")));


						}

					}

				}

			}


		}

	}


}




bool is_numeric(const std::string& str) {
	std::istringstream ss(str);
	double dbl;
	ss >> dbl;      // try to read the number
	ss >> std::ws;  // eat whitespace after number

	if (!ss.fail() && ss.eof()) {
		return true;  // is-a-number
	}
	else {
		return false; // not-a-number
	}
}

bool isFloat(std::string someString)
{
	using boost::lexical_cast;
	using boost::bad_lexical_cast;

	//if aint a decimal, it aint a float.
	if (someString.find('.') == string::npos)
	{
		return false;
	}



	try
	{

		boost::lexical_cast<float>(someString);
	}
	catch (bad_lexical_cast &)
	{
		return false;
	}

	return true;
}

bool isInt(std::string someString)
{
	using boost::lexical_cast;
	using boost::bad_lexical_cast;


	try
	{
		boost::lexical_cast<int>(someString);
	}
	catch (bad_lexical_cast &)
	{
		return false;
	}

	return true;
}