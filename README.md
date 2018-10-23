# [<img src="./images/BranchHinting.png" height="100" alt="BranchHinting">]()
C++ Macro definitions for easy Static Branch Prediction.

*BranchHinting* is a minimalistic macro library used to perform [Static Branch Prediction](https://en.wikipedia.org/wiki/Branch_predictor#Static_branch_prediction), a technique used to hint the compiler about the likeliness of one or more branching conditions, so that the code can be streamlined into being more I-cache friendly. <br>
The desired behaviour is obtained through the use of the [__builtin_expect](https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005fexpect) keyword which is a GCC Built-in function.

*Be aware that using this technique might give better or worse performance based on the quality of the hinting, so use this tool wisely.*

## Table of contents
- [Download](#Download)
- [Dependencies](#Dependencies)
- [Source code integration](#Source-code-integration)
- [Disabling macros](#Disabling-macros)
- [Testing](#Testing)
- [CMake support](#CMake-support)
- [Doxygen support](#Doxygen-support)
- [Compilers supported](#Compilers-supported)
- [PGO vs SBP](#PGO-vs-SBP)
- [Generated x86 assembly](#Generated-x86-assembly)
- [Future upgrades](#Future-upgrades)
- [Font credits](#Font-credits)

## Download
The command below will download the content of this repository:
```bash
$ git clone https://github.com/MuAlphaOmegaEpsilon/BranchHinting
```

## Dependencies
This project consists of a header-only file with no include dependencies.

## Source code integration
Give a look at how to change the source code changes when you want to integrate the macros of this library:
```diff
+ #include <BranchHinting.hpp> // C++ Macro definitions for easy Static Branch Prediction.

bool mostlyTrue (); // A bool function that most of the time returns "true"
bool mostlyFalse (); // A bool function that most of the time returns "false"

void foo_one ();
void foo_two ();
void foo_three ();
void foo_four ();

int main ()
{
    bool almostAlwaysTrue = mostlyTrue ();
    bool almostAlwaysFalse = mostlyFalse ();
    bool otherCondition = ... ;

-   if (almostAlwaysTrue || otherCondition == false)
+   if (LIKELY (almostAlwaysTrue) || otherCondition == false)
        foo_one ();
    else
        foo_two ();

-   if (almostAlwaysFalse)
+   unlikely_if (almostAlwaysFalse)
        foo_three ();
-   else if (almostAlwaysTrue)
+   else likely_if (almostAlwaysTrue)
        foo_four ();

    return 0;
}
```

## Disabling macros
The hints to the compiler can be disabled just by defining a single macro.
```cpp
#define DISABLE_BRANCH_HINTING
```

## Testing
Just run the script contained in the repository. After testing has ended the script will automatically clean all the files created.
```bash
./runTests.sh
```

## CMake support
You only need to add the two commands below to your *CMakeLists.txt* file in order to use this macro library:
```cmake
ADD_SUBDIRECTORY (${PROJECT_SOURCE_DIR}/path_to_BranchHinting/)	
TARGET_LINK_LIBRARIES (your_executable PUBLIC BranchHinting)	
```

## Doxygen support
Doxygen is supported out of the box: just run it and check inside the *docs* folder:
```bash
doxygen
```

## Compilers supported
GCC, Clang and ICC correctly support the macros used to hint about likely taken branches; MSVC on the other hand doesn't support at all such features, and encourages the use of PGO instead.

*In case you are using this library as part of a cross-platform project that will also run on Windows through MSVC:* <br>
*BranchHinting* is automatically disabled when using the MSVC compiler, and you simply won't get the bonuses/maluses that comes from using it; apart from this everything will work fine.

## PGO vs SBP
**Profile Guided Optimization** is a great tool, there's no doubt about it, but it has its pros and cons as well as **Static Branch Prediction**.

*Remember*: *BranchHinting* falls under SBP

> If the test workload does not match the way the program is actually used, the performed optimizations might actually do more harm than good. For this reason, is it often hard to use **PGO** for libraries. Libraries can be used in many–sometimes widely different–scenarios. Unless the use cases are indeed similar, it is usually better to rely exclusively on **Static Branch Prediction** using __builtin_expect. 
> 
> <[What Every Programmer Should Know About Memory, page 85 - Akkadia](https://www.akkadia.org/drepper/cpumemory.pdf)>

## Generated x86 assembly
![](https://user-images.githubusercontent.com/26225010/47092694-d8f08900-d227-11e8-89c5-9c7546607182.png) 
Look at how [these two snippets of code](https://godbolt.org/z/9nVBgW) differ in the generated assembly using GCC 8.2 with the -O3 flag on the GodBolt.org compiler explorer website. <br>
You can notice how the compiler optimizes the path for the likely-tagged branches on the right side:
* **Lines 5-6**: the result of *mostlyTrue ()* is saved in the %EBP register.
* **Lines 7-8**: the result of *mostlyFalse ()* is saved in the %EBX register.
* **Lines 9-10**: the CPU jumps to execute *foo_two ()* only when *mostlyTrue ()* returned false, which is known to be unlikely.
* **Line 11**: the CPU calls *foo_one ()*.
* **Lines 12-13**: the CPU jumps to execute *foo_three ()* only when *mostlyFalse ()* returned true, which is known to be unlikely.
* **Line 14**: the CPU calls *foo_four ()* regardless, since it is already on the path that checked that *mostlyTrue ()* actually returned true. 

## Future upgrades
C++20 is probably going to integrate natively the **[[likely]]** and **[[unlikely]]** attributes for static branch prediction. <br>
I will take into account the possibility of upgrading *BranchHinting* once the new standard will be officially supported by most compilers.

[Here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0479r5.html) you can find the latest revision of 
the attribute proposal, while [here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0479r0.html) you can find the original 2016 proposal which also presents some insights based on statistical data regarding the effectiveness of static branch prediction. 

## Font credits
The font used for the logo is free for non-lucrative purposes: [Pretty Trees](https://www.dafont.com/it/cf-pretty-trees.font), created by [CloutierFontes](http://www.cloutierfontes.ca/).
