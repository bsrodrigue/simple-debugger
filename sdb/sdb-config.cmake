install(
        EXPORT sdb-targets
        FILE sdb-config.cmake
        NAMESPACE sdb::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sdb
)
