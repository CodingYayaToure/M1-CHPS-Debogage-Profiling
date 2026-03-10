# =============================================================================
# CUSTOM COMMANDS AND TARGETS
# =============================================================================
set(DATDIR data)
set(GRPDIR graphs)

find_program(BASH bash HINTS /bin)

add_subdirectory(${DATDIR})
add_subdirectory(${GRPDIR})

# =============================================================================
# PERFTOOL configuration - Q-3.1.1 et Q-3.1.2
# Décommenter la ligne souhaitée :
# =============================================================================
set(PERFTOOL "")
#set(TOOL "time --")
#set(TOOL "perf stat --")
# Q-3.1.1 : Compteurs perf stat
#set(PERFTOOL "perf stat")
# Q-3.1.2 : Profiling perf record
#set(PERFTOOL "perf record -g -F 999")
#set(PERFOPTIONS "")

set(TBASENAME "tst")

get_property(OPTIONS GLOBAL PROPERTY PROP_OPTIONS)
get_property(VERSIONS GLOBAL PROPERTY PROP_VERSIONS)

set(PARAMS 0400 0512 0800 1000)
# ===================================================================================================
# Setting ALL_RUNS
# ===================================================================================================
set(DATA_GROUP_ALL_FILE ${DATDIR}/grall.data)
add_custom_target(TDATA_GROUP_ALL DEPENDS ${DATA_GROUP_ALL_FILE})
add_custom_target(ALL_RUNS)

set(PLT_GROUP_ALL_FILE ${GRPDIR}/pltall.plt)
set(PDF_GROUP_ALL_FILE ${GRPDIR}/pdfall.pdf)
add_custom_target(TPLT_GROUP_ALL DEPENDS ${PLT_GROUP_ALL_FILE})
add_custom_target(TPDF_GROUP_ALL DEPENDS ${PDF_GROUP_ALL_FILE})

# ===================================================================================================
# ALL_RUNS and DATA FILE generation
# ===================================================================================================
foreach(OPT ${OPTIONS})
  add_dependencies(ALL_RUNS ${OPT}_RUNS)
  add_custom_target(${OPT}_RUNS)
  foreach(VER ${VERSIONS})
    foreach(PARAM ${PARAMS})
      set(TNAME ${TBASENAME}${VER}${OPT})
      set(TBIN ${TNAME})
      set(TTARG ${TNAME}_${PARAM})
      set(TDATA ${DATDIR}/${TTARG}.data)
      set(TPERFDATA ${DATDIR}/_perf_${TTARG}.data)
        add_custom_target(${TTARG} DEPENDS ${TDATA} ${TBIN})
      if (${PERFTOOL} MATCHES "perf *")
      add_custom_command(OUTPUT ${TDATA}
        COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "${PERFTOOL} ${PERFOPTIONS} --output=${TPERFDATA} -- ../${TBIN} ${PARAM} >& ${TDATA}"
        DEPENDS ../${TBIN}
        VERBATIM
      )
      else()
      add_custom_command(OUTPUT ${TDATA}
        COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "${PERFTOOL} ../${TBIN} ${PARAM} >& ${TDATA}"
        DEPENDS ../${TBIN}
        VERBATIM
      )
      endif()
      add_dependencies(${OPT}_RUNS ${TTARG})
    endforeach()
  endforeach()
endforeach()

# ===================================================================================================
# DATA GROUPMENT
# ===================================================================================================
foreach(PARAM ${PARAMS})
  set(DATA_GROUP_FILE ${DATDIR}/_generated_group_${PARAM}.data)
  set(TDATA_GROUP_FILE T${DATDIR}_gr_${PARAM})
  add_custom_target(${TDATA_GROUP_FILE} DEPENDS ${DATA_GROUP_FILE})
  add_custom_command(OUTPUT ${DATA_GROUP_FILE}
    COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "(printf '${PARAM}\\t' && cat ${DATDIR}/${TBASENAME}*_${PARAM}.data | cut -f 4 | tr '\\n' '\\t' | sed -e '$a\\') >& ${DATA_GROUP_FILE}"
    VERBATIM
  )
  add_dependencies(TDATA_GROUP_ALL ${TDATA_GROUP_FILE})
endforeach()

add_custom_command(OUTPUT ${DATA_GROUP_ALL_FILE}
  COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "cat ${DATDIR}/_generated_group_*.data >& ${DATA_GROUP_ALL_FILE}"
  VERBATIM
)

# ===================================================================================================
# GNUPLOT FILE generation (.PLT)
# ===================================================================================================
set(I "2")
foreach(VER ${VERSIONS})
  foreach(OPT ${OPTIONS})
    set(TNAME ${TBASENAME}${VER}${OPT})
    set(TBIN ${TNAME})
    set(TPTARG TPLT_${TNAME})
    set(PLTFILE ${GRPDIR}/_generated_group_${TPTARG}.plt)

    add_custom_target(${TPTARG} DEPENDS ${PLTFILE})
    add_dependencies(TPLT_GROUP_ALL ${TPTARG})

    add_custom_command(OUTPUT ${PLTFILE}
      DEPENDS TDATA_GROUP_ALL ${DATA_GROUP_ALL_FILE}
      COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "printf '\\t\"${DATA_GROUP_ALL_FILE}\" u 1:${I} w lp title \"${VER}-${OPT}\", ' >> ${PLTFILE}"
      VERBATIM
    )
    MATH(EXPR I "${I}+1")
  endforeach()
endforeach()

# ===================================================================================================
# DATA GROUP ALL and FINAL GNUPLOT FILE generation
# ===================================================================================================

set(PLT_PROLOG ${GRPDIR}/_generated_group_000_prologue.plt)
add_custom_command(OUTPUT ${PLT_PROLOG}
  COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "printf 'set terminal pdf\\nset xlabel \"Sizes\"\\nset ylabel \"Cycles\"\\nset multiplot\\nplot ' >& ${PLT_PROLOG}"
  VERBATIM
)

add_custom_target(TPLT_PROLOG DEPENDS ${PLT_PROLOG})
add_dependencies(TPLT_GROUP_ALL TPLT_PROLOG)

add_custom_command(OUTPUT ${PLT_GROUP_ALL_FILE}
  DEPENDS ${GRPDIR}/_generated_group_*.plt
  COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "cat ${GRPDIR}/_generated_group_*.plt >& ${PLT_GROUP_ALL_FILE}"
  VERBATIM
)

add_custom_command(OUTPUT ${PDF_GROUP_ALL_FILE}
  DEPENDS TDATA_GROUP_ALL ${DATA_GROUP_ALL_FILE} ${PLT_GROUP_ALL_FILE}
  COMMAND ${CMAKE_COMMAND} -E env ${BASH} -c "gnuplot ${PLT_GROUP_ALL_FILE} >& ${PDF_GROUP_ALL_FILE}"
  VERBATIM
)

add_dependencies(TPDF_GROUP_ALL TPLT_GROUP_ALL)

add_custom_target(RALL ALL DEPENDS ALL_RUNS)
add_custom_target(GALL DEPENDS TPDF_GROUP_ALL ${PDF_GROUP_ALL_FILE})
