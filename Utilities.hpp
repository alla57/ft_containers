#ifndef UTILITIES_HPP
# define UTILITIES_HPP

#include <stdint.h>
# include <uchar.h>

namespace ft
{
	// 					ENABLE_IF
	template<bool B, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// 					INTEGRAL_CONSTANT
	template<class T, T v>
	struct integral_constant
	{
		static const T					value = v;
		typedef T 						value_type;
		typedef integral_constant<T, v>	type;
		operator T(){return v;}
	};
	
	// 					TRUE_TYPE AND FALSE_TYPE
	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	// 						REMOVE_CV
	template<class T> struct remove_cv{typedef T type;};
	template<class T> struct remove_cv<const T>{typedef T type;};
	template<class T> struct remove_cv<volatile T>{typedef T type;};
	template<class T> struct remove_cv<const volatile T>{typedef T type;};

	// 						IS_INTEGRAL_HELPER
	template<class T>
	struct is_integral_helper : false_type{};
	// 			Boolean
	template<>
	struct is_integral_helper<bool> : true_type{};
	// 			Characters
	template<>
	struct is_integral_helper<char> : true_type{};
	template<>
	struct is_integral_helper<wchar_t> : true_type{};
	template<>
	struct is_integral_helper<signed char> : true_type{};
	template<>
	struct is_integral_helper<unsigned char> : true_type{};
	// 			Integers
	template<>
	struct is_integral_helper<short int> : true_type{};
	template<>
	struct is_integral_helper<int> : true_type{};
	template<>
	struct is_integral_helper<long int> : true_type{};
	template<>
	struct is_integral_helper<long long int> : true_type{};
	template<>
	struct is_integral_helper<unsigned short int> : true_type{};
	template<>
	struct is_integral_helper<unsigned int> : true_type{};
	template<>
	struct is_integral_helper<unsigned long int> : true_type{};
	template<>
	struct is_integral_helper<unsigned long long int> : true_type{};

	// 							IS_INTEGRAL
	template<class T>
	struct is_integral : public is_integral_helper<typename remove_cv<T>::type>{};
};

#endif