#pragma once
#include <cstddef>
#include <type_traits>

#include "PackHolder.hpp"

namespace bmt::algorithms
{
#if 1 // like type_identity template types.
#if 1 // like type_identity<LikePackHolder> template types.
// copy_if
	template <
		template <typename> typename Checker_TT,
		LikePackHolder PackHolder_T,
		typename... Pack_T
	>
	struct copy_if;
// transform
	template <
		template <typename> typename Transformer_TT,
		LikePackHolder PackHolder_T,
		typename... Pack_T
	>
	struct transform;
#endif // like type_identity<LikePackHolder> template types.
// find_if
	template <
		template <typename> typename Checker_TT,
		typename... Pack_T
	>
	struct find_if;
// type_of
	template <size_t index, typename... Pack_T>
	struct type_of;
#endif // like "type_identity" template types.
#if 1 // compile-time functions.
	template <template<typename> typename Checker_TT, typename T, typename... Pack_T>
	consteval bool any_of_f();
	template <template<typename> typename Checker_TT, typename T, typename... Pack_T>
	consteval bool all_of_f();
	template <template<typename> typename Checker_TT, typename T, typename... Pack_T>
	consteval bool none_of_f();

	template <typename Sample_T, typename T, typename... Pack_T>
	consteval bool contains_f();

	template <typename Sample_T, typename T, typename... Pack_T>
	consteval size_t count_f();

	template <typename T, typename T2, typename... Pack_T>
	consteval bool is_unique_f();
	template <typename T>
	consteval bool is_unique_f();

	template <typename Sample_T, size_t _sub_index, size_t _counter, typename T, typename... Pack_T>
	consteval size_t index_of_f();

#endif // compile-time functions.
#if 1 // like integral_constant template types.
	template <template<typename> typename Checker_TT, typename... Pack_T>
	using any_of = std::bool_constant< any_of_f<Checker_TT, Pack_T...>() >;
	template <template<typename> typename Checker_TT, typename... Pack_T>
	using all_of = std::bool_constant< all_of_f<Checker_TT, Pack_T...>() >;
	template <template<typename> typename Checker_TT, typename... Pack_T>
	using none_of = std::bool_constant< none_of_f<Checker_TT, Pack_T...>() >;

	template <typename Sample_T, typename... Pack_T>
	using contains = std::bool_constant< contains_f<Sample_T, Pack_T...>() >;

	template <typename Sample_T, typename... Pack_T>
	using count = std::integral_constant<size_t, count_f<Sample_T, Pack_T...>() >;

	template <typename... Pack_T>
	using is_unique = std::bool_constant< is_unique_f<Pack_T...>() >;

	template <typename Sample_T, size_t _sub_index, typename... Pack_T>
	using index_of = std::integral_constant< size_t, index_of_f<Sample_T, _sub_index, 0, Pack_T...>() >;

	template <typename... Pack_T>
	using size_of = std::integral_constant<size_t, sizeof...(Pack_T)>;
#endif // like integral_constant template types.
#if 1 // run-time functions.
	template <typename Functor_T, typename T, typename... Pack_T>
	inline void forEachTypes(Functor_T f);

	template <typename Functor_T, size_t _counter, typename T, typename... Pack_T>
	inline void indexedForEachTypes(Functor_T f);

	template <typename Functor_T, typename T, typename... Pack_T>
	inline bool anyOfTypes(Functor_T f);

	template <typename Functor_T, typename T, typename... Pack_T>
	inline bool allOfTypes(Functor_T f);

	template <typename Functor_T, typename T, typename... Pack_T>
	inline bool noneOfTypes(Functor_T f);
#endif // run-time functions.
#if 1 // special algorithms for LikePackHolders.
// like bool_constant template types.
	template <LikePackHolder PackHolder_T>
	struct is_unique_pack;
	template <LikePackHolder PackHolder_T>
	inline constexpr bool is_unique_pack_v = is_unique_pack<PackHolder_T>::value;
// like integral_constant<size_t> template types.
	template <LikePackHolder PackHolder_T>
	using size_of_pack = typename PackHolder_T::place_t<algorithms::size_of>;
	template <LikePackHolder PackHolder_T>
	inline constexpr size_t size_of_pack_v = size_of_pack<PackHolder_T>::value;
// like type_identity<LikePackHolder> template types.
	template <LikePackHolder... Pack_T>
	struct unite_packs;
	template <LikePackHolder... Pack_T>
	using unite_packs_t = typename unite_packs<Pack_T...>::type;
#endif // special algorithms for LikePackHolders.
}
