/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_empty_bodies.cpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 17:33:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/21 20:57:28 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>

using namespace std;

std::streampos fileSize( const char* filePath ){

    std::streampos fsize = 0;
    std::ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}

int	error(string errmsg)
{
	cerr << errmsg << endl;
	return (0);
}

inline bool exists (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

bool	characterInSet(char c, string s)
{
	for (int i = 0; i < s.size(); i++)
		if (c == s[i])
			return (true);
	return (false);
}

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
	for (int i = 0; i < functions.size(); i++)
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

void	replaceAll(string& src, string s1, string s2)
{
	size_t idx = src.find(s1, 0);
	for (;idx != string::npos;idx = src.find(s1, idx))
	{
		src.replace(idx, s1.size(), s2);
		idx += s2.size();
	}
}

string	createGuard(string headerName)
{
	string guard;

	for (int i = 0; i < headerName.size(); i++)
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
	for (int i = 0; i < sizeof(coplien) / sizeof(string); i++)
	{
		replaceAll(coplien[i], "CLASS", className);
		header << coplien[i];
	}
	header << "};\n";
	header << "\n#endif\n";
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (error("Please provide atleast one file"));
	for (int i = 1; i < argc; i++)
	{
		string raw(argv[i]);
		if (raw.size() <= 3)
			continue ;
		string sourceName;
		string headerName;
		ofstream	source;
		if (int tmp = raw.find(".hpp") != string::npos && tmp + 3 == raw.size())
		{
			sourceName = string(raw.substr(0, tmp) + string(".cpp"));
			headerName = raw;
			source = ofstream(sourceName.c_str());
		}
		else
		{
			sourceName = string(raw + string(".cpp"));
			headerName = string(raw + string(".hpp"));
			source = ofstream(sourceName.c_str());
		}
		if (!exists(headerName))
			initHeaderFile(headerName);
		if (fileSize(sourceName.c_str()) == 0)
			initSourceFile(source, headerName);
	}
	return (0);
}
