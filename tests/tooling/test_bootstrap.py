#!/usr/bin/env python3
"""Unit tests for the cross-platform bootstrap helper."""

from __future__ import annotations

from pathlib import Path
import sys
import unittest


TOOLS_DIR = Path(__file__).resolve().parents[2] / "tools"
sys.path.insert(0, str(TOOLS_DIR))

import bootstrap  # noqa: E402


class BootstrapTests(unittest.TestCase):
    def test_parse_version_accepts_tool_output(self) -> None:
        self.assertEqual(bootstrap.parse_version("cmake version 3.28.3"), (3, 28, 3))
        self.assertEqual(bootstrap.parse_version("QMake version 3.1\nUsing Qt version 6.8.3"), (3, 1, 0))

    def test_version_comparison_normalizes_width(self) -> None:
        self.assertTrue(bootstrap.version_at_least((6, 2), (6, 2, 0)))
        self.assertTrue(bootstrap.version_at_least((6, 10, 1), (6, 2, 0)))
        self.assertFalse(bootstrap.version_at_least((6, 1, 9), (6, 2, 0)))

    def test_default_build_directory_is_out_of_source(self) -> None:
        root = Path("/source")
        self.assertEqual(
            bootstrap.default_build_dir(root, "Release"),
            root / "build/bootstrap-release",
        )

    def test_dependency_hint_is_actionable(self) -> None:
        hint = bootstrap.dependency_hint()
        self.assertIn("Qt", hint)
        self.assertTrue("install" in hint.lower() or "Visual Studio" in hint)


if __name__ == "__main__":
    unittest.main()
