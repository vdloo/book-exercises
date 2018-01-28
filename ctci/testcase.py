from unittest import TestCase
from unittest.mock import patch, Mock


class TestCase(TestCase):
    def set_up_patch(self, patch_target, mock_target=None, **kwargs):
        patcher = patch(patch_target, mock_target or Mock(**kwargs))
        self.addCleanup(patcher.stop)
        return patcher.start()
