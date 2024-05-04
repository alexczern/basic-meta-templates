#include <type_traits>

namespace bmt::containers
{
	namespace test_UnitedTypes_impl
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
	template <template <typename...> typename UnitedTypes_VT, LikeLogger Logger_T>
	int test_UnitedTypes(Logger_T& log)
	{
		Subtester tester(log, "bmt::containers::test_UnitedTypes");

		using namespace test_UnitedTypes_impl;
		UnitedTypes_VT<Alpha, Gamma, Beta> uObject({.a_num = 100}, {}, {.b_num = 35});
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
