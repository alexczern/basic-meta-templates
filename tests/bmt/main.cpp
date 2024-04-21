#include <iostream>
#include <bmt/bmt.hpp>
#include "../src/bmt/bmt.cpp"
#include "LibTester.cpp"

namespace bmt
{
	class Logger
	{
		std::ostream& out;
		std::string tab_line = "";
		template <typename ArgType, typename... Args_P>
		inline void print_data(ArgType arg, Args_P... args_p)
		{
			out << arg;
			if constexpr (sizeof...(Args_P) > 0)
				print_data<Args_P...>(args_p...);
			else
				out << std::endl;
		}
	public:
		friend class TagType;
		struct TagType
		{
			std::string &r_tabline;
			TagType(Logger &log, const char* name)
			:	r_tabline(log.tab_line) {
				log.out << log.tab_line << '(' << name << ')' << std::endl;
				log.tab_line += '\t';
			}
			~TagType() {
				r_tabline.resize(r_tabline.length() - 1);
			}
		};

		TagType tag(const char* name)
		{
			return TagType(*this, name);
		}

		Logger(std::ostream& o)
		: out(o) {}

		template <typename... Args_P>
		inline void info(Args_P... args_p)
		{
			out << tab_line << "[INFO]: "; print_data<Args_P...>(args_p...);
		}
		template <typename... Args_P>
		inline void warning(Args_P... args_p)
		{
			out << tab_line << "[WARNING]: "; print_data<Args_P...>(args_p...);
		}
		template <typename... Args_P>
		inline void debug(Args_P... args_p)
		{
			out << tab_line << "[DEBUG]: "; print_data<Args_P...>(args_p...);
		}
		template <typename... Args_P>
		inline void trace(Args_P... args_p)
		{
			out << tab_line << "[TRACE]: "; print_data<Args_P...>(args_p...);
		}
		template <typename... Args_P>
		inline void error(Args_P... args_p)
		{
			out << tab_line << "[ERROR]: "; print_data<Args_P...>(args_p...);
		}
		template <typename... Args_P>
		inline void fatal(Args_P... args_p)
		{
			out << tab_line << "[FATAL ERROR]: "; print_data<Args_P...>(args_p...);
		}
	};
}

int main()
{
	bmt::Logger logger(std::cout);
	bmt::LibTester<bmt::Logger> test(logger);
	int result = test.start();
	logger.info((result == 0) ? "[SUCCESS]" : "[CATASTROPHE]", "[RETURN CODE: ", result, ']');
	return 0;
}
