#pragma once
#include <cstddef>
#include <type_traits>

#include <bmt/PackHolder.hpp>
#include <bmt/PackAlgorithms.hpp>

namespace bmt::containers
{
#if 1 // helper
	template <size_t index, typename Tuple_T>
	struct ItemTypeByIndex;
#endif // helper
#if 1 // ItemsTupleTail
	template <typename...>
	class ItemsTupleTail;

	template <> class ItemsTupleTail<> {};

	template <typename ItemType_T, typename... Pack_T>
	class ItemsTupleTail<ItemType_T, Pack_T...>
	:	public ItemsTupleTail<Pack_T...>
	{
	public:
		using NextTuple = ItemsTupleTail<Pack_T...>;

		ItemType_T item {};

		ItemsTupleTail() = default;
		ItemsTupleTail(const ItemsTupleTail&) = default;
		ItemsTupleTail(ItemsTupleTail&&) = default;
		ItemsTupleTail& operator=(const ItemsTupleTail&) = default;
		ItemsTupleTail& operator=(ItemsTupleTail&&) = default;

		ItemsTupleTail(const ItemType_T &first, const Pack_T&... args)
		:	ItemsTupleTail<Pack_T...>(args...),
			item(first) {}

		inline static consteval bool not_last() { return sizeof...(Pack_T) != 0; }
		NextTuple& next() { return *this; }
		const NextTuple& next() const { return *this; }

	// run-time methods
		template <typename T, size_t sub_index = 0>
		inline T& get();

		template <typename T, size_t sub_index = 0>
		inline const T& get() const;

		template <size_t index>
		inline typename ItemTypeByIndex<index, ItemsTupleTail<ItemType_T, Pack_T...> >::type& get();

		template <size_t index>
		inline const typename ItemTypeByIndex<index, ItemsTupleTail<ItemType_T, Pack_T...> >::type& get() const;

		inline void forEach(auto lam);
		inline void adjacentForEach(auto lam);
		template <size_t I = 0>
		inline void indexedForEach(auto lam);
		inline bool anyOf(auto lam);
		inline bool allOf(auto lam);
		inline bool noneOf(auto lam);

	};
#endif // ItemsTupleTail
#if 1 // ItemsTuple (Head)
	template <typename... Pack_T>
	class ItemsTuple
	:	public ItemsTupleTail<Pack_T...>,
		private PackAlgorithms<Pack_T...>
	{
	private:
		using Tail = ItemsTupleTail<Pack_T...>;
		using Base = PackAlgorithms<Pack_T...>;

	public:
		ItemsTuple() = default;
		ItemsTuple(const ItemsTuple&) = default;
		ItemsTuple(ItemsTuple&&) = default;
		ItemsTuple& operator=(const ItemsTuple&) = default;
		ItemsTuple& operator=(ItemsTuple&&) = default;

		ItemsTuple(const Pack_T&... args)
		:	Tail(args...) {}

		using typename Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

		using Tail::forEach;
		using Tail::indexedForEach;
		using Tail::anyOf;
		using Tail::allOf;
		using Tail::noneOf;

	};

// Empty specialization.
	template <>
	class ItemsTuple<>
	:	private PackAlgorithms<>
	{
		using Base = PackAlgorithms<>;
	protected:
		ItemsTuple() = default;
		ItemsTuple(const ItemsTuple&) = default;
		ItemsTuple(ItemsTuple&&) = default;
		ItemsTuple& operator=(const ItemsTuple&) = default;
		ItemsTuple& operator=(ItemsTuple&&) = default;

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
#endif // ItemsTuple (Head)
}
