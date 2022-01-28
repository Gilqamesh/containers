#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

// remove const
template <class T> struct remove_const			{ typedef T type; };
template <class T> struct remove_const<const T>	{ typedef T type; };

// remove reference
template <class T> struct remove_reference       { typedef T type; };
template <class T> struct remove_reference<T &>  { typedef T type; };

// is_integral
template <typename T, T v>
struct integral_constant { static const T value = v; };

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <typename T>	struct is_integral_base						: public false_type	{ };
template <>				struct is_integral_base<bool>				: public true_type	{ };
template <>				struct is_integral_base<char>				: public true_type	{ };
template <>				struct is_integral_base<signed char>		: public true_type	{ };
template <>				struct is_integral_base<unsigned char>		: public true_type	{ };
template <>				struct is_integral_base<wchar_t>			: public true_type	{ };
template <>				struct is_integral_base<short>				: public true_type	{ };
template <>				struct is_integral_base<unsigned short>		: public true_type	{ };
template <>				struct is_integral_base<int>				: public true_type	{ };
template <>				struct is_integral_base<unsigned int>		: public true_type	{ };
template <>				struct is_integral_base<long>				: public true_type	{ };
template <>				struct is_integral_base<unsigned long>		: public true_type	{ };
template <>				struct is_integral_base<long long>			: public true_type	{ };
template <>				struct is_integral_base<unsigned long long>	: public true_type	{ };

template <typename T>	struct is_integral
	: public is_integral_base<typename remove_const<T>::type> { };

// enable_if
template <bool B, typename T = void>
struct enable_if { };

template <typename T>
struct enable_if<true, T> { typedef T type; };

// is_same
template <class T, class U>
struct is_same : false_type { };

template <class T>
struct is_same<T, T> : true_type { };

// is_const
template <class T> struct is_const			: false_type { };
template <class T> struct is_const<const T> : true_type  { };

} // ft

#endif
