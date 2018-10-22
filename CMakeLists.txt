###############################################################################
#                                CMAKE VERSION                                #
###############################################################################
CMAKE_MINIMUM_REQUIRED (VERSION 3.9.5)




###############################################################################
#                                   PROJECT                                   #
###############################################################################
PROJECT (BranchHinting VERSION 1.0.0 LANGUAGES CXX 
		DESCRIPTION "C++ Macro definitions for easy Static Branch Prediction."
		HOMEPAGE_URL "https://github.com/MuAlphaOmegaEpsilon/BranchHinting")




###############################################################################
#                                  LIBRARY                                    #
###############################################################################
ADD_LIBRARY (BranchHinting INTERFACE)




###############################################################################
#                                  HEADERS                                    #
###############################################################################
TARGET_INCLUDE_DIRECTORIES	(BranchHinting INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})




###############################################################################
#                                  OPTIONS                                    #
###############################################################################
OPTION (TEST "Is library testing enabled?" OFF)




###############################################################################
#                                    TESTS                                    #
###############################################################################
IF (TEST)
	ENABLE_TESTING ()
	ADD_EXECUTABLE (HintingEnabled "tests/HintingEnabled.cpp")
	ADD_EXECUTABLE (HintingDisabled "tests/HintingDisabled.cpp")
	TARGET_LINK_LIBRARIES (HintingEnabled BranchHinting)
	TARGET_LINK_LIBRARIES (HintingDisabled BranchHinting)
	ADD_TEST (BranchHinting[Enabled] HintingEnabled)	
	ADD_TEST (BranchHinting[Disabled] HintingDisabled)		
ENDIF ()
