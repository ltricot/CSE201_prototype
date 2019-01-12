import sys, os


def _run_format(src: str):
    def _format(fpath: str):
        pipe = os.popen(f'clang-format --style=file {fpath}')
        output = pipe.read()

        with open(fpath, 'w') as f:
            f.write(output)

    for dirpath, dirnames, filenames in os.walk(src):
        for fpath in filenames:
            if fpath.endswith('.cpp'):
                _format(os.path.join(dirpath, fpath))


if __name__ == '__main__':
    _run_format(sys.argv[1])
