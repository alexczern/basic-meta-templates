#include <tuple>
#include <type_traits>

namespace bmt
{
	template <template <typename...> typename TypesPack_VT, LikeLogger Logger_T>
	int test_TypesPack(Logger_T& log)
	{
		Subtester tester(log, "bmt::test_TypesPack");
		tester.check_assert(test_PackHolder<TypesPack_VT>(log) == 0);
		tester.check_assert(test_PackAlgorithms<TypesPack_VT>(log) == 0);

		if (tester.fail())
			return -1;

	// compile-time tests
		using Example = TypesPack_VT<
			int, double, int, double,
			float, unsigned int, unsigned int,
			float, int, float, int
		>;
	#if 1 // test ::template includes_pack
		using IncludesTest0 = TypesPack_VT<int, unsigned int, float, double>;
		static_assert(Example::template includes_pack_v<IncludesTest0> == true);
		static_assert(std::type_identity_t<
			typename Example::includes_pack<IncludesTest0>
		>::value == Example::template includes_pack_v<IncludesTest0>);

		using IncludesTest1 = TypesPack_VT<int, unsigned int, float, double, short>;
		static_assert(Example::template includes_pack_v<IncludesTest1> == false);
		static_assert(std::type_identity_t<
			typename Example::includes_pack<IncludesTest1>
		>::value == Example::template includes_pack_v<IncludesTest1>);

		using IncludesTest2 = TypesPack_VT<short, char, bool>;
		static_assert(Example::template includes_pack_v<IncludesTest2> == false);
		static_assert(std::type_identity_t<
			typename Example::includes_pack<IncludesTest2>
		>::value == Example::template includes_pack_v<IncludesTest2>);

	#endif
	#if 1 // test ::template partly_includes_pack
		using PartlyIncludesSample = TypesPack_VT<int, unsigned int, float, double>;
		static_assert(Example::template partly_includes_pack_v<PartlyIncludesSample> == true);
		static_assert(std::type_identity_t<
			typename Example::partly_includes_pack<PartlyIncludesSample>
		>::value == Example::template partly_includes_pack_v<PartlyIncludesSample>);

		using PartlyIncludesSample2 = TypesPack_VT<short, char, bool>;
		static_assert(Example::template partly_includes_pack_v<PartlyIncludesSample2> == false);
		static_assert(std::type_identity_t<
			typename Example::partly_includes_pack<PartlyIncludesSample2>
		>::value == Example::template partly_includes_pack_v<PartlyIncludesSample2>);
	#endif
	#if 1 // ::front_expand_pack and ::back_expand_t
		using ExpandedExample = TypesPack_VT<int, float, double, char, bool>;
		using ExpandedSample = TypesPack_VT<char, int, float>;
	// (::front_expand_t)
		using FrontExpandedExample = typename ExpandedExample::front_expand_pack<ExpandedSample>::type;
		static_assert(std::is_same_v<
			FrontExpandedExample, typename ExpandedExample::front_expand_pack_t<ExpandedSample>
		>);
		using PlacedTupleFrontExpanded = typename FrontExpandedExample::place_t<std::tuple>;
		using SampleTupleFrontExpanded = std::tuple<char, int, float, int, float, double, char, bool>;
		static_assert(true == std::is_same_v<PlacedTupleFrontExpanded, SampleTupleFrontExpanded>);
	// (::back_expand_t)
		using BackExpandedExample = typename ExpandedExample::back_expand_pack<ExpandedSample>::type;
		static_assert(std::is_same_v<
			BackExpandedExample, typename ExpandedExample::back_expand_pack_t<ExpandedSample>
		>);
		using PlacedTupleBackExpanded = typename BackExpandedExample::place_t<std::tuple>;
		using SampleTupleBackExpanded = std::tuple<int, float, double, char, bool, char, int, float>;
		static_assert(true == std::is_same_v<PlacedTupleBackExpanded, SampleTupleBackExpanded>);
	#endif
		return 0;
	}
}
