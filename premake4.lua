solution "DASH"
  configurations { "Debug", "Release" }

  targetdir "bin/"

  if _ACTION == "clean" then
    os.rmdir("bin/")
    os.rmdir("build/")
  end

  objdir "build/obj"
  location "build/"
  includedirs { "." }

project "svcNALshow"
  language "C++"
  kind "ConsoleApp"
  files { "src/**.cpp"}
  links { "boost_system", "boost_program_options"}

configuration { "Debug*" }
    defines { "_DEBUG", "DEBUG" }
    flags   { "Symbols" }
    targetname ( "svcNALshow_dbg" )

  configuration { "Release*" }
    defines { "NDEBUG" }
    flags   { "Optimize" }
