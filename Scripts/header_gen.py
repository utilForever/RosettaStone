#!/usr/bin/env python

import filecmp
import inspect
import shutil
import os
import utils

dirname = os.path.dirname(os.path.abspath(
    inspect.getfile(inspect.currentframe())))

def main():
    include_dir = os.path.join(dirname, "../Includes/hspp")
    filenames = utils.get_all_files(include_dir, ["*.h"])
    filenames.sort()
    header = os.path.join(dirname, "../Includes/hspp/hspp.h")
    header_tmp = header + ".tmp"
    with open(header_tmp, "w") as header_file:
        header_file.write("""// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.\n
""")
        header_file.write("#ifndef HEARTHSTONEPP_HSPP_H\n")
        header_file.write("#define HEARTHSTONEPP_HSPP_H\n\n")
        for filename in filenames:
            line = "#include <hspp/%s>\n" % filename
            header_file.write(line)
        header_file.write("\n#endif  // HEARTHSTONEPP_HSPP_H\n")
    if not filecmp.cmp(header, header_tmp):
        shutil.move(header_tmp, header)
    else:
        os.remove(header_tmp)

if __name__ == "__main__":
    main()
