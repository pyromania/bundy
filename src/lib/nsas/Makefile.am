SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(MULTITHREADING_FLAG)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/nsas -I$(top_builddir)/src/lib/nsas
AM_CXXFLAGS = $(BUNDY_CXXFLAGS)

# Some versions of GCC warn about some versions of Boost regarding missing
# initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
AM_CXXFLAGS += $(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# clang++ complains about unused function parameters in some boost header
# files.
if USE_CLANGPP
AM_CXXFLAGS += -Wno-unused-parameter
endif

# Define rule to build logging source files from message file
nsas_messages.h nsas_messages.cc: s-messages

s-messages: nsas_messages.mes
	$(top_builddir)/src/lib/log/compiler/message $(top_srcdir)/src/lib/nsas/nsas_messages.mes
	touch $@

# What is being built.
lib_LTLIBRARIES = libbundy-nsas.la

# Tell Automake that the nsas_messages.{cc,h} source files are created in the build
# process, so it must create these before doing anything else.  Although they
# are a dependency of the library (so will be created from the message file
# anyway), there is no guarantee as to exactly _when_ in the build they will be
# created.  As the .h file is included in other sources file (so must be
# present when they are compiled), the safest option is to create it first.
BUILT_SOURCES = nsas_messages.h nsas_messages.cc

# Library sources. The generated files will not be in the distribution.
libbundy_nsas_la_SOURCES  = address_entry.h address_entry.cc
libbundy_nsas_la_SOURCES += hash.cc hash.h
libbundy_nsas_la_SOURCES += hash_deleter.h
libbundy_nsas_la_SOURCES += hash_key.cc hash_key.h
libbundy_nsas_la_SOURCES += hash_table.h
libbundy_nsas_la_SOURCES += nameserver_address_store.cc nameserver_address_store.h
libbundy_nsas_la_SOURCES += nameserver_address.h nameserver_address.cc
libbundy_nsas_la_SOURCES += nameserver_entry.cc nameserver_entry.h
libbundy_nsas_la_SOURCES += nsas_entry_compare.h
libbundy_nsas_la_SOURCES += nsas_entry.h nsas_types.h
libbundy_nsas_la_SOURCES += nsas_log.cc nsas_log.h
libbundy_nsas_la_SOURCES += zone_entry.cc zone_entry.h
libbundy_nsas_la_SOURCES += fetchable.h
libbundy_nsas_la_SOURCES += address_request_callback.h
libbundy_nsas_la_SOURCES += glue_hints.h glue_hints.cc

nodist_libbundy_nsas_la_SOURCES  = nsas_messages.h nsas_messages.cc

# The message file should be in the distribution.
EXTRA_DIST = nsas_messages.mes

# Make sure that the generated files are got rid of in a clean operation
CLEANFILES = *.gcno *.gcda nsas_messages.h nsas_messages.cc s-messages
