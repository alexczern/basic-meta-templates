#include <type_traits>

#include <bmt/PackHolder.hpp>
#include <bmt/TypesPack.hpp>

namespace bmt::containers
{
	template <template <typename, template<typename>typename> typename TypedHeteroMap_T, LikeLogger Logger_T>
	int test_TypedHeteroMap(Logger_T& log)
	{
		Subtester tester(log, "bmt::containers::test_TypedHeteroMap");
		TypedHeteroMap_T<PackHolder<int, float, double>, custom_transformer> typedHeteroMap;

		static_assert(std::is_same_v<float&, decltype(typedHeteroMap.template at<int>())>);
		typedHeteroMap.template at<int>() = 12.3f;
		tester.check_assert((typedHeteroMap.template at<int>() == 12.3f));

		static_assert(std::is_same_v<float&, decltype(typedHeteroMap.template at<float>())>);
		typedHeteroMap.template at<float>() = 45.6f;
		tester.check_assert((typedHeteroMap.template at<float>() == 45.6f));

		static_assert(std::is_same_v<int&, decltype(typedHeteroMap.template at<double>())>);
		typedHeteroMap.template at<double>() = 789;
		tester.check_assert((typedHeteroMap.template at<double>() == 789));

		struct
		: public TypedHeteroMap_T< PackHolder<>, custom_transformer >
		{} emptyTypedHeteroMap;
		static_assert(std::is_empty_v<decltype(emptyTypedHeteroMap)>);
		static_assert(emptyTypedHeteroMap.size_v == 0);
		static_assert(decltype(emptyTypedHeteroMap)::size::value == 0);

		struct
		: public TypedHeteroMap_T< TypesPack<>, custom_transformer >
		{} emptyTypedHeteroMap2;
		static_assert(std::is_empty_v<decltype(emptyTypedHeteroMap2)>);
		static_assert(emptyTypedHeteroMap2.size_v == 0);
		static_assert(decltype(emptyTypedHeteroMap2)::size::value == 0);


		if(tester.has_error)
			return -1;
		else
			return 0;
	}
}
