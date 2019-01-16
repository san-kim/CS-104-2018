# CMake generated Testfile for 
# Source directory: /home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests
# Build directory: /home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(HeapTest.ConstructionDestruction "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ConstructionDestruction")
add_test(HeapTest.InitiallyEmpty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.InitiallyEmpty")
add_test(HeapTest.EmptyPeekException "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.EmptyPeekException")
add_test(HeapTest.EmptyRemoveException "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.EmptyRemoveException")
add_test(HeapTest.SingleItemNonempty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.SingleItemNonempty")
add_test(HeapTest.SingleItemPush "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.SingleItemPush")
add_test(HeapTest.SingleItemPushPop "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.SingleItemPushPop")
add_test(HeapTest.TwoElementPush_LowPriFirst "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.TwoElementPush_LowPriFirst")
add_test(HeapTest.TwoElementPush_HighPriFirst "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.TwoElementPush_HighPriFirst")
add_test(HeapTest.TwoElementsSamePriority "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.TwoElementsSamePriority")
add_test(HeapTest.NegativePriorities "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.NegativePriorities")
add_test(HeapTest.ThreeElementPush_10_20_30 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_10_20_30")
add_test(HeapTest.ThreeElementPush_10_30_20 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_10_30_20")
add_test(HeapTest.ThreeElementPush_20_10_30 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_20_10_30")
add_test(HeapTest.ThreeElementPush_20_30_10 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_20_30_10")
add_test(HeapTest.ThreeElementPush_30_10_20 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_30_10_20")
add_test(HeapTest.ThreeElementPush_30_20_10 "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_30_20_10")
add_test(HeapTest.StringStorage "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.StringStorage")
add_test(HeapTest.ThreeElementPush_TrinaryHeap "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_TrinaryHeap")
add_test(HeapTest.ThreeElementPush_QuaternaryHeap "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapTest.ThreeElementPush_QuaternaryHeap")
add_test(HeapStress.50x50RandomElements_BinaryHeap "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapStress.50x50RandomElements_BinaryHeap")
add_test(HeapStress.50x50RandomElements_QuaternaryHeap "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapStress.50x50RandomElements_QuaternaryHeap")
add_test(HeapStress.50x50RandomElements_DodecenaryHeap "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapStress.50x50RandomElements_DodecenaryHeap")
add_test(HeapStress.2x10000RandomElements_Binary "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_test" "--gtest_filter=HeapStress.2x10000RandomElements_Binary")
add_test(HeapRuntime.Add "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_runtime_test" "--gtest_filter=HeapRuntime.Add")
add_test(HeapRuntime.Peek "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_runtime_test" "--gtest_filter=HeapRuntime.Peek")
add_test(HeapRuntime.Remove "/home/cs104/cs104/hw-kim503/hw6/hw6_tests/heap_tests/heap_runtime_test" "--gtest_filter=HeapRuntime.Remove")
