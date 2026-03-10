# =============================================================================
# CUSTOM COMMANDS AND TARGETS
# =============================================================================
set(DATDIR data)
set(GRPDIR graphs)

find_program(BASH bash HINTS /bin)

add_subdirectory(${DATDIR})
add_subdirectory(${GRPDIR})

set(TOOL "")
#set(TOOL "time --")
#set(TOOL "perf stat --")

# set(OPTIONS "O0" "O1" "O2" "O3")
# set(VERSIONS "001" "002" "003")

set(TBASENAME "tst")

get_property(OPTIONS GLOBAL PROPERTY PROP_OPTIONS)
get_property(VERSIONS GLOBAL PROPERTY PROP_VERSIONS)


set(PARAMS 0400 0800 1000)


# ===================================================================================================
# Setting ALL_RUNS
# ===================================================================================================

add_custom_target(ALL_RUNS)
#add_custom_target(ALL_GRDAT)

#add_dependencies(BALLS ALL_RUNS)

foreach(OPT ${OPTIONS})
  add_dependencies(ALL_RUNS ${OPT}_RUNS)
  add_custom_target(${OPT}_RUNS)

  foreach(VER ${VERSIONS})

    foreach(PARAM ${PARAMS})
      set(TNAME ${TBASENAME}${VER})

      set(TSTBIN ${TNAME}${OPT})
      set(TSTTGT R${TNAME}${OPT}_${PARAM})
      set(TSTDAT ${DATDIR}/${TSTTGT}.data)
      add_custom_target(${TSTTGT} DEPENDS ${TSTDAT} ${TSTBIN})
      add_custom_command(OUTPUT ${TSTDAT}
        COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "${TOOL} ../${TSTBIN} ${PARAM} >& ${TSTDAT}"
        DEPENDS ../${TSTBIN}
        VERBATIM
      )
      add_dependencies(${OPT}_RUNS ${TSTTGT})
    endforeach()
  endforeach()
endforeach()

set(GRALL_FILE ${GRPDIR}/grall.data)
add_custom_target(GALL DEPENDS ${GRALL_FILE})

add_custom_target(TTGRALL DEPENDS ${GRALL_FILE})

foreach(PARAM ${PARAMS})
  set(GRFILE ${GRPDIR}/gr_${PARAM}.data)
  set(TTGRFILE TT${GRPDIR}_gr_${PARAM})
  add_custom_target(${TTGRFILE} DEPENDS ${GRFILE})
  add_custom_command(OUTPUT ${GRFILE}
    COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "(printf '${PARAM}\\t' && cat ${DATDIR}/R${TBASENAME}*_${PARAM}.data | cut -f 4 | tr '\\n' '\\t' | sed -e '\$a\\') >& ${GRFILE}"
    VERBATIM
  )
  add_dependencies(TTGRALL ${TTGRFILE})
  #  add_dependencies(GALL ${GRFILE})
endforeach()

add_custom_command(OUTPUT ${GRALL_FILE}
  COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "cat ${GRPDIR}/gr_*.data >& ${GRALL_FILE}"
  VERBATIM
)
add_dependencies(GALL TTGRALL)

add_custom_target(BALLS ALL DEPENDS ALL_RUNS)
