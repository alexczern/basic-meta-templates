#pragma once
#include <cstddef>
#include <type_traits>

#include <bmt/PackHolder.hpp>
#include <bmt/PackAlgorithms.hpp>

namespace bmt::containers
{

	template <typename... Pack_T>
	struct ItemsHolder;

	template <typename T, size_t sub_index = 0, typename... Pack_T>
	struct ItemsHolderByType;

	template <size_t index, typename... Pack_T>
	struct ItemsHolderByIndex;

	template <typename... Pack_T>
	class ItemsTuple
	:	private PackAlgorithms<Pack_T...>
	{
		using Base = PackAlgorithms<Pack_T...>;
		ItemsHolder<Pack_T...> items;
	public:
		ItemsTuple() = default;
		ItemsTuple(const ItemsTuple&) = default;
		ItemsTuple(ItemsTuple&&) = default;

		ItemsTuple(const Pack_T&... args)
		:	items(args...) {}

		using Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods
		template <typename ItemType_T, size_t sub_index = 0>
		ItemType_T& get();

		template <size_t index>
		ItemsHolderByIndex<index, Pack_T...>::type::type& get();

		inline void forEach(auto func);
		inline void indexedForEach(auto func);
		inline bool anyOf(auto func);
		inline bool allOf(auto func);
		inline bool noneOf(auto func);

	};
	template <>
	class ItemsTuple<>
	:	private PackAlgorithms<>
	{
		using Base = PackAlgorithms<>;
	protected:
		ItemsTuple() = default;
		ItemsTuple(const ItemsTuple&) = default;
		ItemsTuple(ItemsTuple&&) = default;

	public:
		using Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods
		template <typename ItemType_T, size_t sub_index = 0>
		ItemType_T& get() = delete;

		template <size_t _index>
		void get() = delete;

		inline void forEach(auto f) = delete;
		inline void indexedForEach(auto f) = delete;
		inline bool anyOf(auto f) = delete;
		inline bool allOf(auto f) = delete;
		inline bool noneOf(auto f) = delete;

	};
}
