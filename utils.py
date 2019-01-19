import sys, os, shutil, signal
import json

import arxiv


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

def _run_compile(debug=""):
    if not os.path.exists('build'):
        os.mkdir('build')

    sh = f'cd build && cmake {"-DCMAKE_BUILD_TYPE=Debug" if debug else ""} .. && make'
    for line in os.popen(sh):
        print(line, end='')

def _run_get_sources(topicp, out, many="10"):
    many = int(many)
    with open(topicp) as f:
        topics = json.load(f)

    toparts = {t: [] for t in topics}
    for topic in topics:
        res = arxiv.query(search_query=topic)
        for p in res[:many]:
            toparts[topic].append(p['id'].split('/')[-1])
    
    with open(out, 'w') as f:
        json.dump(toparts, f)

def _run_estimate(cdata):
    tot = 0
    for dirpath, dirnames, filenames in os.walk(cdata):
        for fname in filenames:
            p = os.path.join(dirpath, fname)
            with open(p) as f:
                tot += len(f.read()) - 1
    print(f'{tot} edges found')

def _run_crawl(cdata: str, refdata, sdata, source):
    sh = f'./build/src/executables/crawl {cdata} {refdata} {sdata} {source}'
    for line in os.popen(sh):
        print(line, end='')

def _run_minhash(cdata, mdata, threshold):
    sh = f'./build/src/executables/minhash {cdata} {mdata} {threshold}'
    for line in os.popen(sh):
        print(line, end='')

def _run_tfidf(sdata, tfidfdata):
    sh = f'./build/src/executables/tfidf {sdata} {tfidfdata}'
    for line in os.popen(sh):
        print(line, end='')

def _run_clustering(mdata, clusterdata):
    sh = f'./build/src/executables/cluster {mdata} {clusterdata}'
    for line in os.popen(sh):
        print(line, end='')

def _run_mf(cdata, vdata, alpha, beta):
    sh = f'./build/src/executables/runmf {cdata} {vdata} {alpha} {beta}'
    for line in os.popen(sh):
        print(line, end='')

def _run_serve(cdata, vdata, clusterdata, keys, k="30"):
    sh = f'./build/src/server/serve {cdata} {vdata} {clusterdata} {keys} {k}'
    for line in os.popen(sh):
        orint(line, end='')

def _run_references_all(data, archives, statep=""):
    archs = []
    with open(archives) as f:
        for line in f:
            paper = line.split('/')[-1].rstrip('\n')
            if not paper.endswith('tar'):
                continue
            
            archs.append(paper)
    
    getyear = lambda a: int(a[-12:-8])  # sort by year
    archs = sorted(archs, key=getyear)
    archs = [p for p in archs if getyear(p) in range(1000, 2000)]

    if os.path.exists(statep):
        with open(statep) as f:
            state = json.load(f)
    else:
        state = {
            'paper_errs': [],
            'temp_err': None,  # != None means error deleting
            'last': None,
        }

    def _sig_handler(sig, frame):
        print(json.dumps(state))
    signal.signal(signal.SIGINT, _sig_handler);

    fm = archs.index(state['last']) if state['last'] is not None else -2
    for paper in reversed(archs[:fm + 1]):
        print(f'at archive {paper}')
        sh = f'./build/src/executables/download_references {paper} {data}'
        for out in os.popen(sh):
            print(out, end='')

            if 'what()' in out:
                state['paper_errs'].append(paper)

        os.remove(paper)
        shutil.rmtree('temp', onerror=lambda _, path, __: state.__setitem__('temp', paper))
        os.mkdir('temp')

        with open(statep, 'w') as f:
            json.dump(state, f)
        print(state)

    os.rmdir('temp')


if __name__ == '__main__':
    cmds = {
        'fmt': _run_format,
        'clean': _run_clean,
        'compile': _run_compile,
        'estimate': _run_estimate,
        'sources': _run_get_sources,
        'crawl': _run_crawl,
        'ref_all': _run_references_all,
        'minhash': _run_minhash,
        'tfidf': _run_tfidf,
        'cluster': _run_clustering,
        'runmf': _run_mf,
        'serve': _run_serve,
    }

    cmds[sys.argv[1]].__call__(*sys.argv[2:])
