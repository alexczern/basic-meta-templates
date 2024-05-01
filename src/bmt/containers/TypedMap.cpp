#include <bmt/containers/TypedMap.hpp>

namespace bmt::containers
{
#if 1 // TypedMap impl.
	template <LikePackHolder PackHolder_T, typename DataType_T>
		requires algorithms::is_unique_pack_v<PackHolder_T>
		template <typename TypedKey_T>
		DataType_T& TypedMap<
			PackHolder_T, DataType_T
		>::at()
		{
			return arr[Base::template index_of_v<TypedKey_T>];
		}

	template <LikePackHolder PackHolder_T, typename DataType_T>
		requires algorithms::is_unique_pack_v<PackHolder_T>
		template <typename TypedKey_T>
		const DataType_T& TypedMap<
			PackHolder_T, DataType_T
		>::at() const
		{
			return arr[Base::template index_of_v<TypedKey_T>];
		}
#endif // TypedMap impl.
#if 1 // TypedMultiMap impl.
	template <LikePackHolder PackHolder_T, typename DataType_T>
		template <typename TypedKey_T, size_t _key_index>
		DataType_T& TypedMultiMap<
			PackHolder_T, DataType_T
		>::at()
		{
			return arr[Base::template index_of_v<TypedKey_T, _key_index>];
		}

	template <LikePackHolder PackHolder_T, typename DataType_T>
		template <typename TypedKey_T, size_t _key_index>
		const DataType_T& TypedMultiMap<
			PackHolder_T, DataType_T
		>::at() const
		{
			return arr[Base::template index_of_v<TypedKey_T, _key_index>];
		}
#endif // TypedMultiMap impl.
}
