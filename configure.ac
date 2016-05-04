dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(alenka-distributed, 0.1)

AC_CHECK_LIB([boost_thread], [main], [],[
         echo "boost_thread library is required for this program"
         exit -1])
         
AC_CHECK_LIB([boost_program_options], [main], [],[
         echo "boost_program_options library is required for this program"
         exit -1])
                 
AC_CHECK_LIB([boost_system], [main], [],[
         echo "boost_system library is required for this program"
         exit -1])
         
AC_CHECK_LIB([config++], [main], [],[
         echo "libconfig library is required for this program"
         exit -1])

AC_CHECK_LIB([pthread], [main], [],[
         echo "pthread library is required for this program"
         exit -1])
         
AC_CHECK_LIB([zookeeper_mt], [main], [],[
         echo "zookeeper_mt library is required for this program"
         exit -1])

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT

