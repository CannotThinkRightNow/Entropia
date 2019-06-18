##################################################
# Packaging
##################################################

# Common
set(CPACK_PACKAGE_VENDOR "William So")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION_STRING})
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/cpack/description.txt")
set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/cpack/icon.png")
set(CPACK_PACKAGE_CHECKSUM "SHA3_512")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "${PROJECT_SOURCE_DIR}/cpack/welcome.txt")

# Source
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAMESPACE}-${PROJECT_VERSION_STRING}")

# Packaging
include(InstallRequiredSystemLibraries)
include(CPack)
