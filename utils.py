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

def _run_clean(src: str):
    def _del(fpath: str):
        os.popen(f'rm {fpath}')

    for dirpath, dirnames, filenames in os.walk(src):
        for fpath in filenames:
            if fpath == '.DS_Store':
                _del(os.path.join(dirpath, fpath))

def _run_crawl(src: str, data: str):
    sh = f'./build/src/executables/crawl {src} {data}'
    for line in os.popen(sh):
        print(line, end='')

def _run_compile(build: str):
    sh = f'cd {build} && cmake .. && make'
    for line in os.popen(sh):
        print(line, end='')


if __name__ == '__main__':
    cmds = {
        'fmt': _run_format,
        'clean': _run_clean,
        'crawl': _run_crawl,
        'compile': _run_compile,
    }

    # usage: python utils [fmt|clean|crawl] *args
    cmds[sys.argv[1]].__call__(*sys.argv[2:])
