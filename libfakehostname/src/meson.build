fakehostname_sources = ['libfakehostname.c']

# We use libtool-version numbers because it's easier to understand.
# Before making a release, the libfakehostname_so_*
# numbers should be modified. The components are of the form C:R:A.
# a) If binary compatibility has been broken (eg removed or changed interfaces)
#    change to C+1:0:0.
# b) If interfaces have been changed or added, but binary compatibility has
#    been preserved, change to C+1:0:A+1
# c) If the interface is the same as the previous version, change to C:R+1:A
libfakehostname_lt_c=1
libfakehostname_lt_r=0
libfakehostname_lt_a=0

libfakehostname_so_version = '@0@.@1@.@2@'.format((libfakehostname_lt_c - libfakehostname_lt_a),
                                              libfakehostname_lt_a,
                                              libfakehostname_lt_r)
cc = meson.get_compiler('c')
libdl = cc.find_library('dl')
libfakehostname_lib_shared = shared_library('fakehostname',
                            fakehostname_sources,
                            version : libfakehostname_so_version,
                            dependencies: libdl,
                            install : true)
