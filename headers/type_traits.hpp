#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{

// remove const
template <class T> struct remove_const			{ typedef T type; };
template <class T> struct remove_const<const T>	{ typedef T type; };

// is_integral
template <typename T, T v>
struct integral_constant { static const T value = v; };

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <typename T>	struct __libcppis_integral						: public false_type	{ };
template <>				struct __libcppis_integral<bool>				: public true_type	{ };
template <>				struct __libcppis_integral<char>				: public true_type	{ };
template <>				struct __libcppis_integral<signed char>			: public true_type	{ };
template <>				struct __libcppis_integral<unsigned char>		: public true_type	{ };
template <>				struct __libcppis_integral<wchar_t>				: public true_type	{ };
template <>				struct __libcppis_integral<short>				: public true_type	{ };
template <>				struct __libcppis_integral<unsigned short>		: public true_type	{ };
template <>				struct __libcppis_integral<int>					: public true_type	{ };
template <>				struct __libcppis_integral<unsigned int>		: public true_type	{ };
template <>				struct __libcppis_integral<long>				: public true_type	{ };
template <>				struct __libcppis_integral<unsigned long>		: public true_type	{ };
template <>				struct __libcppis_integral<long long>			: public true_type	{ };
template <>				struct __libcppis_integral<unsigned long long>	: public true_type	{ };

template <typename T>	struct is_integral
	: public __libcppis_integral<typename remove_const<T>::type> { };

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

} // ft

#endif
