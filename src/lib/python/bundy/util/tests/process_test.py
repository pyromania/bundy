# Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

"""Tests for bundy.util.process."""
import unittest
import bundy.util.process
run_tests = True
try:
    import setproctitle
except ImportError:
    run_tests = False

class TestRename(unittest.TestCase):
    """Testcase for bundy.process.rename."""
    def __get_self_name(self):
        return setproctitle.getproctitle()

    @unittest.skipIf(not run_tests, "Setproctitle not installed, not testing")
    def test_rename(self):
        """Test if the renaming function works."""
        bundy.util.process.rename("rename-test")
        self.assertEqual("rename-test", self.__get_self_name())
        bundy.util.process.rename()
        self.assertEqual("process_test.py", self.__get_self_name())

if __name__ == "__main__":
    unittest.main()
