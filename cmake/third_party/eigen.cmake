include (ExternalProject)

set(EIGEN_INCLUDE_DIR ${THIRD_PARTY_DIR}/eigen/include/eigen3)
set(EIGEN_INSTALL_DIR ${THIRD_PARTY_DIR}/eigen)

set(EIGEN_URL ${CMAKE_CURRENT_BINARY_DIR}/third_party/eigen/src/eigen)

add_definitions(-DEIGEN_NO_AUTOMATIC_RESIZING -DEIGEN_USE_GPU)
if (NOT WITH_XLA)
add_definitions(-DEIGEN_NO_MALLOC)
endif()
#add_definitions(-DEIGEN_NO_AUTOMATIC_RESIZING -DEIGEN_NO_MALLOC -DEIGEN_USE_GPU)

if (THIRD_PARTY)
  
ExternalProject_Add(eigen
    PREFIX eigen
    URL ${EIGEN_URL}
    UPDATE_COMMAND ""
    INSTALL_DIR "${EIGEN_INSTALL_DIR}"
    CMAKE_CACHE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF
        -DCMAKE_INSTALL_PREFIX:STRING=${EIGEN_INSTALL_DIR}
        -DCMAKE_CXX_FLAGS_DEBUG:STRING=${CMAKE_CXX_FLAGS_DEBUG}
        -DCMAKE_CXX_FLAGS_RELEASE:STRING=${CMAKE_CXX_FLAGS_RELEASE}
        -DBUILD_TESTING:BOOL=OFF
)


endif(THIRD_PARTY)
