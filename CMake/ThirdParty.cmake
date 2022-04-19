option(ENABLE_3RD_DEBUG_INFO "3rd package debug" OFF)
option(CUSTOM_3RD_REPO "using custom 3rd repo" OFF)

if (${CUSTOM_3RD_REPO})
    set(3RD_REPO ${3RD_REPO_URL} CACHE STRING "" FORCE)
else()
    set(3RD_REPO "http://124.223.92.162" CACHE STRING "" FORCE)
endif()

set(3RD_DIR ${CMAKE_SOURCE_DIR}/ThirdParty CACHE PATH "" FORCE)
set(3RD_ZIP_DIR ${3RD_DIR}/Zip CACHE PATH "" FORCE)
set(3RD_SOURCE_DIR ${3RD_DIR}/Lib CACHE PATH "" FORCE)
set(3RD_BINARY_DIR ${CMAKE_BINARY_DIR}/ThirdPartyBuild CACHE PATH "" FORCE)
set(3RD_INSTALL_DIR ${CMAKE_BINARY_DIR}/ThirdPartyInstall CACHE PATH "" FORCE)

function(AddThirdPartyPackage)
    cmake_parse_arguments(PARAMS "BUILD" "NAME;VERSION;HASH" "ARG" ${ARGN})

    set(3RD_PACKAGE_NAME "${PARAMS_NAME}")
    set(3RD_PACKAGE_FULL_NAME "${PARAMS_NAME}-${PARAMS_VERSION}")
    set(3RD_PACKAGE_URL "${3RD_REPO}/${3RD_PACKAGE_FULL_NAME}.zip")
    set(3RD_PACKAGE_ZIP "${3RD_ZIP_DIR}/${3RD_PACKAGE_FULL_NAME}.zip")
    set(3RD_PACKAGE_SOURCE_DIR "${3RD_SOURCE_DIR}/${3RD_PACKAGE_FULL_NAME}")

    if (${PARAMS_BUILD})
        set(3RD_PACKAGE_BINARY_DIR "${3RD_BINARY_DIR}/${3RD_PACKAGE_NAME}")
        set(3RD_PACKAGE_INSTALL_DIR "${3RD_INSTALL_DIR}/${3RD_PACKAGE_NAME}/$<CONFIG>")
    endif()

    if (${ENABLE_3RD_DEBUG_INFO})
        message("")
        message("[3rd Package]")
        message(" - name: ${PARAMS_NAME}")
        message(" - version: ${PARAMS_VERSION}")
        message(" - hash: ${PARAMS_HASH}")
        message(" - full name: ${3RD_PACKAGE_FULL_NAME}")
        message(" - url: ${3RD_PACKAGE_URL}")
        message("")
    endif()

    # download zip file and check hash
    if (EXISTS ${3RD_PACKAGE_ZIP})
        message("found downloaded file for ${3RD_PACKAGE_URL} -> ${3RD_PACKAGE_ZIP}")
    else()
        message("starting download package ${3RD_PACKAGE_URL}")
        file(
            DOWNLOAD
            ${3RD_PACKAGE_URL} ${3RD_PACKAGE_ZIP}
            SHOW_PROGRESS
        )
    endif()

    # check zip file hash
    if (DEFINED PARAMS_HASH)
        file(SHA256 ${3RD_PACKAGE_ZIP} 3RD_PACKAGE_HASH_VALUE)
        if (NOT (${PARAMS_HASH} STREQUAL ${3RD_PACKAGE_HASH_VALUE}))
            message(FATAL_ERROR "check hash failed for file ${3RD_PACKAGE_ZIP}, please delete zip file and extracted files and try again")
        endif()
    endif()

    # extract files
    if (NOT EXISTS ${3RD_PACKAGE_SOURCE_DIR})
        file(
            ARCHIVE_EXTRACT
            INPUT ${3RD_PACKAGE_ZIP}
            DESTINATION ${3RD_PACKAGE_SOURCE_DIR}
        )
    endif()

    if (${PARAMS_BUILD})
        ExternalProject_Add(
            ${3RD_PACKAGE_NAME}
            SOURCE_DIR ${3RD_PACKAGE_SOURCE_DIR}
            BINARY_DIR ${3RD_PACKAGE_BINARY_DIR}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${3RD_PACKAGE_INSTALL_DIR} ${PARAMS_ARG}
            BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG>
            INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR> --config $<CONFIG>
        )
    endif()

    set(${3RD_PACKAGE_NAME}_SOURCE_DIR ${3RD_PACKAGE_SOURCE_DIR} CACHE PATH "" FORCE)
    if (${PARAMS_BUILD})
        set(${3RD_PACKAGE_NAME}_BINARY_DIR ${3RD_PACKAGE_BINARY_DIR} CACHE PATH "" FORCE)
        set(${3RD_PACKAGE_NAME}_INSTALL_DIR ${3RD_PACKAGE_INSTALL_DIR} CACHE PATH "" FORCE)
    endif()
endfunction()
