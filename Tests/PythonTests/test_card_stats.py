import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from Scripts import card_stats


class CardStatsTest(unittest.TestCase):
    def test_collect_rejects_malformed_row(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            documents = root / "Documents"
            documents.mkdir()
            path = documents / "CardList - Standard.md"
            for row in (
                "CORE | CORE_001 | Missing Status",
                "CORE | CORE_002 | Extra Cell | O | unexpected",
            ):
                with self.subTest(row=row):
                    path.write_text(
                        f"## Core\nSet | ID | Name | Implemented\n:---: | :---: | :---: | :---:\n{row}\n",
                        encoding="utf-8",
                    )

                    with patch.object(card_stats, "ROOT", root):
                        with self.assertRaises(ValueError) as error:
                            card_stats.collect("Standard")

                    self.assertIn(str(path), str(error.exception))
                    self.assertIn(row, str(error.exception))


if __name__ == "__main__":
    unittest.main()
