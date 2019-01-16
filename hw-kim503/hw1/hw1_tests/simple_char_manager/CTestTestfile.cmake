# CMake generated Testfile for 
# Source directory: /home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager
# Build directory: /home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(FirstMemtest.Execution "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=FirstMemtest.Execution")
add_test(SimpleCharManager.ConstructionDestruction "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.ConstructionDestruction")
add_test(SimpleCharManager.OneCharAlloc "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.OneCharAlloc")
add_test(SimpleCharManager.OneCharFree "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.OneCharFree")
add_test(SimpleCharManager.FiveCharAlloc "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.FiveCharAlloc")
add_test(SimpleCharManager.FiveCharAllocFree "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.FiveCharAllocFree")
add_test(SimpleCharManager.AllocFree_x2 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.AllocFree_x2")
add_test(SimpleCharManager.FreeAll "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.FreeAll")
add_test(SimpleCharManager.Alloc10000Chars "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.Alloc10000Chars")
add_test(SimpleCharManager.Alloc1Charx10000 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/simple_char_manager/simple_char_manager_test" "--gtest_filter=SimpleCharManager.Alloc1Charx10000")
