set(component_srcs "main.c" "ds3231.c")

# get IDF version for comparison
set(idf_version "${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}")

if(idf_version VERSION_GREATER_EQUAL "5.2")
    list(APPEND component_srcs "i2cdev_new.c")
else()
    list(APPEND component_srcs "i2cdev_legacy.c")
endif()

idf_component_register(SRCS ${component_srcs} INCLUDE_DIRS ".")
