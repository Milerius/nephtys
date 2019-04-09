macro(download_app_image)
    if (LINUX)
        ## We need appimage
        if (NOT EXISTS ${PROJECT_SOURCE_DIR}/tools/linux/linuxdeploy-x86_64.AppImage)
            file(DOWNLOAD
                    https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
                    ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage
                    SHOW_PROGRESS
                    )
        endif ()
        if (EXISTS ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage)
            file(COPY
                    ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage DESTINATION
                    ${PROJECT_SOURCE_DIR}/tools/linux/
                    FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)
        endif ()
        if (EXISTS ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage)
            file(REMOVE ${PROJECT_SOURCE_DIR}/tools/linuxdeploy-x86_64.AppImage)
        endif ()
    endif ()
endmacro()

macro(init_env)
    if (UNIX AND NOT APPLE)
        set(LINUX TRUE)
    endif ()
endmacro()

macro(exec_conan)
    if (NOT EXISTS conanbuildinfo.cmake)
        message("Conan need to be executed")
        message("Conan installing remote ...")

        execute_process(COMMAND conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan)
        execute_process(COMMAND conan remote add skypjack https://api.bintray.com/conan/skypjack/conan)
        execute_process(COMMAND conan remote add conan-doom_strong_types https://api.bintray.com/conan/milerius/doom_strong_types)

        execute_process(COMMAND conan install ../
                RESULT_VARIABLE CMD_ERROR
                OUTPUT_FILE CMD_OUTPUT)
        MESSAGE(STATUS "CMD_ERROR:" ${CMD_ERROR})
        MESSAGE(STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})
    else ()
        message("Conan doesn't need to be executed")
    endif ()
endmacro()

macro(init_nephtys)
    init_env()
    exec_conan()
    download_app_image()
endmacro()