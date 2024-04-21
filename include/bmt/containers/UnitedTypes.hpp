#pragma once
#include <type_traits>

namespace bmt::containers
{
	template <typename... Pack_T>
	struct UnitedTypes;
	template<> struct UnitedTypes<> {};

	template <typename ItemType_T, typename... Pack_T>
		requires std::is_class_v<ItemType_T>
	struct UnitedTypes<ItemType_T, Pack_T...>
	:	public ItemType_T,
		public UnitedTypes<Pack_T...>
	{
	public:
		UnitedTypes() = default;
		UnitedTypes(const UnitedTypes&) = default;
		UnitedTypes(UnitedTypes&&) = default;

		UnitedTypes(const ItemType_T &item, const Pack_T&... args)
		:	ItemType_T(item),
			UnitedTypes<Pack_T...>(args...) {}
	};
	template <typename ItemType_T>
		requires std::is_class_v<ItemType_T>
	struct UnitedTypes<ItemType_T>
	:	public ItemType_T
	{
	public:
		UnitedTypes() = default;
		UnitedTypes(const UnitedTypes&) = default;
		UnitedTypes(UnitedTypes&&) = default;

		UnitedTypes(const ItemType_T &item)
		:	ItemType_T(item) {}
	};
}
