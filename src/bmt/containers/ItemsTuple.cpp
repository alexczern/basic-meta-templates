#include <bmt/containers/ItemsTuple.hpp>

namespace bmt::containers
{
#if 1 // helper impl
	template <size_t index, typename ItemType_T, typename... Pack_T>
	struct ItemTypeByIndex<index, ItemsTupleTail<ItemType_T, Pack_T...>>
	:	public ItemTypeByIndex<index - 1, ItemsTupleTail<Pack_T...>>
	{};

	template <typename ItemType_T, typename... Pack_T>
	struct ItemTypeByIndex<0, ItemsTupleTail<ItemType_T, Pack_T...>>
	:	public std::type_identity<ItemType_T>
	{};

	template <size_t index>
	struct ItemTypeByIndex<index, ItemsTupleTail<>>
	{
		static_assert(0 <= index, "Out of range!");
	};

#endif // helper impl
#if 1 // ItemsTupleTail impl
	template <typename ItemType_T, typename... Pack_T>
		template <typename T, size_t sub_index>
		inline T& ItemsTupleTail<ItemType_T, Pack_T...>
		::get()
		{
			if constexpr(std::is_same_v<T, ItemType_T>)
			{
				if constexpr(sub_index == 0)
					return item;
				else if constexpr(sizeof...(Pack_T) > 0)
					return NextTuple::template get<T, (sub_index - 1)>();
				else
					static_assert(sizeof...(Pack_T) > 0, "Error! Item not found!");
			}
			else if constexpr(sizeof...(Pack_T) > 0)
				return NextTuple::template get<T, sub_index>();
			else
				static_assert(sizeof...(Pack_T) > 0, "Error! Item not found!");
		}

	template <typename ItemType_T, typename... Pack_T>
		template <typename T, size_t sub_index>
		inline const T& ItemsTupleTail<ItemType_T, Pack_T...>
		::get() const
		{
			if constexpr(std::is_same_v<T, ItemType_T>)
			{
				if constexpr(sub_index == 0)
					return item;
				else if constexpr(sizeof...(Pack_T) > 0)
					return NextTuple::template get<T, (sub_index - 1)>();
				else
					static_assert(sizeof...(Pack_T) > 0, "Error! Item not found!");
			}
			else if constexpr(sizeof...(Pack_T) > 0)
				return NextTuple::template get<T, sub_index>();
			else
				static_assert(sizeof...(Pack_T) > 0, "Error! Item not found!");
		}

	template <typename ItemType_T, typename... Pack_T>
		template <size_t index>
		ItemTypeByIndex<index, ItemsTupleTail<ItemType_T, Pack_T...>>::type& ItemsTupleTail<ItemType_T, Pack_T...>
		:: get()
		{
			if constexpr(index > 0)
				return NextTuple::template get<index - 1>();
			else
				return item;
		}

	template <typename ItemType_T, typename... Pack_T>
		template <size_t index>
		const ItemTypeByIndex<index, ItemsTupleTail<ItemType_T, Pack_T...>>::type& ItemsTupleTail<ItemType_T, Pack_T...>
		:: get() const
		{
			if constexpr(index > 0)
				return NextTuple::template get<index - 1>();
			else
				return item;
		}

	template <typename ItemType_T, typename... Pack_T>
		inline void ItemsTupleTail<ItemType_T, Pack_T...>
		::forEach(auto lam)
		{
			lam(item);
			if constexpr(not_last())
				next().forEach(lam);
		}

	template <typename ItemType_T, typename... Pack_T>
		inline void ItemsTupleTail<ItemType_T, Pack_T...>
		::adjacentForEach(auto lam)
		{
			if constexpr(not_last())
			{
				lam(item, NextTuple::item);
				next().adjacentForEach(lam);
			}
		}

	template <typename ItemType_T, typename... Pack_T>
		template <size_t index>
		inline void ItemsTupleTail<ItemType_T, Pack_T...>
		::indexedForEach(auto lam)
		{
			lam.template operator()<index>(item);
			if constexpr(not_last())
				next().template indexedForEach<(index + 1)>(lam);
		}

	template <typename ItemType_T, typename... Pack_T>
		inline bool ItemsTupleTail<ItemType_T, Pack_T...>
		::anyOf(auto lam)
		{
			if (lam(item))
				return true;
			else if constexpr (not_last())
				return next().anyOf(lam);
			else
				return false;
		}

	template <typename ItemType_T, typename... Pack_T>
		inline bool ItemsTupleTail<ItemType_T, Pack_T...>
		::allOf(auto lam)
		{
			if (lam(item))
			{
				if constexpr(not_last())
					return next().allOf(lam);
				else
					return true;
			}
			else
				return false;
		}

	template <typename ItemType_T, typename... Pack_T>
		inline bool ItemsTupleTail<ItemType_T, Pack_T...>
		::noneOf(auto lam)
		{
			if (lam(item))
				return false;
			else if constexpr(not_last())
				return next().noneOf(lam);
			else
				return true;
		}

#endif // ItemsTupleTail impl
}
