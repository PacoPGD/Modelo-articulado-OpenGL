INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./obj)
INCLUDE_DIRECTORIES(./3ds)
INCLUDE_DIRECTORIES(./math)
INCLUDE_DIRECTORIES(/usr/include/SDL)

FILE(GLOB hdrs_base "*.h*")
FILE(GLOB srcs_base "*.c*")
FILE(GLOB srcs_3ds "3ds/*.c*" )
FILE(GLOB srcs_obj "obj/*.c*" )
FILE(GLOB srcs_math "math/*.c*" )
FILE(GLOB hdrs_3ds "3ds/*.h*")
FILE(GLOB hdrs_obj "obj/*.h*")
FILE(GLOB hdrs_math "math/*.h*")

FILE(GLOB srcs ${srcs_base} ${srcs_3ds} ${srcs_obj} ${srcs_math})
FILE(GLOB hdrs ${hdrs_base} ${hdrs_3ds} ${hdrs_obj} ${hdrs_math})         

SET(hdrs ${hdrs})
SET(srcs ${srcs})


ADD_LIBRARY(${PROJECT_NAME} ${srcs} ${hdrs})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES 				# create *nix style library versions + symbolic links
	DEFINE_SYMBOL DSO_EXPORTS
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_SOVERSION}
	CLEAN_DIRECT_OUTPUT 1 					# allow creating static and shared libs without conflicts
	OUTPUT_NAME "${PROJECT_NAME}${PROJECT_DLLVERSION}" 	# avoid conflicts between library and binary target names
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${REQUIRED_LIBRARIES}) 

INSTALL(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin COMPONENT main			# Install the dll file in bin directory
	LIBRARY DESTINATION lib PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE COMPONENT main
	ARCHIVE DESTINATION lib COMPONENT main)			# Install the dll.a file in lib directory

INSTALL(FILES ${hdrs}
	DESTINATION include/${PROJECT_NAME}
	COMPONENT main)

