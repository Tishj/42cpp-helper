/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Function.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 15:46:52 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/09/23 19:12:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP
# define FUNCTION_HPP

#include <iostream>
#include <string>

class	Function
{
	public:
		Function();
		Function(std::string ret, std::string name, std::string clss);
		Function(const Function& funct);
		~Function();
		std::string	returnType;
		std::string	name;
		std::string	classPrefix;
};

std::ostream&	operator<<(std::ostream& stream, const Function& funct);

#endif
