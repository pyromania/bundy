PYCOVERAGE_RUN = @PYCOVERAGE_RUN@

PYTESTS = d2_test.py
EXTRA_DIST = $(PYTESTS)

# Explicitly specify paths to dynamic libraries required by loadable python
# modules. That is required on Mac OS systems. Otherwise we will get exception
# about python not being able to load liblog library.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_srcdir)/src/bin:$(abs_top_builddir)/src/bin/bundy:$(abs_top_builddir)/src/lib/util/io/.libs \
	BUNDY_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(LIBRARY_PATH_PLACEHOLDER) \
		$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/d2/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

AM_CXXFLAGS = $(BUNDY_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += d2_unittests

d2_unittests_SOURCES = ../d2_asio.h
d2_unittests_SOURCES += ../d2_log.h ../d2_log.cc
d2_unittests_SOURCES += ../d_process.h
d2_unittests_SOURCES += ../d_controller.cc ../d2_controller.h
d2_unittests_SOURCES += ../d2_process.cc ../d2_process.h
d2_unittests_SOURCES += ../d2_controller.cc ../d2_controller.h
d2_unittests_SOURCES += ../d_cfg_mgr.cc ../d_cfg_mgr.h
d2_unittests_SOURCES += ../d2_config.cc ../d2_config.h
d2_unittests_SOURCES += ../d2_cfg_mgr.cc ../d2_cfg_mgr.h
d2_unittests_SOURCES += ../d2_queue_mgr.cc ../d2_queue_mgr.h
d2_unittests_SOURCES += ../d2_update_message.cc ../d2_update_message.h
d2_unittests_SOURCES += ../d2_update_mgr.cc ../d2_update_mgr.h
d2_unittests_SOURCES += ../d2_zone.cc ../d2_zone.h
d2_unittests_SOURCES += ../dns_client.cc ../dns_client.h
d2_unittests_SOURCES += ../labeled_value.cc ../labeled_value.h
d2_unittests_SOURCES += ../nc_add.cc ../nc_add.h
d2_unittests_SOURCES += ../nc_remove.cc ../nc_remove.h
d2_unittests_SOURCES += ../nc_trans.cc ../nc_trans.h
d2_unittests_SOURCES += ../state_model.cc ../state_model.h
d2_unittests_SOURCES += d_test_stubs.cc d_test_stubs.h
d2_unittests_SOURCES += d2_unittests.cc
d2_unittests_SOURCES += d2_process_unittests.cc
d2_unittests_SOURCES += d_controller_unittests.cc
d2_unittests_SOURCES += d2_controller_unittests.cc
d2_unittests_SOURCES += d_cfg_mgr_unittests.cc
d2_unittests_SOURCES += d2_cfg_mgr_unittests.cc
d2_unittests_SOURCES += d2_queue_mgr_unittests.cc
d2_unittests_SOURCES += d2_update_message_unittests.cc
d2_unittests_SOURCES += d2_update_mgr_unittests.cc
d2_unittests_SOURCES += d2_zone_unittests.cc
d2_unittests_SOURCES += dns_client_unittests.cc
d2_unittests_SOURCES += labeled_value_unittests.cc
d2_unittests_SOURCES += nc_add_unittests.cc
d2_unittests_SOURCES += nc_remove_unittests.cc
d2_unittests_SOURCES += nc_test_utils.cc nc_test_utils.h
d2_unittests_SOURCES += nc_trans_unittests.cc
d2_unittests_SOURCES += state_model_unittests.cc
nodist_d2_unittests_SOURCES = ../d2_messages.h ../d2_messages.cc

d2_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
d2_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
d2_unittests_LDADD = $(GTEST_LDADD)
d2_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libbundy-exceptions.la
d2_unittests_LDADD += $(top_builddir)/src/lib/log/libbundy-log.la
d2_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libbundy-asiodns.la
d2_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libbundy-asiolink.la
d2_unittests_LDADD += $(top_builddir)/src/lib/cc/libbundy-cc.la
d2_unittests_LDADD += $(top_builddir)/src/lib/config/libbundy-cfgclient.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcp_ddns/libbundy-dhcp_ddns.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libbundy-dhcp++.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libbundy-dhcpsrv.la
d2_unittests_LDADD += $(top_builddir)/src/lib/dns/libbundy-dns++.la
d2_unittests_LDADD += $(top_builddir)/src/lib/util/libbundy-util.la
d2_unittests_LDADD += $(top_builddir)/src/lib/hooks/libbundy-hooks.la

endif

noinst_PROGRAMS = $(TESTS)
