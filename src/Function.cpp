/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Function.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 15:49:30 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/23 21:39:43 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include <Function.hpp>

using namespace std;

Function::Function() {};

Function::Function(string ret, string name, string clss) : returnType(ret), name(name), classPrefix(clss) {};

Function::Function(const Function& funct) : returnType(funct.returnType), name(funct.name), classPrefix(funct.classPrefix) {};

Function::~Function() {};

ostream&	operator<<(ostream& stream, const Function& funct)
{
	stream << "\n";
	if (funct.returnType.size())
		stream << funct.returnType << "\t";
	stream << funct.classPrefix << "::" << funct.name << "\n{\n\n}\n";
	return (stream);
}
