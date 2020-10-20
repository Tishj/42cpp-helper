/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   source.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:55:39 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/20 15:52:10 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <42cpp_helper.hpp>
#include <Function.hpp>
#include <unordered_map>

using namespace std;

//If source file exists, check if some of the functions in the header are missing
//if there are, add them to the source file

bool	getPrototype(string buf, Function& funct, string className)
{
	regex expression("[\\t]+(?:([^\\t\\ \\(\\);]+)[\\t\\ ]+)?(.*\\(.*\\));");
	smatch match;
	if (!regex_search(buf, match, expression))
		return (false);
	funct.returnType = match.str(1);
	funct.name = match.str(2);
	funct.classPrefix = className;
//	cout << "1: " << match.str(1) << " | 2: " << match.str(2) << endl;
	return (true);
}

bool	getFunctionDeclaration(string buf, Function& funct, string className)
{
	regex expression("^[\\t]*(?:(.*)[\\t])?(?:.*\\:\\:)?([^\\t]*\\(.*\\))$");
	smatch match;
	if (!regex_search(buf, match, expression))
		return (false);
	funct.returnType = match.str(1);
	funct.name = match.str(2);
	funct.classPrefix = className;
//	cout << "1: " << match.str(1) << " | 2: " << match.str(2) << endl;
	return (true);
}

bool	isUpToDate(Function sfunct, Function hfunct)
{
	if (sfunct.name != hfunct.name)
		return (false);
	if (sfunct.returnType != sfunct.returnType)
		return (false);
	return (true);
}

void	addMissingFunctions(string sourceName, vector<Function> missing)
{
	ofstream	source(sourceName.c_str(), ios_base::app);

	for (size_t i = 0; i < missing.size(); i++)
		source << missing[i];
}

void	updateSourceFile(string sourceName, string headerName)
{
	ifstream	source(sourceName.c_str());
	ifstream	header(headerName.c_str());

	string className = headerName.substr(0, headerName.find(".hpp"));
	if (className.size() > 0)
		className[0] = toupper(className[0]);
	vector<Function>	headerPrototypes;
	unordered_map<string, Function>	sourceDeclaration;
	string buf;
	while (getline(header, buf))
	{
		Function tmp;
		if (getPrototype(buf, tmp, className))
			headerPrototypes.push_back(tmp);
		if (header.eof())
			break ;
	}
	while (getline(source, buf))
	{
		Function tmp;
		if (getFunctionDeclaration(buf, tmp, className))
			sourceDeclaration[tmp.name] = tmp;
		if (source.eof())
			break ;
	}
	vector<Function>	missingFunctions;
	for (size_t i = 0; i < headerPrototypes.size(); i++)
	{
		Function tmp = sourceDeclaration[headerPrototypes[i].name];
		if (!isUpToDate(tmp, headerPrototypes[i]))
			missingFunctions.push_back(headerPrototypes[i]);
	}
	addMissingFunctions(sourceName, missingFunctions);
}

void	initSourceFile(ofstream& source, string headerName)
{
	ifstream	header(headerName.c_str());

	size_t	path_separator = headerName.find_last_of('/');
	if (path_separator != string::npos)
		headerName = headerName.substr(path_separator + 1, headerName.size());
	source << "#include <" << headerName << ">\n\n";
	source << "#include <string>\n";
	source << "#include <iostream>\n";

	string className = headerName.substr(0, headerName.find(".hpp"));
	if (className.size() > 0)
		className[0] = toupper(className[0]);
	vector<string>	functions;

	string	buf;
	bool functsFound = false;
	while (getline(header, buf))
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
		if (header.eof())
			break ;
	}
	for (size_t i = 0; i < functions.size(); i++)
	{
		size_t	parenthesis = functions[i].find('(');
		size_t	whitespace = functions[i].find_first_of(" \t");
		if (whitespace < parenthesis && whitespace < functions[i].size())
		{
			string funct_definition;
			funct_definition += "\n";
			funct_definition += functions[i].substr(0, whitespace);
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
			source << "\n" << className << "::" << functions[i] << endl;
		source << "{\n\n}\n";
	}
}
