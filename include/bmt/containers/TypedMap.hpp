#pragma once
#include <cstddef>
#include <type_traits>
#include <array>

#include <bmt/PackHolder.hpp>
#include <bmt/PackAlgorithms.hpp>
#include <bmt/algorithms_internal.hpp>

namespace bmt::containers
{
// TypedMap
	template <LikePackHolder PackHolder_T, typename DataType_T>
		requires (true == algorithms::is_unique_pack_v<PackHolder_T>)
	class TypedMap
	:	private PackHolder_T::place_t<PackAlgorithms>
	{
		using Base = typename PackHolder_T::place_t<PackAlgorithms>;
		std::array<
			DataType_T,
			Base::size_v
		> arr;
	public:
		TypedMap() = default;
		TypedMap(const TypedMap&) = default;
		TypedMap(TypedMap&&) = default;

		using Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods.
		template <typename TypedKey_T>
		DataType_T& at();
	};

	template <template <typename...> typename PackHolder_VT, typename DataType_T>
		requires LikePackHolder<PackHolder_VT<>>
	class TypedMap<PackHolder_VT<>, DataType_T>
	:	private PackAlgorithms<>
	{
	private:
		using Base = PackAlgorithms<>;
	protected:
		TypedMap() = default;
		TypedMap(const TypedMap&) = default;
		TypedMap(TypedMap&&) = default;
	public:
		using Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods.
		template <typename>
		DataType_T& at() = delete;
	};
// TypedMultiMap
	template <LikePackHolder PackHolder_T, typename DataType_T>
	class TypedMultiMap
	:	private PackHolder_T::place_t<PackAlgorithms>
	{
		using Base = typename PackHolder_T::place_t<PackAlgorithms>;
		std::array<
			DataType_T,
			Base::size_v
		> arr;
	public:
		TypedMultiMap() = default;
		TypedMultiMap(const TypedMultiMap&) = default;
		TypedMultiMap(TypedMultiMap&&) = default;

		using Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods.
		template <typename TypedKey_T, size_t _index = 0>
		DataType_T& at();
	};

	template <template <typename...> typename PackHolder_VT, typename DataType_T>
		requires LikePackHolder<PackHolder_VT<>>
	class TypedMultiMap<PackHolder_VT<>, DataType_T>
	:	private PackAlgorithms<>
	{
	private:
		using Base = PackAlgorithms<>;
	protected:
		TypedMultiMap() = default;
		TypedMultiMap(const TypedMultiMap&) = default;
		TypedMultiMap(TypedMultiMap&&) = default;
	public:
		using Base::size;
		using Base::size_v;
		using Base::contains;
		using Base::contains_v;
		using Base::count;
		using Base::count_v;

	// run-time methods.
		template <typename, size_t = 0>
		DataType_T& at() = delete;
	};
}
