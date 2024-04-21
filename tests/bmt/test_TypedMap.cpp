#include <tuple>
#include <type_traits>

#include <bmt/PackHolder.hpp>

namespace bmt
{
	template <LikeLogger Logger_T>
	template <template <typename, typename> typename TypedMap_T>
	int LibTester<Logger_T>::test_TypedMap()
	{
		Subtester tester(log, "bmt::LibTester::test_TypedMap");
		using TypedMapExample = TypedMap_T<
			PackHolder<int, float, double, char>,
			int
		>;
		TypedMapExample typedMap;
		typedMap.template at<int>() = 123;
		typedMap.template at<float>() = -456;
		typedMap.template at<double>() = 789;
		typedMap.template at<char>() = -101;
		tester.check_assert(typedMap.template at<int>() == 123);
		tester.check_assert(typedMap.template at<float>() == -456);
		tester.check_assert(typedMap.template at<double>() == 789);
		tester.check_assert(typedMap.template at<char>() == -101);

		struct
		: public TypedMap_T< PackHolder<>, int >
		{} emptyTypedMap;
		static_assert(std::is_empty_v<decltype(emptyTypedMap)>);
		static_assert(emptyTypedMap.size_v == 0);
		static_assert(decltype(emptyTypedMap)::size::value == 0);

		struct
		: public TypedMap_T< TypesPack<>, int >
		{} emptyTypedMap2;
		static_assert(std::is_empty_v<decltype(emptyTypedMap2)>);
		static_assert(emptyTypedMap2.size_v == 0);
		static_assert(decltype(emptyTypedMap2)::size::value == 0);

		if(tester.has_error)
			return -1;
		else
			return 0;
	}
}
