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

def _run_crawl(cdata: str, refdata, source):
    sh = f'./build/src/executables/crawl {cdata} {refdata} {source}'
    for line in os.popen(sh):
        print(line, end='')

def _run_compile(build: str, debug=""):
    sh = f'cd {build} && cmake {"-DCMAKE_BUILD_TYPE=Debug" if debug else ""} .. && make'
    for line in os.popen(sh):
        print(line, end='')

def _run_download_references(paper, data):
    sh = f'./build/src/executables/download_references {paper} {data}'
    for line in os.popen(sh):
        print(line, end='')

def _run_references_all(data, archives, fm="10", to="19"):
    archs = []
    with open(archives) as f:
        for line in f:
            paper = line.split('/')[-1].rstrip('\n')
            if not paper.endswith('tar'):
                continue
            
            archs.append(paper)
    
    getyear = lambda a: int(a[-12:-10])
    archs = [a for a in archs if getyear(a) in range(int(fm), int(to))]
    archs = sorted(archs, key=getyear)
    print(archs)
    exit()

    for paper in archs:
        sh = f'./build/src/executables/download_references {paper} {data}'
        for out in os.popen(sh):
            print(out, end='')


if __name__ == '__main__':
    cmds = {
        'fmt': _run_format,
        'clean': _run_clean,
        'crawl': _run_crawl,
        'references': _run_download_references,
        'compile': _run_compile,
        'ref_all': _run_references_all,
    }

    # usage: python utils [fmt|clean|crawl] *args
    cmds[sys.argv[1]].__call__(*sys.argv[2:])
