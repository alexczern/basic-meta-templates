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

	template <LikePackHolder PackHolder_T, typename DataType_T>
		requires algorithms::is_unique_pack_v<PackHolder_T>
	void TypedMap<PackHolder_T, DataType_T>::forEach(auto lam)
	{
		Base::indexedForEach(
			[this, &lam]<size_t index, typename TypedKey_T>() {
				lam.template operator()<TypedKey_T>(arr[index]);
			}
		);
	}

	template <LikePackHolder PackHolder_T, typename DataType_T>
		requires algorithms::is_unique_pack_v<PackHolder_T>
	void TypedMap<PackHolder_T, DataType_T>::forEach(auto lam) const
	{
		Base::indexedForEach(
			[this, &lam]<size_t index, typename TypedKey_T>() {
				lam.template operator()<TypedKey_T>(arr[index]);
			}
		);
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
