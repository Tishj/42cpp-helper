/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:49:35 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/21 21:33:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <42cpp_helper.hpp>
#include <fstream>

using namespace std;

string	createGuard(string headerName)
{
	string guard;

	for (size_t i = 0; i < headerName.size(); i++)
	{
		if (isalpha(headerName[i]) && islower(headerName[i]))
			guard += toupper(headerName[i]);
		else
		{
			if (i && islower(headerName[i - 1]))
				guard += "_";
			if (isalpha(headerName[i]))
				guard += headerName[i];
		}
	}
	return (guard);
}

void	initHeaderFile(string headerName)
{
	ofstream header(headerName.c_str());
	string guard;
	string coplien[] = {
	"\tCLASS();\n",
	"\tCLASS(const CLASS& ref);\n",
	"\tCLASS& operator=(const CLASS& ref);\n",
	"\t~CLASS();\n"
	};

	guard = createGuard(headerName);
	string className = headerName.substr(0, headerName.find(".hpp"));
	if (className.size() > 0)
		className[0] = toupper(className[0]);
	header << "#ifndef " << guard << endl;
	header << "# define " << guard << "\n\n";
	header << "class\t" << className << endl;
	header << "\{\n";
	header << "public:\n";
	for (size_t i = 0; i < sizeof(coplien) / sizeof(string); i++)
	{
		replaceAll(coplien[i], "CLASS", className);
		header << coplien[i];
	}
	header << "};\n";
	header << "\n#endif\n";
}
