


execute_process(COMMAND git log --pretty=format:'%h' -n 1
        OUTPUT_VARIABLE GIT_REV
        ERROR_QUIET)

# Check whether we got any revision (which isn't
# always the case, e.g. when someone downloaded a zip
# file from Github instead of a checkout)
if ("${GIT_REV}" STREQUAL "")
    set(GIT_REV "N/A")
    set(GIT_DIFF "")
    set(GIT_TAG "N/A")
    set(GIT_BRANCH "N/A")
    set(GIT_NUMBER "N/A")
else ()
    if (NOT CONTINOUS_INTEGRATION)
        execute_process(
                COMMAND bash -c "git diff --quiet --exit-code || echo +"
                OUTPUT_VARIABLE GIT_DIFF)
    endif ()
    execute_process(
            COMMAND git describe --exact-match --tags
            OUTPUT_VARIABLE GIT_TAG ERROR_QUIET)
    execute_process(
            COMMAND git rev-parse --abbrev-ref HEAD
            OUTPUT_VARIABLE GIT_BRANCH)
    execute_process(
            COMMAND git rev-list HEAD --count
            OUTPUT_VARIABLE GIT_NUMBER)

    string(STRIP "${GIT_REV}" GIT_REV)
    string(SUBSTRING "${GIT_REV}" 1 7 GIT_REV)
    string(STRIP "${GIT_DIFF}" GIT_DIFF)
    string(STRIP "${GIT_TAG}" GIT_TAG)
    string(STRIP "${GIT_BRANCH}" GIT_BRANCH)
    string(STRIP "${GIT_NUMBER}" GIT_NUMBER)
endif ()

set(VERSION
        "const char* ${PROJECT_NAME}_MAJOR_VERSION=\"${${PROJECT_NAME}_MAJOR_VERSION}\";
        const char* ${PROJECT_NAME}_MINOR_VERSION=\"${${PROJECT_NAME}_MINOR_VERSION}\";
        const char* GIT_REV=\"${GIT_REV}${GIT_DIFF}\";
        const char* GIT_TAG=\"${GIT_TAG}\";
        const char* GIT_BRANCH=\"${GIT_BRANCH}\";
        const char* GIT_NUMBER=\"${GIT_NUMBER}\";")

set(VERSION_FILEPATH ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)

if (EXISTS ${VERSION_FILEPATH})
    file(READ ${VERSION_FILEPATH} VERSION_)
else ()
    set(VERSION_ "")
endif ()

if (NOT "${VERSION}" STREQUAL "${VERSION_}")
    file(WRITE ${VERSION_FILEPATH} "${VERSION}")
endif ()

message(STATUS "${PROJECT_NAME} Version: ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${GIT_NUMBER}")