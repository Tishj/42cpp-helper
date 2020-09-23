/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:47:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/23 21:25:18 by tbruinem      ########   odam.nl         */
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

enum e_extension	get_extension(size_t *extension, string input)
{
	*extension = input.find(".hpp");
	if (*extension == string::npos)
	{
		*extension = input.find(".cpp");
		if (*extension != string::npos)
			return (CPP);
		return (NONE);
	}
	return (HPP);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (error("Please provide atleast one file"));
	for (int i = 1; i < argc; i++)
	{
		string raw(argv[i]);
		string sourceName;
		string headerName;

		size_t	ext_index;
		e_extension	ext = get_extension(&ext_index, raw);
		if (ext != NONE)
		{
			sourceName = string(raw.substr(0, ext_index) + string(".cpp"));
			headerName = string(raw.substr(0, ext_index) + string(".hpp"));
		}
		else
		{
			sourceName = string(raw + string(".cpp"));
			headerName = string(raw + string(".hpp"));
		}
		if (!exists(headerName))
			initHeaderFile(headerName);
		if (fileSize(sourceName.c_str()) == 0)
		{
			ofstream source(sourceName.c_str());
			initSourceFile(source, headerName);
		}
		else
			updateSourceFile(sourceName, headerName);
	}
	return (0);
}
