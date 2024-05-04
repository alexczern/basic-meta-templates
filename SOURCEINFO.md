Basic-Meta-Templates
====================
### File organization:
* Used separation for implementation ("src/", ".cpp"), header ("include/", ".hpp") and tests ("test/", "test_\*.cpp").
* Library used own folder ("bmt") like "src/bmt", "include/bmt", "test/bmt".
* Main header file - "include/bmt/bmt.hpp" and implementation file - "src/bmt/bmt.cpp".
* Every "namespace" has own folder and nested file at "src" and "include" ("include/bmt", "include/bmt/bmt.hpp").
* Every "namespace" used "underscored" naming ("some_ns").
* If class has nested class then folder named as primary class used for nested classes ("SomeClass.hpp", "SomeClass/SomeNestedClass.hpp").

### Coding style:
* Different styles are used for code executed at "compile-time" and at "run-time":
	* Compile-time:
		* Using "underscored" naming ("some_class_v", "some_class_t", "some_class").
		* Mainly used like "integral_constant"/"type_identity" templates/types.
		* Using helpers ("\*\_v", "\*\_t") for "integral_constant"/"type_identity" templates/types (variable or variable template and type or type template).
	* Run-time:
		* Used "uppercased" naming (".someMethod()", "someData", "NestedOrNotClassOrStructure").
