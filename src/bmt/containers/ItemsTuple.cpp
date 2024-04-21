#include <bmt/containers/ItemsTuple.hpp>

namespace bmt::containers
{
#if 1 // ItemsHolder impl
	template <typename ItemType_T, typename... Pack_T>
	struct ItemsHolder<ItemType_T, Pack_T...>
	:	public ItemsHolder<Pack_T...>
	{
	private:
		using NextHolder = ItemsHolder<Pack_T...>;
	public:
		using type = ItemType_T;
		ItemType_T item{};

		ItemsHolder() = default;
		ItemsHolder(const ItemsHolder&) = default;
		ItemsHolder(ItemsHolder&&) = default;

		ItemsHolder(const ItemType_T &first, const Pack_T&... args)
		:	ItemsHolder<Pack_T...>(args...),
			item(first) {}

		inline void forEach(auto func)
		{
			func(item);
			NextHolder::forEach(func);
		}

		template <size_t I = 0>
		inline void indexedForEach(auto func)
		{
			func.template operator()<I>(item);
			NextHolder::template indexedForEach<(I + 1)>(func);
		}

		inline bool anyOf(auto &func)
		{
			if (func(item))
				return true;
			else
				return NextHolder::anyOf(func);
		}

		inline bool allOf(auto &func)
		{
			if (func(item))
				return NextHolder::allOf(func);
			else
				return false;
		}

		inline bool noneOf(auto &func)
		{
			if (func(item))
				return false;
			else
				return NextHolder::noneOf(func);
		}
	};
	template <typename ItemType_T>
	struct ItemsHolder<ItemType_T>
	{
		using type = ItemType_T;
		ItemType_T item{};

		ItemsHolder() = default;
		ItemsHolder(const ItemsHolder&) = default;
		ItemsHolder(ItemsHolder&&) = default;

		ItemsHolder(const ItemType_T &last)
		:	item(last) {}

		inline void forEach(auto &func)
		{
			func(item);
		}

		template <size_t I = 0>
		inline void indexedForEach(auto &func)
		{
			func.template operator()<I>(item);
		}

		inline bool anyOf(auto &func)
		{
			return func(item);
		}

		inline bool allOf(auto &func)
		{
			return func(item);
		}

		inline bool noneOf(auto &func)
		{
			return false == func(item);
		}
	};
#endif // ItemsHolderImpl
#if 1 // ItemsHolderByType impl
// "skip" recursion.
	template <typename T, size_t sub_index, typename _Ignored_T, typename... Pack_T>
	struct ItemsHolderByType<T, sub_index, _Ignored_T, Pack_T...>
	:	public ItemsHolderByType<T, sub_index, Pack_T...> {};
// "decrement sub_index" recursion.
	template <typename T, size_t sub_index, typename... Pack_T>
	struct ItemsHolderByType<T, sub_index, T, Pack_T...>
	:	public ItemsHolderByType<T, (sub_index - 1), Pack_T...> {};
// good result
	template <typename T, typename... Pack_T>
	struct ItemsHolderByType<T, 0, T, Pack_T...>
	:	public std::type_identity< ItemsHolder<T, Pack_T...> > {};
// bad result
	template <typename T, size_t I>
	struct ItemsHolderByType<T, I>
	{ using type = ItemsHolder<>; };

#endif // ItemsHolderByType impl
#if 1 // ItemsHolderByIndex impl
// "decrement index" recursion.
	template <size_t index, typename _Ignored_T, typename... Pack_T>
		// [AMOMALY][AMBIGUOUS]
		// without next "requires" compiler (gnu g++ Debian 12.2.0)
		// return "ambiguous template instantiation"
		// (?Why does not it choose ItemsHolderByIndex<0, Pack_T>?).
		// I really want to delete this "requires"...
		requires (index != 0)
	struct ItemsHolderByIndex<index, _Ignored_T, Pack_T...>
	{
		using type = typename ItemsHolderByIndex<(index - 1), Pack_T...>::type;
	};
// good result
	template <typename... Pack_T>
	struct ItemsHolderByIndex<0, Pack_T...>
	:	public std::type_identity< ItemsHolder<Pack_T...> > {};
// bad result
	template <size_t I>
	struct ItemsHolderByIndex<I>
	{ using type = ItemsHolder<>; };


#endif // ItemsHolderByIndex impl
#if 1 // ItemsTuple impl
	template <typename... Pack_T>
		template <typename ItemType_T, size_t sub_index>
		ItemType_T& ItemsTuple<Pack_T...>::get()
		{
			using HolderType = typename ItemsHolderByType<ItemType_T, sub_index,  Pack_T...>::type;
			static_assert(false == std::is_same_v<HolderType, ItemsHolder<> >, "Item not found!");
			return items.HolderType::item;
		}
	template <typename... Pack_T>
		template <size_t index>
		ItemsHolderByIndex<index, Pack_T...>::type::type& ItemsTuple<Pack_T...>::get()
		{
			using HolderType = ItemsHolderByIndex<index, Pack_T...>::type;
			static_assert(false == std::is_same_v<HolderType, ItemsHolder<> >, "Item not found!");
			return items.HolderType::item;
		}

	template <typename... Pack_T>
		inline void ItemsTuple<Pack_T...>::forEach(auto func)
		{
			items.forEach(func);
		}

	template <typename... Pack_T>
		inline void ItemsTuple<Pack_T...>::indexedForEach(auto l)
		{
			items.indexedForEach(l);
		}

	template <typename... Pack_T>
		inline bool ItemsTuple<Pack_T...>::anyOf(auto func)
		{
			return items.template anyOf(func);
		}
	template <typename... Pack_T>
		inline bool ItemsTuple<Pack_T...>::allOf(auto func)
		{
			return items.template allOf(func);
		}
	template <typename... Pack_T>
		inline bool ItemsTuple<Pack_T...>::noneOf(auto func)
		{
			return items.template noneOf(func);
		}

#endif // ItemsTuple impl
}
