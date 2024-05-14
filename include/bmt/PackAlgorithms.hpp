#pragma once
#include <concepts>
#include <limits>

#include "PackHolder.hpp"
#include "algorithms_internal.hpp"

namespace bmt
{
	template <typename... Pack_T>
	struct PackAlgorithms
	{
	// nested "integral_constant" types
		using size = std::integral_constant<size_t, sizeof...(Pack_T)>;
	// nested "type_identity" template types.
		template <template<typename> typename Checker_TT>
		using copy_if = algorithms::copy_if<Checker_TT, PackHolder<>, Pack_T...>;
		template <template<typename> typename Checker_TT>
		using copy_if_t = typename copy_if<Checker_TT>::type;

		template <template<typename>typename Extractor_TT>
		using transform = algorithms::transform<Extractor_TT, PackHolder<>, Pack_T...>;
		template <template<typename>typename Extractor_TT>
		using transform_t = typename transform<Extractor_TT>::type;

		template <template<typename> typename Checker_TT>
		using find_if = algorithms::find_if<Checker_TT, Pack_T...>;
		template <template<typename> typename Checker_TT>
		using find_if_t = typename find_if<Checker_TT>::type;

		template <size_t _index>
		using type_of = algorithms::type_of<_index, Pack_T...>;
		template <size_t _index>
		using type_of_t = typename type_of<_index>::type;
	// nested "bool_constant" template types
		template <template<typename> typename Checker_TT>
		using any_of = algorithms::any_of<Checker_TT, Pack_T...>;
		template <template<typename> typename Checker_TT>
		using all_of = algorithms::all_of<Checker_TT, Pack_T...>;
		template <template<typename> typename Checker_TT>
		using none_of = algorithms::none_of<Checker_TT, Pack_T...>;
		template <typename T>
		using contains = algorithms::contains<T, Pack_T...>;
		template <typename... AnotherPack_T>
		using includes = algorithms::all_of<contains, AnotherPack_T...>;
		template <typename... AnotherPack_T>
		using partly_includes = algorithms::any_of<contains, AnotherPack_T...>;
		template <typename... AnotherPack_T>
		using equal = std::is_same<PackHolder<Pack_T...>, PackHolder<AnotherPack_T...>>;
	// nested "integral_constant<size_t>" template types
		template <typename T>
		using count = algorithms::count<T, Pack_T...>;

		template <typename T, size_t sub_index = 0>
		using index_of = algorithms::index_of<T, sub_index, Pack_T...>;

	// compile-time variables.
		inline static constexpr size_t size_v = size::value;
	// compile-time template variables.
		template <template<typename> typename Checker_TT>
		inline static constexpr bool any_of_v = any_of<Checker_TT>::value;
		template <template<typename> typename Checker_TT>
		inline static constexpr bool all_of_v = all_of<Checker_TT>::value;
		template <template<typename> typename Checker_TT>
		inline static constexpr bool none_of_v = none_of<Checker_TT>::value;

		template <typename T>
		inline static constexpr bool contains_v = contains<T>::value;

		template <typename T>
		inline static constexpr size_t count_v = count<T>::value;

		template <typename T, size_t sub_index = 0>
		inline static constexpr size_t index_of_v = index_of<T, sub_index>::value;

		template <typename... AnotherTypesPack_T>
		inline static constexpr bool includes_v = includes<AnotherTypesPack_T...>::value;

		template <typename... AnotherPack_T>
		inline static constexpr bool partly_includes_v = partly_includes<AnotherPack_T...>::value;

		template <typename... AnotherPack_T>
		inline static constexpr bool equal_v = equal<AnotherPack_T...>::value;
	// run-time static methods
		template<typename Lambda_T>
		inline static void forEach(Lambda_T f)
		{ algorithms::forEachTypes<Lambda_T, Pack_T...>(f); }

		template<typename Lambda_T>
		inline static void indexedForEach(Lambda_T f)
		{ algorithms::indexedForEachTypes<Lambda_T, 0, Pack_T...>(f); }

		template <typename Lambda_T>
		inline static bool anyOf(Lambda_T f)
		{ return algorithms::anyOfTypes<Lambda_T,Pack_T...>(f); }

		template <typename Lambda_T>
		inline static bool allOf(Lambda_T f)
		{ return algorithms::allOfTypes<Lambda_T, Pack_T...>(f); }

		template <typename Lambda_T>
		inline static bool noneOf(Lambda_T f)
		{ return algorithms::noneOfTypes<Lambda_T, Pack_T...>(f); }
	};

	template <>
	struct PackAlgorithms<>
	{
	// nested "integral_constant" types
		using size = std::integral_constant<size_t, 0>;
	// nested "type_identity" template types.
		template <template<typename> typename>
		using copy_if = std::type_identity< PackHolder<> >;
		template <template<typename> typename>
		using copy_if_t = PackHolder<>;

		template <template<typename>typename>
		using transform = std::type_identity< PackHolder<> >;
		template <template<typename>typename>
		using transform_t = PackHolder<>;

		template <template<typename> typename>
		using find_if = std::type_identity< std::nullptr_t >;
		template <template<typename> typename>
		using find_if_t = std::nullptr_t;

		template <size_t _index>
		using type_of = std::nullptr_t;
		template <size_t _index>
		using type_of_t = std::nullptr_t;

	// nested "bool_constant" template types
		template <template<typename> typename>
		using any_of = std::false_type;
		template <template<typename> typename>
		using all_of = std::false_type;
		template <template<typename> typename>
		using none_of = std::true_type;
		template <typename>
		using contains = std::false_type;
		template <typename...>
		using includes = std::false_type;
		template <typename...>
		using partly_includes = std::false_type;
		template <typename... AnotherPack_T>
		using equal = std::is_same<PackHolder<>, PackHolder<AnotherPack_T...>>;
	// nested "integral_constant<size_t>" template types
		template <typename>
		using count = std::integral_constant<size_t, 0>;

		template <typename, size_t>
		using index_of = std::integral_constant<size_t, std::numeric_limits<size_t>::max() >;

	// compile-time variables.
		inline static constexpr size_t size_v = size::value;
	// compile-time template variables.
		template <template<typename> typename Checker_TT>
		inline static constexpr bool any_of_v = any_of<Checker_TT>::value;
		template <template<typename> typename Checker_TT>
		inline static constexpr bool all_of_v = all_of<Checker_TT>::value;
		template <template<typename> typename Checker_TT>
		inline static constexpr bool none_of_v = none_of<Checker_TT>::value;

		template <typename T>
		inline static constexpr bool contains_v = contains<T>::value;

		template <typename T>
		inline static constexpr size_t count_v = count<T>::value;

		template <typename T, size_t si>
		inline static constexpr size_t index_of_v = index_of<T, si>::value;

		template <typename... AnotherTypesPack_T>
		inline static constexpr bool includes_v = includes<AnotherTypesPack_T...>::value;

		template <typename... AnotherPack_T>
		inline static constexpr bool partly_includes_v = partly_includes<AnotherPack_T...>::value;

		template <typename... AnotherPack_T>
		inline static constexpr bool equal_v = equal<AnotherPack_T...>::value;
	// run-time static methods
		template<typename Lambda_T>
		inline static void forEach(Lambda_T) {}

		template<typename Lambda_T>
		inline static void indexedForEach(Lambda_T) {}

		template <typename Lambda_T>
		inline static bool anyOf(Lambda_T) { return false; }
		template <typename Lambda_T>
		inline static bool allOf(Lambda_T) { return false; }
		template <typename Lambda_T>
		inline static bool noneOf(Lambda_T) { return true; }
	};

	namespace impl_concepts
	{
		template < template< typename> typename >
		using check_singl_param_templ = void;
		template <template<template<typename> typename> typename>
		using check_singl_templ_param_templ = void;
		template < template< typename... > typename >
		using check_variadic_templ = void;
		template <template<typename, size_t> typename>
		using check_index_of_templ = void;
		template <template<size_t> typename>
		using check_singl_size_t_arg_templ = void;
	}
	template <typename T>
	concept LikePackAlgorithms =
		requires
		{
			typename T::size;
			T::size_v;

			typename impl_concepts::check_singl_templ_param_templ<T::template copy_if>;
			typename impl_concepts::check_singl_templ_param_templ<T::template transform>;
			typename impl_concepts::check_singl_templ_param_templ<T::template find_if>;
			typename impl_concepts::check_singl_templ_param_templ<T::template copy_if_t>;
			typename impl_concepts::check_singl_templ_param_templ<T::template transform_t>;
			typename impl_concepts::check_singl_templ_param_templ<T::template find_if_t>;
			typename impl_concepts::check_singl_size_t_arg_templ<T::template type_of>;
			typename impl_concepts::check_singl_size_t_arg_templ<T::template type_of_t>;

			typename impl_concepts::check_singl_templ_param_templ<T::template any_of>;
			typename impl_concepts::check_singl_templ_param_templ<T::template all_of>;
			typename impl_concepts::check_singl_templ_param_templ<T::template none_of>;
			typename impl_concepts::check_singl_param_templ<T::template contains>;
			typename impl_concepts::check_variadic_templ<T::template includes>;
			typename impl_concepts::check_variadic_templ<T::template partly_includes>;
			typename impl_concepts::check_variadic_templ<T::template equal>;
			typename impl_concepts::check_singl_param_templ<T::template count>;
			typename impl_concepts::check_index_of_templ<T::template index_of>;

			// how to check template variable? (use clang)
			//~ T::template any_of_v;
			//~ T::template all_of_v;
			//~ T::template none_of_v;
			//~ T::template contains_v;
			//~ T::template includes_v;
			//~ T::template partly_includes_v;
			//~ T::template equal_v;
			//~ T::template count_v;
			//~ T::template index_of_v;

			T::template forEach([]<typename>{});
			T::template indexedForEach([]<size_t, typename>{});
			{T::template anyOf([]<typename>{})} -> std::same_as<bool>;
			{T::template allOf([]<typename>{})} -> std::same_as<bool>;
			{T::template noneOf([]<typename>{})} -> std::same_as<bool>;
		};
		static_assert(LikePackAlgorithms<PackAlgorithms<>>);
}
