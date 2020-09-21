/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:47:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/21 21:32:10 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <42cpp_helper.hpp>
#include <fstream>

using namespace std;

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
		if (size_t tmp = raw.find(".hpp") != string::npos && tmp + 3 == raw.size())
		{
			sourceName = string(raw.substr(0, tmp) + string(".cpp"));
			headerName = raw;
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
