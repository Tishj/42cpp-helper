/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:47:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/10/20 16:27:42 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <42cpp_helper.hpp>
#include <fstream>
#include <vector>

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

void	sanitize_args(std::vector<std::string>& args, char **argv)
{
	bool newArg = true;

	for (size_t i = 1; argv[i]; i++)
	{
		for (size_t j = 0; argv[i][j]; j++)
		{
			if (isalnum(argv[i][j]) || argv[i][j] == '.')
			{
				if (newArg)
					args.push_back(std::string());
				args[args.size() - 1] += argv[i][j];
				newArg = false;
			}
			else
				newArg = true;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (error("Please provide atleast one file"));
	std::vector<std::string> args;

	sanitize_args(args, argv);
	for (size_t i = 0; i < args.size(); i++)
	{
		string sourceName;
		string headerName;

		size_t	ext_index;
		e_extension	ext = get_extension(&ext_index, args[i]);
		if (ext != NONE)
		{
			sourceName = string(args[i].substr(0, ext_index) + string(".cpp"));
			headerName = string(args[i].substr(0, ext_index) + string(".hpp"));
		}
		else
		{
			sourceName = string(args[i] + string(".cpp"));
			headerName = string(args[i] + string(".hpp"));
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
