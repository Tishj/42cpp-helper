/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   source.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:55:39 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/21 21:32:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <42cpp_helper.hpp>

using namespace std;

void	initSourceFile(ofstream& source, string headerName)
{
	ifstream	header(headerName.c_str());

	source << "#include <" << headerName << ">\n\n";
	source << "#include <string>\n";
	source << "#include <iostream>\n\n";

	string className = headerName.substr(0, headerName.find(".hpp"));
	if (className.size() > 0)
		className[0] = toupper(className[0]);
	vector<string>	functions;

	string	buf;
	bool functsFound = false;
	for (;getline(header, buf, '\n');!header.eof())
	{
		if (buf.find("}") != string::npos)
			break ;
		if (functsFound)
		{
			int tabs = 0;
			for (;buf[tabs] == '\t';tabs++) {}
			buf = buf.substr(tabs, (buf.find(';') == string::npos) ? buf.size() : buf.find(';') - 1);
			functions.push_back(buf);
		}
		if (buf.find("public:") != string::npos)
			functsFound = true;
	}
	for (size_t i = 0; i < functions.size(); i++)
	{
		cout << functions[i] << endl;
		size_t	parenthesis = functions[i].find('(');
		size_t	whitespace = functions[i].find_first_of(" \t");
		if (whitespace < parenthesis && whitespace < functions[i].size())
		{
			string funct_definition = functions[i].substr(0, whitespace);
			funct_definition += "\t";
			int count = 0;
			for (int j = whitespace; characterInSet(functions[i][j], "\t "); j++)
				count++;
			funct_definition += className;
			funct_definition += "::";
			funct_definition += functions[i].substr(whitespace + count, functions[i].size());
			funct_definition += "\n";
			source << funct_definition;
		}
		else
			source << className << "::" << functions[i] << endl;
		source << "{\n\n}\n\n";
	}
}
