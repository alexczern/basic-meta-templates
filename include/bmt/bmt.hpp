// P. S. Comments are partially goolge-translated, as the author is not native english user.
// Use all "bmt" definitions from this header file.
// ATTENTION: Do not use internal implementations as they may change in future versions.
#pragma once
#include "algorithms_internal.hpp"

#include "PackHolder.hpp"
#include "PackAlgorithms.hpp"
#include "TypesPack.hpp"

#include "containers/containers.hpp"

namespace bmt
{
// Concepts.
	using bmt::LikePackHolder;
	using bmt::LikePackAlgorithms;
	using bmt::LikeTypesPack;

#if 1 // Primary template types.
	using bmt::PackHolder;
	/*	PackHolder<Pack_T...> members:
		// [template types]
			place_t<template<typename...>typename VariadicTempl_T> -> VariadicTempl_T<Pack_T...>;
			front_expand_t<typename... APack_T> -> PackHolder<APack_T..., Pack_T...>;
			back_expand_t<typename... APack_T> -> PackHolder<Pack_T..., APack_T...>;
	*/
	using bmt::PackAlgorithms;
	/*	PackAlgorithms<Pack_T...> members:
	(type_identity/integral_constant has helper type/variable template "_t"/"_v")
		// [like integral_constant<size_t>]
			size
		// [like type_identity][template types]
			copy_if<template<typename> typename Checker_TT>
				// copy_if_t -> copy_if::type -> PackHolder
			transform<template<typename> typename Transformer_TT>
				// transform_t -> transform::type -> PackHolder
			find_if<template<typename> typename Checker_TT> -> auto
				// find_if_t -> find_if::type -> PackHolder

		// [like bool_constant][template types]
			any_of<template<typename> typename Checker_TT>
			all_of<template<typename> typename Checker_TT>
			none_of<template<typename> typename Checker_TT>
			contains<typename>
			includes<typename...>
			partly_includes<typename...>
			equal<typename...>

		// [like integral_constant<size_t>][template types]
			count<typename>
			index_of<typename, size_t = 0>

		// [run-time][inline static][methods]
			forEach([]<typename>{}) -> void
			indexedForEach([]<size_t, typename>{}) -> void
			anyOf([]<typename>{}) -> bool
			allOf([]<typename>{}) -> bool
			noneOf([]<typename>{}) -> bool
	*/
	using bmt::TypesPack;
	/*	TypesPack<Pack_T...> some members (also inherit PackHolder & PackAlgorithms members):
		// [like type_identity][template types]
			front_expand_pack<LikePackHolder>
				// front_expand_pack_t -> front_expand_pack::type -> TypesPack
			back_expand_pack<LikePackHolder>
				// back_expand_pack_t -> back_expand_pack_t::type -> TypesPack
			copy_if<template<typename> typename Checker_TT>
				// copy_if_t -> copy_if::type -> TypesPack
			transform<template<typename> typename Transformer_TT>
				// transform_t -> transform::type -> TypesPack
		// [like bool_constant][template types]
			includes_pack<LikePackHolder>
			partly_includes_pack<LikePackHolder>
	*/
#endif // Primary template types.
#if 1 // special algorithms for LikePackHolders
	// like bool_constants
	using algorithms::is_unique_pack;
	using algorithms::is_unique_pack_v;
	// like integral_constant<size_t>
	using algorithms::size_of_pack;
	using algorithms::size_of_pack_v;
	// like type_identity template types
	using algorithms::unite_packs;
	using algorithms::unite_packs_t;
#endif // special algorithms for LikePackHolders
#if 1 // Containers template types.
	using containers::TypedMap;
	/* TypedMap<LikePackHolder, typename DataType_T> members:
	(all "like integral_constant" has helper variable (template) "*_v")
		// [integral_constant<size_t>]
			size

		// [like bool_constant][template types]
			contains<typename>

		// [like integral_constant<size_t>][template types]
			count<typename>

		// [run-time][methods]
			at<typename T>() -> T&
			forEach([]<typename TypedKey_T>(DataType_T&){}) -> void
	*/
	using containers::TypedMultiMap;
	/* TypedMultiMap<LikePackHolder, typename> members:
	(all "like integral_constant" has helper variable (template) "*_v")
		// [integral_constant<size_t>]
			size

		// [like bool_constant][template types]
			contains<typename>

		// [like integral_constant<size_t>][template types]
			count<typename>

		// [run-time][methods]
			at<typename T, size_t sub_index = 0>() -> T&
	*/
	using containers::ItemsTuple;
	/* ItemsTuple<Pack_T...> members:
	(all "like integral_constant" has helper variable (template) "*_v")
		// [ItemsTupleTail][type]
			NextTuple

		// [integral_constant<size_t>]
			size

		// [like bool_constant][template types]
			contains<typename>

		// [like integral_constant<size_t>][template types]
			count<typename>

		// [compile-time][static methods]
			not_last() -> consteval bool

		// [run-time][methods]
			next() -> NextTuple&
			get<typename T, size_t sub_index = 0>() -> T&
			get<size_t index>() -> auto&
			forEach([](auto&){}) -> void
			adjacentForEach([](auto&, auto&){}) -> void
			indexedForEach([](auto&)<size_t index>{}) -> void
			anyOf([](auto&) -> bool {}) -> bool
			allOf([](auto&) -> bool {}) -> bool
			noneOf([](auto&) -> bool {}) -> bool
	*/
	using containers::TypedHeteroMap;
	/* TypedHeteroMap<LikePackHolder, template<typename> typename Transformer_TT> members:
	(all "like integral_constant" has helper variable (template) "*_v")
		// [integral_constant<size_t>]
			size

		// [like bool_constant][template types]
			contains<typename>

		// [like integral_constant<size_t>][template types]
			count<typename>

		// [run-time][methods]
			at<typename>() -> auto&;
	*/
	using containers::UnitedTypes;
	/* UnitedTypes<Pack_T...>. Just inherits all types.
		Has default copy-constructor (for itself and variadic arguments) and default move-constructor (for itself).
	*/
#endif // Containers template types.
}
