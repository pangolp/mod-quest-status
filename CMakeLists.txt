AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/QuestStatusCommand.cpp")
AC_ADD_SCRIPT_LOADER("QuestStatus" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/mod_quest_status.conf.dist")
