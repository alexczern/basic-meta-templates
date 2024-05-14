#pragma once
#include <cstddef>
#include <type_traits>

#include "PackHolder.hpp"
#include "algorithms_internal.hpp"
#include "PackAlgorithms.hpp"

namespace bmt
{
// Concepts.
#if 1
	namespace impl
	{
		template <template<typename> typename>
		using check_singl_param_templ = void;

		template <template<template<typename> typename> typename>
		using check_singl_templ_param_templ = void;
	}

	template <typename T>
	concept LikeTypesPack =
		requires
		{
			requires std::is_empty_v<T>;
			requires LikePackHolder<T>;
			requires LikePackAlgorithms<T>;
			typename impl::check_singl_param_templ<T::template front_expand_pack>;
			typename impl::check_singl_param_templ<T::template back_expand_pack>;
			typename impl::check_singl_param_templ<T::template front_expand_pack_t>;
			typename impl::check_singl_param_templ<T::template back_expand_pack_t>;
			typename impl::check_singl_param_templ<T::template includes_pack>;
			typename impl::check_singl_param_templ<T::template partly_includes_pack>;

			// how to check template variable? (use clang)
			//~ T::template includes_pack_v;
			//~ T::template partly_includes_pack_v;
		};
#endif
// TypesPack
	template <typename... Pack_T>
	class TypesPack
	:	public PackAlgorithms<Pack_T...>,
		public PackHolder<Pack_T...>
	{
		using BaseAlgorithms = PackAlgorithms<Pack_T...>;
		using BaseHolder = PackHolder<Pack_T...>;
	public:
	// nested "type_identity" template types.
		template <LikePackHolder AnotherPackHolder_T>
		struct front_expand_pack
		{
			using type = typename AnotherPackHolder_T::template place_t<BaseHolder::template front_expand_t>::template place_t<TypesPack>;
		};
		template <LikePackHolder AnotherPackHolder_T>
		using front_expand_pack_t = typename front_expand_pack<AnotherPackHolder_T>::type;

		template <LikePackHolder AnotherPackHolder_T>
		struct back_expand_pack
		{
			using type = typename AnotherPackHolder_T::template place_t<BaseHolder::template back_expand_t>::template place_t<TypesPack>;
		};
		template <LikePackHolder AnotherPackHolder_T>
		using back_expand_pack_t = typename back_expand_pack<AnotherPackHolder_T>::type;

		template <template<typename> typename Checker_TT>
		struct copy_if
		{
			using type = typename BaseAlgorithms::template copy_if_t<Checker_TT>::template place_t<TypesPack>;
		};
		template <template<typename> typename Checker_TT>
		using copy_if_t = typename copy_if<Checker_TT>::type;

		template <template<typename>typename Extractor_TT>
		struct transform
		{
			using type = typename BaseAlgorithms::template transform_t<Extractor_TT>::template place_t<TypesPack>;
		};
		template <template<typename>typename Extractor_TT>
		using transform_t = typename transform<Extractor_TT>::type;

	// nested "bool_constant" template types
		template <LikePackHolder AnotherPackHolder_T>
		using includes_pack = typename AnotherPackHolder_T::template place_t<BaseAlgorithms::template includes>;
		using BaseAlgorithms::partly_includes;
		template <LikePackHolder AnotherPackHolder_T>
		using partly_includes_pack = typename AnotherPackHolder_T::template place_t<BaseAlgorithms::template partly_includes>;

	// compile-time template variables.
		template <LikePackHolder AnotherPackHolder_T>
		inline static constexpr bool includes_pack_v = includes_pack<AnotherPackHolder_T>::value;
		template <LikePackHolder AnotherPackHolder_T>
		inline static constexpr bool partly_includes_pack_v = partly_includes_pack<AnotherPackHolder_T>::value;
	};
	static_assert(LikeTypesPack<TypesPack<>>);
}
