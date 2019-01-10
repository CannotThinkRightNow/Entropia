##################################################
# Boost
##################################################

# System
# Files
file (GLOB_RECURSE BOOST_SYSTEM_INCLUDE CONFIGURE_DEPENDS "system/include/*")
file (GLOB_RECURSE BOOST_SYSTEM_SOURCE CONFIGURE_DEPENDS "system/src/*")

# Targets
add_library (boost_system ${BOOST_SYSTEM_INCLUDE} ${BOOST_SYSTEM_SOURCE})
target_include_directories (boost_system SYSTEM PUBLIC ${BOOST_SYSTEM_INCLUDE} PRIVATE ${BOOST_SYSTEM_SOURCE})

# Filesystem
# Files
file (GLOB_RECURSE BOOST_FILESYSTEM_INCLUDE CONFIGURE_DEPENDS "filesystem/include/*")
file (GLOB_RECURSE BOOST_FILESYSTEM_SOURCE CONFIGURE_DEPENDS "filesystem/src/*")

# Targets
add_library (boost_filesystem ${BOOST_FILESYSTEM_INCLUDE} ${BOOST_FILESYSTEM_SOURCE})
target_link_libraries (boost_filesystem boost_system)
target_include_directories (boost_filesystem SYSTEM PUBLIC ${BOOST_FILESYSTEM_INCLUDE} PRIVATE ${BOOST_FILESYSTEM_SOURCE})

# Packaging
install (TARGETS boost_system boost_filesystem DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${BOOST_SYSTEM_INCLUDE} ${BOOST_SYSTEM_SOURCE}
               ${BOOST_FILESYSTEM_INCLUDE} ${BOOST_FILESYSTEM_SOURCE}
         DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PLATFORM}")
