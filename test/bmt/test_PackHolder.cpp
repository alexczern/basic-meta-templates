#include <tuple>
#include <type_traits>

namespace bmt
{
	template <template <typename...> typename PackHolder_VT, LikeLogger Logger_T>
	int test_PackHolder(Logger_T& log)
	{
		Subtester tester(log, "bmt::test_PackHolder");
	// first test
		using Example = PackHolder_VT<int, float, double, char, bool>;

		static_assert(LikePackHolder<Example>);
		using PlacedTuple = typename Example::template place_t<std::tuple>;
		using SampleTuple = std::tuple<int, float, double, char, bool>;
		using WrongSampleTuple = std::tuple<int, float, double>;
		static_assert(true == std::is_same_v<PlacedTuple, SampleTuple >);
		static_assert(false == std::is_same_v<PlacedTuple, WrongSampleTuple >);
	// second test (::front_expand_t)
		using FrontExpandedExample = typename Example::template front_expand_t<char, int, float>;
		static_assert(LikePackHolder<FrontExpandedExample>);
		using PlacedTupleFrontExpanded = typename FrontExpandedExample::template place_t<std::tuple>;
		using SampleTupleFrontExpanded = std::tuple<char, int, float, int, float, double, char, bool>;
		static_assert(true == std::is_same_v<PlacedTupleFrontExpanded, SampleTupleFrontExpanded>);
	// second test (::back_expand_t)
		using BackExpandedExample = typename Example::template back_expand_t<char, int, float>;
		static_assert(LikePackHolder<BackExpandedExample>);
		using PlacedTupleBackExpanded = typename BackExpandedExample::template place_t<std::tuple>;
		using SampleTupleBackExpanded = std::tuple<int, float, double, char, bool, char, int, float>;
		static_assert(true == std::is_same_v<PlacedTupleBackExpanded, SampleTupleBackExpanded>);
	// thrid test
		static_assert(is_unique_pack_v< PackHolder_VT<int> >);
		static_assert(is_unique_pack_v< PackHolder_VT<int, float> >);
		static_assert(is_unique_pack_v< PackHolder_VT<int, float, double> >);
		static_assert(false == is_unique_pack_v< PackHolder_VT<int, float, double, double> >);
		static_assert(size_of_pack_v<Example> == 5);
		using UnitedPacks = typename unite_packs<Example, FrontExpandedExample, BackExpandedExample>::type;
		static_assert(size_of_pack<UnitedPacks>::value == 21);
		static_assert(std::is_same_v<UnitedPacks, unite_packs_t<Example, FrontExpandedExample, BackExpandedExample>>);
		static_assert(
			std::is_base_of_v<
				UnitedPacks,
				PackHolder_VT<
					int, float, double, char, bool,
					char, int, float, int, float, double, char, bool,
					int, float, double, char, bool, char, int, float
				>
			>,
			"Error! bmt::unite_packs make wrong \"unite\" operation!"
		);

		return 0;
	}
}
