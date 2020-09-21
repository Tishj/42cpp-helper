/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:47:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/21 22:07:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <42cpp_helper.hpp>
#include <fstream>

using namespace std;

enum	e_extension
{
	NONE,
	HPP,
	CPP,
};

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
		size_t	extension = raw.find(".hpp");
		e_extension	ext = NONE;
		if (extension == string::npos)
		{
			extension = raw.find(".hpp");
			if (extension != string::npos)
				ext = CPP;
		}
		else
			ext = HPP;
		if (ext != NONE)
		{
			sourceName = string(raw.substr(0, extension) + string(".cpp"));
			headerName = string(raw.substr(0, extension) + string(".hpp"));
		}
		else
		{
			sourceName = string(raw + string(".cpp"));
			headerName = string(raw + string(".hpp"));
		}
		ofstream source(sourceName.c_str());
		if (!exists(headerName))
			initHeaderFile(headerName);
		if (fileSize(sourceName.c_str()) == 0)
			initSourceFile(source, headerName);
	}
	return (0);
}
