/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   42cpp_helper.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 20:51:34 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/21 21:27:17 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPP_HELPER_HPP
# define CPP_HELPER_HPP

#include <string>
#include <iostream>

void			replaceAll(std::string& src, std::string s1, std::string s2);
void			initHeaderFile(std::string headerName);
std::string		createGuard(std::string headerName);
std::streampos	fileSize(const char* filePath);
int				error(std::string errmsg);
bool			exists (const std::string& name);
bool			characterInSet(char c, std::string s);
void			initSourceFile(std::ofstream& source, std::string headerName);

#endif
