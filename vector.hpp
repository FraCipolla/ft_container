/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:42:22 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/27 17:30:47 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <string>
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class Vector
	{
	public:
		typedef T												value_type;
		typedef Alloc											allocator_trait;
		typedef value_type&										refence;
		typedef const value_type&								reference_pointer;
		typedef typename allocator_trait::pointer				pointer;
		typedef typename allocator_trait::const_pointer			const_pointer;
		// typedef ft::random_access_iterator<value_type>			iterator;
		// typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef typename allocator_trait::size_type          	size_type;
		typedef	pointer											iterator;
		typedef	const_pointer									const_iterator;
		
		explicit Vector(const allocator_trait& alloc = allocator_trait())
		:
				_alloc(alloc),
				_start(nullptr),
				_end(nullptr),
				_end_capacity(nullptr)
		{}
		~Vector();

	iterator				begin()	noexcept;
	const_iterator			begin()	const noexcept;
	iterator				end()	noexcept;
	const_iterator			end()	const noexcept;

	reverse_iterator		rbegin()	noexcept;
	const_reverse_iterator	rbegin()	const noexcept;
	reverse_iterator		rend()	noexcept;
	const_reverse_iterator	rend()	const noexcept;

	const_iterator			cbegin()	const noexcept;
	const_iterator			cend()	const noexcept;
	const_reverse_iterator	crbegin()	const noexcept;
	const_reverse_iterator	crend()	const noexcept;
		
		protected:
		allocator_trait		_alloc;
		pointer				_begin;
		pointer				_end;
		pointer				_end_capacity;
	};	
}

#endif