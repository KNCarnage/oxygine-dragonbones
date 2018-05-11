cmake_minimum_required (VERSION 2.6)
project (OXYGINESOUND)

set(OXYGINEDRAGONBONES_INCLUDE_DIRS 
	${CMAKE_CURRENT_SOURCE_DIR}/src
	)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(OXYGINEDRAGONBONES_DEFINITIONS	
	-DOXYGINE_DRAGONBONES=1)

set(SRC
	src/Character.h
	src/Character.cpp

	src/lib/Animation.h	
	src/lib/Animation.cpp

	src/lib/Armature.h	
	src/lib/Armature.cpp

	src/lib/Bone.h		
	src/lib/Bone.cpp

	src/lib/db.h	

	src/lib/Display.h	
	src/lib/Display.cpp

	src/lib/Frame.h	
	src/lib/Frame.cpp

	src/lib/Skeleton.h	
	src/lib/Skeleton.cpp

	src/lib/Skin.h	
	src/lib/Skin.cpp

	src/lib/Slot.h	
	src/lib/Slot.cpp

	src/lib/Timeline.h	
	src/lib/Timeline.cpp

	src/lib/Transform.h	
	src/lib/Transform.cpp
	)


add_library(oxygine-dragonbones STATIC ${SRC})

set(OXYGINEDRAGONBONES_LIBS
		oxygine-dragonbones)	

if(EMSCRIPTEN)
	set(linkFlags "-Wno-warn-absolute-paths")
	set_target_properties(oxygine-dragonbones PROPERTIES LINK_FLAGS "${linkFlags}")
endif(EMSCRIPTEN)

include_directories(${OXYGINEDRAGONBONES_INCLUDE_DIRS})
include_directories(src/lib)




#target_link_libraries(oxyginemagicparticles)
set(OXYGINEDRAGONBONES_INCLUDE_DIRS 
	${CMAKE_CURRENT_SOURCE_DIR}/src)

set(OXYGINEDRAGONBONES_INCLUDE_DIRS ${OXYGINEDRAGONBONES_INCLUDE_DIRS} PARENT_SCOPE)
set(OXYGINEDRAGONBONES_LIBS ${OXYGINEDRAGONBONES_LIBS} PARENT_SCOPE)
set(OXYGINEDRAGONBONES_DEFINITIONS ${OXYGINEDRAGONBONES_DEFINITIONS} PARENT_SCOPE)