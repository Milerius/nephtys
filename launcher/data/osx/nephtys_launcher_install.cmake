if (APPLE)
    set_target_properties(nephtys_launcher PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME "nephtys_launcher"
            RESOURCE data/osx/nephtys_launcher.icns
            MACOSX_BUNDLE_ICON_FILE nephtys_launcher
            MACOSX_BUNDLE_SHORT_VERSION_STRING 0.0.1
            MACOSX_BUNDLE_LONG_VERSION_STRING 0.0.1
            MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/cmake/MacOSXBundleInfo.plist.in")
    configure_file(${PROJECT_SOURCE_DIR}/vendor/noesisgui/runtime/osx/Noesis.dylib
            ${CMAKE_BINARY_DIR}/bin/nephtys_launcher.app/Contents/Frameworks/Noesis.dylib COPYONLY)
    add_custom_command(TARGET nephtys_launcher
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/"
            $<TARGET_FILE:nephtys_launcher>)
    add_custom_command(TARGET nephtys_launcher
            POST_BUILD COMMAND
            ${CMAKE_INSTALL_NAME_TOOL} -change "@rpath/Noesis.dylib" "../Frameworks/Noesis.dylib"
            $<TARGET_FILE:nephtys_launcher>)
endif ()

if (APPLE)
    install(TARGETS nephtys_launcher
            BUNDLE DESTINATION . COMPONENT Runtime
            RUNTIME DESTINATION bin COMPONENT Runtime
            )

    # Note Mac specific extension .app
    set(APPS "\${CMAKE_INSTALL_PREFIX}/nephtys_launcher.app")

    # Directories to look for dependencies
    set(DIRS ${CMAKE_BINARY_DIR})

    install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

    set(CPACK_GENERATOR "DRAGNDROP")
    set(CPACK_DMG_DS_STORE_SETUP_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/data/osx/Packaging_CMakeDMGSetup.scpt")
    set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_CURRENT_SOURCE_DIR}/data/osx/Packaging_CMakeDMGBackground.tif")
    set(CPACK_PACKAGE_NAME "nephtys_launcher")
    include(CPack)
endif ()