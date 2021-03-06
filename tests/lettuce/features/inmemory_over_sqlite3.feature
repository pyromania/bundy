Feature: In-memory zone using SQLite3 backend
    This feature tests the authoritative server configured with an in-memory
    data source that uses the SQLite3 data source as the backend, and tests
    scenarios that update the zone via incoming zone transfers.

    Scenario: 1. Load and response
        Given I have bundy running with configuration inmemory_over_sqlite3/secondary.conf
        And wait for bundy stderr message BUNDY_STARTED_CC
        And wait for bundy stderr message CMDCTL_STARTED
        And wait for bundy stderr message AUTH_SERVER_STARTED
        A query for www.example.org should have rcode NOERROR
        The SOA serial for example.org should be 1234

    Scenario: 2. In-memory datasource backed by sqlite3
        Given I have bundy running with configuration xfrin/retransfer_master.conf with cmdctl port 56174 as master
        And wait for master stderr message BUNDY_STARTED_CC
        And wait for master stderr message CMDCTL_STARTED
        And wait for master stderr message AUTH_SERVER_STARTED
        And wait for master stderr message XFROUT_STARTED
        And wait for master stderr message ZONEMGR_STARTED

        And I have bundy running with configuration xfrin/inmem_slave.conf
        And wait for bundy stderr message BUNDY_STARTED_CC
        And wait for bundy stderr message CMDCTL_STARTED
        And wait for bundy stderr message AUTH_SERVER_STARTED
        And wait for bundy stderr message XFRIN_STARTED
        And wait for bundy stderr message ZONEMGR_STARTED

        A query for www.example.org to [::1]:56176 should have rcode NOERROR
        """
        www.example.org.        3600    IN      A       192.0.2.63
        """
        A query for mail.example.org to [::1]:56176 should have rcode NXDOMAIN
        When I send bundy the command Xfrin retransfer example.org IN ::1 56177
        Then wait for new bundy stderr message XFRIN_TRANSFER_SUCCESS not XFRIN_XFR_PROCESS_FAILURE
        Then wait for new bundy stderr message AUTH_DATASRC_CLIENTS_BUILDER_LOAD_ZONE

        A query for www.example.org to [::1]:56177 should have rcode NOERROR
        The answer section of the last query response should be
        """
        www.example.org.        3600    IN      A       192.0.2.1
        """
        A query for mail.example.org to [::1]:56176 should have rcode NOERROR
