cmake_minimum_required(VERSION 2.8.4)
project(Icecap)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/Program\ Files/Java/jdk1.8.0_121/include C:/Program\ Files/Java/jdk1.8.0_121/include/win32)

set(SOURCE_FILES icecap/collection/list/jlist.cpp icecap/collection/list/jlist.h icecap/collection/list/jlist_fwd.h icecap/collection/list/jlist_iterator.cpp icecap/collection/set/jset_fwd.h icecap/collection/set/jset.h icecap/collection/jcollection_fwd.h icecap/collection/jcollection.h icecap/collection/jcollection.cpp icecap/collection/set/jset.cpp icecap/collection/map/jmap_fwd.h icecap/collection/map/jmap.h icecap/collection/map/jmap.cpp icecap/jadapter.h icecap/jadapter.cpp icecap/jcontainer.h icecap/jcontainer.cpp icecap/JavaStandardOutputBuffer.cpp icecap/field.cpp icecap/array.cpp)
add_library(Icecap SHARED ${SOURCE_FILES})