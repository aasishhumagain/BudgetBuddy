# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "BudgetBuddy_2_autogen"
  "CMakeFiles\\BudgetBuddy_2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BudgetBuddy_2_autogen.dir\\ParseCache.txt"
  )
endif()
