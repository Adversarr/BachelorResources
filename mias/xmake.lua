add_requires("spdlog", {configs={fmt_external=true}})
add_requires('magic_enum')
add_requires("cxxopts")
add_requires("doctest")

target("mias-lib")
  set_kind("static")
  set_languages('cxx17')
  add_includedirs("src", {public = true})
  add_files("src/**.cpp")
  add_packages("cxxopts", "spdlog", "magic_enum", {public = true})

target("test_mias")
  set_languages("cxx17")
  add_deps('mias-lib')
  add_files("test/**.cpp")
  add_packages('doctest')

target("mias")
  set_languages("cxx17")
  add_files("standalone/**.cpp")
  add_deps('mias-lib')


