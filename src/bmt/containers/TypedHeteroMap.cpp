#include <bmt/containers/TypedHeteroMap.hpp>

namespace bmt::containers
{
	template <LikePackHolder PackHolder_T, template<typename> typename Transformer_TT>
		requires algorithms::is_unique_pack_v<PackHolder_T>
		template <typename Key_T>
		Transformer_TT<Key_T>::type& TypedHeteroMap<
			PackHolder_T, Transformer_TT
		>::at()
		{
			return itemsTuple.template get< Base::template index_of_v<Key_T> >();
		}
	template <LikePackHolder PackHolder_T, template<typename> typename Transformer_TT>
		requires algorithms::is_unique_pack_v<PackHolder_T>
		template <typename Key_T>
		const Transformer_TT<Key_T>::type& TypedHeteroMap<
			PackHolder_T, Transformer_TT
		>::at() const
		{
			return itemsTuple.template get< Base::template index_of_v<Key_T> >();
		}
}
