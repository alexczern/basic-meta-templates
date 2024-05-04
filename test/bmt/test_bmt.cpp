#include <concepts>
#include <source_location>

#include <bmt/bmt.hpp>

namespace bmt
{
	template <typename Logger_T, typename T>
	concept LikeTagOfLogger =
		requires(Logger_T l)
		{
			T(l, "str");
		};
	template <typename T>
	concept LikeLogger =
		requires(T log, int i, const char *str){
			typename T::TagType;
			requires LikeTagOfLogger<T, typename T::TagType>;
			{ log.tag("str") } -> std::same_as<typename T::TagType>;
			log.template info(str, i, str);
			log.template warning(str, i, str);
			log.template debug(str, i, str);
			log.template trace(str, i, str);
			log.template error(str, i, str);
			log.template fatal(str, i, str);
		};

	template <LikeLogger Logger_T>
	struct Subtester
	:	public Logger_T::TagType
	{
		Logger_T &r_log;
		bool has_error = false;
		Subtester(Logger_T &l, const char *name)
		:	Logger_T::TagType(l, name),
			r_log(l)
		{}
		void check_assert(
			bool a, const std::source_location location = std::source_location::current()
		)
		{
			if (false == a)
			{
				r_log.error("[BAD][CHECK_ASSERT][",
					location.file_name(), '(',
					location.line(), ':', location.column(), ")]");
				has_error = true;
			}
		}
		bool fail() { return has_error; };
	};

	template <typename T>
	struct custom_transformer
	{
		using type = T;
	};
	template <>
	struct custom_transformer<int>
	{
		using type = float;
	};
	template <>
	struct custom_transformer<double>
	{
		using type = int;
	};
}

#include "test_PackHolder.cpp"
#include "test_PackAlgorithms.cpp"
#include "test_TypesPack.cpp"
#include "containers/test_containers.cpp"

namespace bmt
{
	template <LikeLogger Logger_T>
	int test_bmt(Logger_T& log)
	{
		Subtester<Logger_T> tester(log, "bmt::test_bmt");

		tester.check_assert(0 == test_PackHolder<PackHolder>(log));
		tester.check_assert(0 == test_PackAlgorithms<PackAlgorithms>(log));
		tester.check_assert(0 == test_TypesPack<TypesPack>(log));
		tester.check_assert(0 == containers::test_containers(log));

		if (tester.fail())
			return -1;
		else
			return 0;
	}
}
