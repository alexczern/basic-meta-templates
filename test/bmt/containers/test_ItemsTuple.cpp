#include <type_traits>

namespace bmt::containers
{
	template <template <typename...> typename ItemsTuple_VT, LikeLogger Logger_T>
	int test_ItemsTuple(Logger_T& log)
	{
		Subtester tester(log, "bmt::containers::test_ItemsTuple");
		using ItemsTupleExample = ItemsTuple_VT<int, int, double, float, long, short, unsigned int>;
		ItemsTupleExample itemsTuple(123, 0, 789.d, -101112.f, 1234568789, 0, 131415);
		static_assert(
			sizeof(itemsTuple) ==
			sizeof(std::tuple<int, int, double, float, long, short, unsigned int>)
				// Dont forget about "padding"!
				//~ (
					//~ sizeof(int) * 2
					//~ + sizeof(double)
					//~ + sizeof(float)
					//~ + sizeof(char)
					//~ + sizeof(bool)
					//~ + sizeof(unsigned int)
				//~ )
		);

	#if 1 // compile-time tests
		static_assert(itemsTuple.size_v == 7);
		static_assert( // contains_v test
			itemsTuple.template contains_v<int>
			&& itemsTuple.template contains_v<double>
			&& itemsTuple.template contains_v<float>
			&& itemsTuple.template contains_v<long>
			&& itemsTuple.template contains_v<short>
			&& itemsTuple.template contains_v<unsigned int>
			&& (false == itemsTuple.template contains_v<const char*>)
		);
		static_assert( // count_v test
			itemsTuple.template count_v<int> == 2
			&& itemsTuple.template count_v<double> == 1
			&& itemsTuple.template count_v<float> == 1
			&& itemsTuple.template count_v<long> == 1
			&& itemsTuple.template count_v<short> == 1
			&& itemsTuple.template count_v<unsigned int> == 1
			&& (0 == itemsTuple.template contains_v<const char*>)
		);
	#endif // compile-time tests
	#if 1 // run-time tests
	// element access
		itemsTuple.template get<int, 1>() = -456;
		itemsTuple.template get<short>() = 12345;
		tester.check_assert( itemsTuple.template get<int>() == 123);
		tester.check_assert( itemsTuple.template get<int, 1>() == -456);
		tester.check_assert( itemsTuple.template get<double>() == 789.d);
		tester.check_assert( itemsTuple.template get<float>() == -101112.f);
		tester.check_assert( itemsTuple.template get<long>() == 1234568789);
		tester.check_assert( itemsTuple.template get<short>() == 12345);
		tester.check_assert( itemsTuple.template get<unsigned int>() == 131415);
		tester.check_assert( itemsTuple.template get<0>() == 123);
		tester.check_assert( itemsTuple.template get<1>() == -456);
		tester.check_assert( itemsTuple.template get<2>() == 789.d);
		tester.check_assert( itemsTuple.template get<3>() == -101112.f);
		tester.check_assert( itemsTuple.template get<4>() == 1234568789);
		tester.check_assert( itemsTuple.template get<5>() == 12345);
		tester.check_assert( itemsTuple.template get<6>() == 131415);

		static_assert(std::is_same_v<
			decltype(itemsTuple.template get<0>()), int&
		>);
		static_assert(std::is_same_v<
			decltype(itemsTuple.template get<1>()), int&
		>);
		static_assert(std::is_same_v<
			decltype(itemsTuple.template get<2>()), double&
		>);
		static_assert(std::is_same_v<
			decltype(itemsTuple.template get<3>()), float&
		>);
		static_assert(std::is_same_v<
			decltype(itemsTuple.template get<4>()), long&
		>);
		static_assert(std::is_same_v<
			decltype(itemsTuple.template get<5>()), short&
		>);
		static_assert(std::is_same_v<
			decltype(itemsTuple.template get<6>()), unsigned int&
		>);

	// algorithms
		int counter = 0;
		itemsTuple.forEach(
			[&counter](auto &el) { ++counter; }
		);
		tester.check_assert(counter == 7);
		counter = 0;
		itemsTuple.indexedForEach(
			[&tester, &counter]<size_t index>(auto &el) {
				tester.check_assert(index == counter);
				++counter;
			}
		);
		tester.check_assert(counter == 7);
		counter = 0;
		itemsTuple.adjacentForEach(
			[&tester, &counter](auto &first, auto& second) {
				++counter;
			}
		);
		tester.check_assert(counter == 6);
		counter = 0;

		auto Kono = [](auto &item) -> bool {
				if(item == 123)
					return true;
				else
					return false;
			};
		auto Dio = [](auto &item) -> bool {
					if(item == 1000000)
						return true;
					else
						return false;
				};
		auto Da = [](auto &item) -> bool {
				if(item != 1000000)
						return true;
					else
						return false;
				};

		tester.check_assert(itemsTuple.anyOf(Kono));
		tester.check_assert(false == itemsTuple.anyOf(Dio));
		tester.check_assert(itemsTuple.anyOf(Da));

		tester.check_assert(false == itemsTuple.allOf(Kono));
		tester.check_assert(false == itemsTuple.allOf(Dio));
		tester.check_assert(itemsTuple.allOf(Da));

		tester.check_assert(false == itemsTuple.noneOf(Kono));
		tester.check_assert(itemsTuple.noneOf(Dio));
		tester.check_assert(false == itemsTuple.noneOf(Da));
	#endif // run-time tests

		struct
		: public ItemsTuple_VT<>
		{} emptyItemsTuple;
		static_assert(std::is_empty_v<decltype(emptyItemsTuple)>);
		static_assert(emptyItemsTuple.size_v == 0);
		static_assert(decltype(emptyItemsTuple)::size::value == 0);

		if(tester.has_error)
			return -1;
		else
			return 0;
	}
}
