cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        include/model/Client.h
        include/model/Repair.h
        include/model/Service.h

        src/model/Client.cpp
        src/model/Repair.cpp
        src/model/Service.cpp
        include/repositories/ClientRepository.h
        include/repositories/ServiceRepository.h
        src/repositories/ClientRepository.cpp
        src/repositories/ServiceRepository.cpp

        include/managers/ClientManager.h
        include/managers/ServiceManager.h
        src/managers/ClientManager.cpp
        src/managers/ServiceManager.cpp

        include/model/ClientType.h
        include/model/EngineRepair.h
        include/model/TyreRepair.h
        src/model/EngineRepair.cpp
        src/model/TyreRepair.cpp
        include/model/TimingChainRepair.h
        src/model/TimingChainRepair.cpp
        src/model/OilChange.cpp
        include/model/OilChange.h
        src/model/ClientType.cpp
        include/typedefs.h

)

# Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

# Włączenie testów powoduje pojawienie się celu test w Makefiles
enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)
find_package(Boost 1.60.0 COMPONENTS "date_time" REQUIRED)


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        include/test/model/master.cpp
        include/test/model/ClientTest.cpp
        include/test/model/RepairTest.cpp
        include/test/model/ServiceTest.cpp
        include/test/repositories/ClientRepositoryTest.cpp
        include/test/managers/ClientManagerTest.cpp
        include/test/managers/ServiceManagerTest.cpp
        include/test/repositories/ServiceRepositoryTest.cpp

) # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTester ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów

target_link_libraries (LibraryTester
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)

#czy ta linia jest potrzebna? niech ktos pomoze
target_include_directories(LibraryTester PRIVATE ${Boost_INCLUDE_DIRS})

#dodaj test LibraryTest. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest LibraryTester
        --report_level=detailed
        --log_level=all
        --color_output=yes
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})