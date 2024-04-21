#include <type_traits>

namespace bmt
{
	namespace test_impl
	{
		struct Alpha
		{
			int a_num = 10;
		};
		struct Gamma
		{
			int g_num = 20;
		};
		struct Beta
		{
			int b_num = 30;
		};
	}
	template <LikeLogger Logger_T>
	template <template <typename...> typename UnitedTypes_T>
	int LibTester<Logger_T>::test_UnitedTypes()
	{
		Subtester tester(log, "bmt::LibTester::test_UnitedTypes");
		using namespace test_impl;
		UnitedTypes_T<Alpha, Gamma, Beta> uObject({.a_num = 100}, {}, {.b_num = 35});
		static_assert(std::is_base_of_v<Alpha, decltype(uObject)>);
		static_assert(std::is_base_of_v<Gamma, decltype(uObject)>);
		static_assert(std::is_base_of_v<Beta, decltype(uObject)>);

		tester.check_assert(uObject.a_num == 100);
		tester.check_assert(uObject.g_num == 20);
		tester.check_assert(uObject.b_num == 35);

		if(tester.has_error)
			return -1;
		else
			return 0;
	}
}
