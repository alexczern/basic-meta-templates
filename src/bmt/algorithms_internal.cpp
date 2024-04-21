#include <bmt/algorithms_internal.hpp>

namespace bmt::algorithms
{
#if 1 // like type_identity template types impl.
#if 1 // like type_identity<LikePackHolder> template types impl.
// copy if
	template <
		template <typename> typename Checker_TT,
		LikePackHolder PackHolder_T,
		typename ItemType_T,
		typename... Pack_T
	>
		requires (true == Checker_TT<ItemType_T>::value)
	struct copy_if<Checker_TT, PackHolder_T, ItemType_T, Pack_T...>
	// recursion and type addition.
	:	public copy_if<
			Checker_TT,
			typename PackHolder_T::back_expand_t<ItemType_T>,
			Pack_T...
		>	{};

	template <
		template <typename> typename Checker_TT,
		LikePackHolder PackHolder_T,
		typename ItemType_T,
		typename... Pack_T
	>
		requires (false == Checker_TT<ItemType_T>::value)
	struct copy_if<Checker_TT, PackHolder_T, ItemType_T, Pack_T...>
	// recursion.
	:	public copy_if<
			Checker_TT,
			PackHolder_T,
			Pack_T...
		>	{};

	template <
		template <typename> typename Checker_TT,
		LikePackHolder PackHolder_T
	>
	struct copy_if<Checker_TT, PackHolder_T>
	// recursion end.
	:	public std::type_identity<PackHolder_T> {};

// transform
	template <
		template <typename> typename Transformer_TT,
		LikePackHolder PackHolder_T,
		typename ItemType_T,
		typename... Pack_T
	>
	struct transform<Transformer_TT, PackHolder_T, ItemType_T, Pack_T...>
	// recursion.
	:	public transform<
			Transformer_TT,
			typename PackHolder_T::back_expand_t<typename Transformer_TT<ItemType_T>::type>,
			Pack_T...
		>	{};

	template <
		template <typename> typename Transformer_TT,
		LikePackHolder PackHolder_T
	>
	struct transform<Transformer_TT, PackHolder_T>
	// recursion end.
	:	public std::type_identity<PackHolder_T>	{};

#endif // like type_identity<LikePackHolder> template types impl.
// find_if
	template <
		template <typename> typename Checker_TT,
		typename ItemType_T,
		typename... Pack_T
	>
		requires (true == Checker_TT<ItemType_T>::value)
	struct find_if<Checker_TT, ItemType_T, Pack_T...>
	// good result, recursion end.
	:	public std::type_identity<ItemType_T> {};

	template <
		template <typename> typename Checker_TT,
		typename ItemType_T,
		typename... Pack_T
	>
		requires (false == Checker_TT<ItemType_T>::value)
	struct find_if<Checker_TT, ItemType_T, Pack_T...>
	// recursion.
	:	public find_if<Checker_TT, Pack_T...> {};

	template <template <typename> typename Checker_TT>
	struct find_if<Checker_TT>
	// bad result, recursion end..
	:	public std::type_identity<std::nullptr_t> {};

// type_of
	template <typename ItemType_T, typename... Pack_T>
	struct type_of<0, ItemType_T, Pack_T...>
	// good result, recursion end.
	:	public std::type_identity<ItemType_T> {};

	template <size_t _i>
	struct type_of<_i>
	// bad result, recursion end.
	:	public std::type_identity<std::nullptr_t>	{};

	template <size_t _index, typename RudimentmType_T, typename... Pack_T>
	struct type_of<_index, RudimentmType_T, Pack_T...>
	// recursion.
	:	public type_of<(_index - 1), Pack_T...>	{};

#endif // like type_identity template types impl.

#if 1 // compile-time functions impl.
	template <template<typename> typename Checker_TT, typename T, typename... Pack_T>
	consteval bool any_of_f()
	{
		if constexpr( sizeof...(Pack_T) > 0)
		{
			if constexpr(Checker_TT<T>::value)
				return true;
			else
				return any_of_f<Checker_TT, Pack_T...>();
		}
		else
			return Checker_TT<T>::value;
	}

	template <template<typename> typename Checker_TT, typename T, typename... Pack_T>
	consteval bool all_of_f()
	{
		if constexpr( sizeof...(Pack_T) > 0 )
		{
			if constexpr(Checker_TT<T>::value)
				return all_of_f<Checker_TT, Pack_T...>();
			else
				return false;
		}
		else
			return Checker_TT<T>::value;
	}

	template <template<typename> typename Checker_TT, typename T, typename... Pack_T>
	consteval bool none_of_f()
	{
		if constexpr( sizeof...(Pack_T) > 0 )
		{
			if constexpr(Checker_TT<T>::value)
				return false;
			else
				return none_of_f<Checker_TT, Pack_T...>();
		}
		else
			return false == Checker_TT<T>::value;
	}

	template <typename Sample_T, typename T, typename... Pack_T>
	consteval bool contains_f()
	{
		if constexpr (std::is_same_v<Sample_T, T>)
			return true;
		else if constexpr( sizeof...(Pack_T) != 0)
			return contains_f<Sample_T, Pack_T...>();
		else
			return false;
	}

	template <typename Sample_T, typename T, typename... Pack_T>
	consteval size_t count_f()
	{
		if constexpr (std::is_same_v<Sample_T, T>)
		{
			if constexpr( sizeof...(Pack_T) > 0 )
				return 1 + count_f<Sample_T, Pack_T...>();
			else
				return 1;
		}
		else
		{
			if constexpr( sizeof...(Pack_T) > 0 )
				return count_f<Sample_T, Pack_T...>();
			else
				return 0;
		}
	}

	template <typename First_T, typename Second_T, typename... Pack_T>
	consteval bool is_unique_f()
	{
		if constexpr( sizeof...(Pack_T) > 0 )
		{
			if constexpr(contains_f<First_T, Second_T, Pack_T...>())
				return false;
			else
				return is_unique_f<Second_T, Pack_T...>();
		}
		else
		{
			if constexpr(std::is_same_v<First_T, Second_T>)
				return false;
			else
				return true;
		}
	}
	template <typename T>
	consteval bool is_unique_f()
	{
		return true;
	}

	template <typename Sample_T, size_t _sub_index, size_t _counter, typename T, typename... Pack_T>
	consteval size_t index_of_f()
	{
		if constexpr (std::is_same_v<Sample_T, T>)
		{
			if constexpr (_sub_index == 0)
				return _counter;
			else if constexpr (sizeof...(Pack_T) > 0)
				return index_of_f<Sample_T, (_sub_index - 1), (_counter + 1), Pack_T...>();
		}
		else if constexpr (sizeof...(Pack_T) > 0)
			return index_of_f<Sample_T, _sub_index, (_counter + 1), Pack_T...>();
		else
			static_assert(std::is_void_v<bool>, "Index of type is not found.");
	}

#endif // compile-time functions impl.

#if 1 // run-time functions impl.
	template <typename Functor_T, typename T, typename... Pack_T>
	inline void forEachTypes(Functor_T f)
	{
		f.template operator()<T>();
		if constexpr(sizeof...(Pack_T) > 0)
			forEachTypes<Functor_T, Pack_T...>(f);
	}

	template <typename Functor_T, size_t _counter, typename T, typename... Pack_T>
	inline void indexedForEachTypes(Functor_T f)
	{
		f.template operator()<_counter, T>();
		if constexpr(sizeof...(Pack_T) > 0)
			indexedForEachTypes<Functor_T, (1 + _counter), Pack_T...>(f);
	}

	template <typename Functor_T, typename T, typename... Pack_T>
	inline bool anyOfTypes(Functor_T f)
	{
		if constexpr( sizeof...(Pack_T) > 0)
		{
			if (f.template operator()<T>())
				return true;
			else
				return anyOfTypes<Functor_T, Pack_T...>(f);
		}
		else
			return f.template operator()<T>();
	}

	template <typename Functor_T, typename T, typename... Pack_T>
	inline bool allOfTypes(Functor_T f)
	{
		if constexpr( sizeof...(Pack_T) > 0 )
		{
			if (f.template operator()<T>())
				return allOfTypes<Functor_T, Pack_T...>(f);
			else
				return false;
		}
		else
			return f.template operator()<T>();
	}

	template <typename Functor_T, typename T, typename... Pack_T>
	inline bool noneOfTypes(Functor_T f)
	{
		if constexpr( sizeof...(Pack_T) > 0 )
		{
			if (f.template operator()<T>())
				return false;
			else
				return noneOfTypes<Functor_T, Pack_T...>(f);
		}
		else
			return false == f.template operator()<T>();
	}
#endif // run-time functions impl.
#if 1 // special algorithms for LikePackHolders impl.
// is_unique_pack
	template <LikePackHolder PackHolder_T>
	struct is_unique_pack
	: public PackHolder_T::place_t<algorithms::is_unique> {};
	template <template <typename...> typename PackHolder_VT>
		requires LikePackHolder<PackHolder_VT<>>
	struct is_unique_pack< PackHolder_VT<> >
	: public std::true_type {};
// unite_packs
	template <LikePackHolder First_T, LikePackHolder Second_T, LikePackHolder... Pack_T>
	struct unite_packs<First_T, Second_T, Pack_T...>
	// recursion.
	:	public unite_packs<
			typename Second_T::place_t<First_T::template back_expand_t>,
			Pack_T...
		>
	{};

	template <LikePackHolder Last_T>
	struct unite_packs<Last_T>
	// recursion end.
	:	public std::type_identity<Last_T>	{};

	template <>
	struct unite_packs<>
	:	public std::type_identity<PackHolder<>>	{};

#endif // special algorithms for LikePackHolders impl.
}
