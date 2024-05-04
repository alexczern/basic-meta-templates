#include <type_traits>

#include <bmt/PackHolder.hpp>
#include <bmt/TypesPack.hpp>

namespace bmt::containers
{
	template <template <typename, typename> typename TypedMap_T, LikeLogger Logger_T>
	int test_TypedMap(Logger_T& log)
	{
		Subtester tester(log, "bmt::containers::test_TypedMap");
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
		typedMap.forEach(
			[&tester]<typename TypedKey_T>(int& value)
			{
				if constexpr (std::is_same_v<TypedKey_T, int>)
					tester.check_assert(value == 123);
				else if constexpr (std::is_same_v<TypedKey_T, float>)
					tester.check_assert(value == -456);
				else if constexpr (std::is_same_v<TypedKey_T, double>)
					tester.check_assert(value == 789);
				else if constexpr (std::is_same_v<TypedKey_T, char>)
					tester.check_assert(value == -101);
			}
		);
		const auto& c_typedMap = typedMap;
		c_typedMap.forEach(
			[&tester]<typename TypedKey_T>(const int& value)
			{
				if constexpr (std::is_same_v<TypedKey_T, int>)
					tester.check_assert(value == 123);
				else if constexpr (std::is_same_v<TypedKey_T, float>)
					tester.check_assert(value == -456);
				else if constexpr (std::is_same_v<TypedKey_T, double>)
					tester.check_assert(value == 789);
				else if constexpr (std::is_same_v<TypedKey_T, char>)
					tester.check_assert(value == -101);
			}
		);

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
