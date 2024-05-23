#pragma once
#include <cstddef>
#include <type_traits>

#include <bmt/PackHolder.hpp>
#include <bmt/PackAlgorithms.hpp>
#include <bmt/algorithms_internal.hpp>

#include "ItemsTuple.hpp"

namespace bmt::containers
{
	template <LikePackHolder PackHolder_T, template<typename> typename Transformer_TT>
		requires algorithms::is_unique_pack_v<PackHolder_T>
	class TypedHeteroMap
	:	private PackHolder_T::template place_t<PackAlgorithms>
	{
	private:
		using Base = typename PackHolder_T::template place_t<PackAlgorithms>;
		typename Base::template transform_t<Transformer_TT>::template place_t<ItemsTuple> itemsTuple;

	public:
		TypedHeteroMap() = default;
		TypedHeteroMap(const TypedHeteroMap&) = default;
		TypedHeteroMap(TypedHeteroMap&&) = default;
		TypedHeteroMap& operator =(const TypedHeteroMap&) = default;
		TypedHeteroMap& operator =(TypedHeteroMap&&) = default;

		using typename Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods.
		template <typename Key_T>
		typename Transformer_TT<Key_T>::type& at();

		template <typename Key_T>
		const typename Transformer_TT<Key_T>::type& at() const;

	};

	template <template <typename...> typename PackHolder_VT, template<typename> typename Transformer_TT>
		requires LikePackHolder<PackHolder_VT<>>
	class TypedHeteroMap<PackHolder_VT<>, Transformer_TT>
	:	private PackAlgorithms<>
	{
	private:
		using Base = PackAlgorithms<>;

	protected:
		TypedHeteroMap() = default;
		TypedHeteroMap(const TypedHeteroMap&) = default;
		TypedHeteroMap(TypedHeteroMap&&) = default;
		TypedHeteroMap& operator =(const TypedHeteroMap&) = default;
		TypedHeteroMap& operator =(TypedHeteroMap&&) = default;

	public:
		using Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods.
		template <typename Key_T>
		typename Transformer_TT<Key_T>::type& at() = delete;

		template <typename Key_T>
		const typename Transformer_TT<Key_T>::type& at() const = delete;

	};

	//~ class TypedHeteroMultiMap;
}
