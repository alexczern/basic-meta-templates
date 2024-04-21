#include <bmt/containers/TypedHeteroMap.hpp>

namespace bmt::containers
{
	template <LikePackHolder PackHolder_T, template<typename> typename Transformer_TT>
		template <typename Key_T>
		Transformer_TT<Key_T>::type& TypedHeteroMap<
			PackHolder_T, Transformer_TT
		>::at()
		{
			return itemsTuple.template get< Base::template index_of_v<Key_T> >();
		}
}
