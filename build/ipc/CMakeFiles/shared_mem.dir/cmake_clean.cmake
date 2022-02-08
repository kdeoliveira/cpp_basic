file(REMOVE_RECURSE
  "libshared_mem.a"
  "libshared_mem.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/shared_mem.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
