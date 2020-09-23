/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:50:11 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/23 19:19:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

using namespace std;

std::streampos fileSize(const char* filePath)
{
	std::streampos fsize = 0;
	std::ifstream file(filePath, std::ios::binary);

	fsize = file.tellg();
	file.seekg( 0, std::ios::end );
	fsize = file.tellg() - fsize;
	file.close();

	cerr << "Source(" << filePath << ") filesize: " << fsize << endl;
	return fsize;
}

int	error(string errmsg)
{
	cerr << errmsg << endl;
	return (0);
}

bool exists (const std::string& name)
{
	return ( access( name.c_str(), F_OK ) != -1 );
}

bool	characterInSet(char c, string s)
{
	for (size_t i = 0; i < s.size(); i++)
		if (c == s[i])
			return (true);
	return (false);
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
