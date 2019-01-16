# CMake generated Testfile for 
# Source directory: /home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams
# Build directory: /home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Streams.NoWords "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams/streams_test" "--gtest_filter=Streams.NoWords")
add_test(Streams.OneWord "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams/streams_test" "--gtest_filter=Streams.OneWord")
add_test(Streams.FiveWordsSameLine "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams/streams_test" "--gtest_filter=Streams.FiveWordsSameLine")
add_test(Streams.FiveWordsSeparateLines "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams/streams_test" "--gtest_filter=Streams.FiveWordsSeparateLines")
add_test(Streams.MixedWhitespace "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams/streams_test" "--gtest_filter=Streams.MixedWhitespace")
add_test(Streams.ThousandWordStressTest "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/cs104/cs104/hw-kim503/hw1/hw1_tests/streams/streams_test" "--gtest_filter=Streams.ThousandWordStressTest")
