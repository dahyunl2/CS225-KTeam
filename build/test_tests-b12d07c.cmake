add_test( [==[Testing Airport constructor 1]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing Airport constructor 1]==]  )
set_tests_properties( [==[Testing Airport constructor 1]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
add_test( [==[Testing Airport constructor 2]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing Airport constructor 2]==]  )
set_tests_properties( [==[Testing Airport constructor 2]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
add_test( [==[Testing Graph constructor]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing Graph constructor]==]  )
set_tests_properties( [==[Testing Graph constructor]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
<<<<<<< HEAD
add_test( [==[Testing the traversed airports in BFS]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing the traversed airports in BFS]==]  )
set_tests_properties( [==[Testing the traversed airports in BFS]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
add_test( [==[Testing Djikstra's algorithm to find the shortest path]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing Djikstra's algorithm to find the shortest path]==]  )
set_tests_properties( [==[Testing Djikstra's algorithm to find the shortest path]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
add_test( [==[Testing Pagerank function top_airport()]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing Pagerank function top_airport()]==]  )
set_tests_properties( [==[Testing Pagerank function top_airport()]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
add_test( [==[Testing Pagerank implementation on a subset of the whole data set]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing Pagerank implementation on a subset of the whole data set]==]  )
set_tests_properties( [==[Testing Pagerank implementation on a subset of the whole data set]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
set( test_TESTS [==[Testing Airport constructor 1]==] [==[Testing Airport constructor 2]==] [==[Testing Graph constructor]==] [==[Testing the traversed airports in BFS]==] [==[Testing Djikstra's algorithm to find the shortest path]==] [==[Testing Pagerank function top_airport()]==] [==[Testing Pagerank implementation on a subset of the whole data set]==])
=======
add_test( [==[Testing Pagerank function top_N_airport()]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing Pagerank function top_N_airport()]==]  )
set_tests_properties( [==[Testing Pagerank function top_N_airport()]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
add_test( [==[Testing constructing graph from a subset of data and execute pagerank algorithm on the test data set]==] /workspaces/cs225/225_project/CS225-KTeam/build/test [==[Testing constructing graph from a subset of data and execute pagerank algorithm on the test data set]==]  )
set_tests_properties( [==[Testing constructing graph from a subset of data and execute pagerank algorithm on the test data set]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/225_project/CS225-KTeam/build)
set( test_TESTS [==[Testing Airport constructor 1]==] [==[Testing Airport constructor 2]==] [==[Testing Graph constructor]==] [==[Testing Pagerank function top_N_airport()]==] [==[Testing constructing graph from a subset of data and execute pagerank algorithm on the test data set]==])
>>>>>>> 57a5d65e6e94edbdd9cbc5269a897356b34c51d7
