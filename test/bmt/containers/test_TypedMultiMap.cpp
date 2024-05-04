#include <type_traits>

#include <bmt/PackHolder.hpp>
#include <bmt/TypesPack.hpp>

namespace bmt::containers
{
	template <template <typename, typename> typename TypedMultiMap_T, LikeLogger Logger_T>
	int test_TypedMultiMap(Logger_T& log)
	{
		Subtester tester(log, "bmt::containers::test_TypedMultiMap");
		using TypedMultiMapExample = TypedMultiMap_T<
			PackHolder<int, float, double, int, float, char>,
			int
		>;
		TypedMultiMapExample typedMultiMap;
		typedMultiMap.template at<int, 0>() = 123;
		typedMultiMap.template at<float, 0>() = -456;
		typedMultiMap.template at<double>() = 789;
		typedMultiMap.template at<char>() = -101;
		typedMultiMap.template at<int, 1>() = 112;
		typedMultiMap.template at<float, 1>() = -131;
		tester.check_assert(typedMultiMap.template at<int>() == 123);
		tester.check_assert(typedMultiMap.template at<float>() == -456);
		tester.check_assert(typedMultiMap.template at<double>() == 789);
		tester.check_assert(typedMultiMap.template at<char>() == -101);
		tester.check_assert(typedMultiMap.template at<int, 1>() == 112);
		tester.check_assert(typedMultiMap.template at<float, 1>() == -131);

		struct
		: public TypedMultiMap_T< PackHolder<>, int >
		{} emptyTypedMultiMap;
		static_assert(std::is_empty_v<decltype(emptyTypedMultiMap)>);
		static_assert(emptyTypedMultiMap.size_v == 0);
		static_assert(decltype(emptyTypedMultiMap)::size::value == 0);

		struct
		: public TypedMultiMap_T< TypesPack<>, int >
		{} emptyTypedMultiMap2;
		static_assert(std::is_empty_v<decltype(emptyTypedMultiMap2)>);
		static_assert(emptyTypedMultiMap2.size_v == 0);
		static_assert(decltype(emptyTypedMultiMap2)::size::value == 0);

		if(tester.has_error)
			return -1;
		else
			return 0;
	}
}
