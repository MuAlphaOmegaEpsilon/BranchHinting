/** @brief C++ Macro definitions for easy Static Branch Prediction. 
 * 
 * *BranchHinting* is a minimalistic macro library used to perform [Static Branch Prediction](https://en.wikipedia.org/wiki/Branch_predictor#Static_branch_prediction), a technique used to hint the compiler about the likeliness of one or more branching conditions, so that the code can be streamlined into being more I-cache friendly. <br>
 * The desired behaviour is obtained through the use of the [__builtin_expect](https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005fexpect) keyword which is a GCC Built-in function.
 *
 * *Be aware that using this technique might give better or worse performance based on the quality of the hinting, so use this tool wisely.*
 *
 * 
 * Keep track of the latest updates of the BranchHinting project on 
 * <a href="https://github.com/MuAlphaOmegaEpsilon/BranchHinting">GitHub</a>.
 * 
 * @file BranchHinting.hpp
 * 
 * @author <a href="https://github.com/MuAlphaOmegaEpsilon/">Tommaso Bonvicini</a> - tommasobonvicini@gmail.com
 * 
 * @date 16-10-2018
 * 
 * **License** <br>
 * &emsp;&emsp;&emsp;[GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007](https://www.gnu.org/licenses/gpl-3.0.html)
 * 
 * @version 1.0.0
 */

#if !defined (_MSC_VER) && !defined (DISABLE_BRANCH_HINTING)

/** @brief Tags a condition as likely to verify.
 * 
 * example:<br>
 * The *foo ()* function should be called only when my_list has exactly 10 elements inside and when other conditions are met. <br>
 * The list might be empty as well as contain elements, however if it does actually contain elements 
 * it is likely to have exactly 10.
 * ```cpp
 * if (otherConditions == true && LIKELY (my_list.size () == 10))
 *     foo (); 
 * ``` */
#define LIKELY(x)			__builtin_expect ((x), 1)

/** @brief Tags a condition as unlikely to verify.
 * 
 * example:<br>
 * The *foo ()* function should be called only when my_list has exactly 10 elements inside and when other conditions are met. <br>
 * The list might be empty as well as contain elements, however if it does actually contain elements 
 * it is unlikely to have exactly 10.
 * ```cpp
 * if (otherConditions == true && UNLIKELY (my_list.size () == 10))
 *     foo (); 
 * ``` */
#define UNLIKELY(x) 		__builtin_expect ((x), 0)

/** @brief Tags an entire if-statement's condition as likely to verify.
 * 
 * example:<br>
 * The *foo ()* function should be called only when my_list has exactly 10 elements inside. <br>
 * The list might be empty as well asStatic Branch Prediction contain elements, however if it does actually contain elements 
 * it is likely to have exactly 10.
 * ```cpp
 * likely_if (my_list.size () == 10)
 *     foo (); 
 * ``` */
#define likely_if(x) 		if (__builtin_expect ((x), 1))	
	
/** @brief Tags an entire if-statement's condition as unlikely to verify.
 * 
 * example:<br>
 * The *foo ()* function should be called only when my_list has exactly 10 elements inside. <br>
 * The list might be empty as well as contain elements, however if it does actually contain elements 
 * it is unlikely to have exactly 10.
 * ```cpp
 * unlikely_if (my_list.size () == 10)
 *     foo (); 
 * ``` */
#define unlikely_if(x) 		if (__builtin_expect ((x), 0))	

#else

// No hinting at all
#define LIKELY(x)			x
#define UNLIKELY(x) 		x
#define likely_if(x) 		if (x)
#define unlikely_if(x) 		if (x)

#endif 
