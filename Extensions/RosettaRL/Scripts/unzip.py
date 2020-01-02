import sys
import zipfile

def main(argv):
    input_ = argv[1]
    output = argv[2]

    with zipfile.ZipFile(input_) as f:
        f.extractall(output)

    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv))
