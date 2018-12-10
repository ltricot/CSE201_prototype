from xml.etree import ElementTree
from collections import deque, defaultdict
from itertools import count
import sys

import requests

# arxiv's api seems to prefix this to the tags of all its nodes
prefix = '{http://www.w3.org/2005/Atom}'
base_url = 'http://export.arxiv.org/api/query'

def authors_from_ids(id_list):
    """Yield pairs of the form (author, ID).
    Each pair is produced by searching the authors of each article associated to
    each ID in `id_list`.
    """

    # call arxiv api
    for ids in (id_list[k:k + 15] for k in range(0, len(id_list), 15)):
        response = requests.get(url=base_url, params={
            'id_list': ','.join(ids),
            'max_results': 1,
        })

        # parse xml
        root = ElementTree.fromstring(response.content)

        # iterate over all entries / ids
        for entry in root.findall(prefix + 'entry'):
            id_ = entry.find(prefix + 'id').text.rsplit('/', 1)[-1]

            # iterate over authors & yield names
            for author in entry.findall(prefix + 'author'):
                name = author.find(prefix + 'name').text
                yield name, id_

def ids_from_authors(authors, max_results=100):
    """Yield pairs of the form (author, ID).
    Each pair is produced by searching the ID of each article associated to
    each author in `authors`.
    """

    for author in authors:  # slow :(
        # call arxiv api
        response = requests.get(url=base_url, params={
            'search_query': f'au:{author}',
            'max_results': max_results,
        })

        # parse xml
        root = ElementTree.fromstring(response.content)

        # iterate over entries & yield ids
        for entry in root.findall(prefix + 'entry'):
            id_ = entry.find(prefix + 'id').text.rsplit('/', 1)[-1]  # last part of id url
            yield author, id_

def crawl(id_):
    """Crawl the arxiv author / ID graph from a source ID.
    Alternate calls to `authors_from_ids` and `ids_from_authors` and yield the
    pairs produced.
    """

    call_queue = deque([[id_]])  # for bfs
    aus = False

    for degree in count():
        print(f'\n{degree}')  # informational

        if aus:
            ids = set()
            authors = call_queue.popleft()
            for author, article in ids_from_authors(authors):
                yield author, article
                ids.add(article)
            call_queue.append(list(ids))

        else:
            authors = set()
            ids = call_queue.popleft()
            for author, article in authors_from_ids(ids):
                yield author, article
                authors.add(author)
            call_queue.append(list(authors))

        aus = not aus

# example script counting authors & papers
# crawling stops during an article search so the ID / author quotient is innaccurate
graph = defaultdict(set)
for i, (au, id_) in enumerate(crawl('1810.07586')):
    graph[au].add(id_)
    print('.', end='')
    sys.stdout.flush()

    if i > 1000:
        break

for au in graph.keys():
    print(au, graph[au])
