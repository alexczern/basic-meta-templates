#include <bmt/containers/containers.hpp>

#include "test_TypedMap.cpp"
#include "test_TypedMultiMap.cpp"
#include "test_ItemsTuple.cpp"
#include "test_TypedHeteroMap.cpp"
#include "test_UnitedTypes.cpp"


namespace bmt::containers
{
	template <LikeLogger Logger_T>
	int test_containers(Logger_T& log)
	{
		Subtester tester(log, "bmt::containers::test_containers");

		tester.check_assert(0 == test_TypedMap<TypedMap>(log));
		tester.check_assert(0 == test_TypedMultiMap<TypedMultiMap>(log));
		tester.check_assert(0 == test_ItemsTuple<ItemsTuple>(log));
		tester.check_assert(0 == test_TypedHeteroMap<TypedHeteroMap>(log));
		tester.check_assert(0 == test_UnitedTypes<UnitedTypes>(log));

		if (tester.fail())
			return -1;
		else
			return 0;
	};
}
