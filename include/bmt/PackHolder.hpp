#pragma once

namespace bmt
{
	namespace impl_concepts
	{
		template < template< template<typename...> typename > typename >
		using check_pack_placer = void;
		template < template< typename... > typename >
		using check_variadic_templ = void;
	}
	template<typename... Pack_T>
	struct PackHolder
	{
		template <template <typename...> typename VariadicTempl_T>
		using place_t = VariadicTempl_T<Pack_T...>;
		template <typename... AnotherPack_T>
		using front_expand_t = PackHolder<AnotherPack_T..., Pack_T...>;
		template <typename... AnotherPack_T>
		using back_expand_t = PackHolder<Pack_T..., AnotherPack_T...>;
	};
	template <typename T>
	concept LikePackHolder =
		requires{
			typename impl_concepts::check_pack_placer<T::template place_t>;
			typename impl_concepts::check_variadic_templ<T::template front_expand_t>;
			typename impl_concepts::check_variadic_templ<T::template back_expand_t>;
		};
	static_assert(LikePackHolder<PackHolder<>>);
}
