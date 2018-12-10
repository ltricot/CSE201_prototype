from xml.etree import ElementTree
import sys

import requests

# arxiv's api seems to prefix this to the tags of all its nodes
prefix = '{http://www.w3.org/2005/Atom}'
base_url = 'http://export.arxiv.org/api/query'

def authors_from_id(id_):
    # call arxiv api
    response = requests.get(url=base_url, params={
        'id_list': id_,
        'max_results': 1,
    })

    # parse xml
    root = ElementTree.fromstring(response.content)
    entry = root.find(prefix + 'entry')  # there should be only one

    # iterate over authors & yield names
    for author in entry.findall(prefix + 'author'):
        name = author.find(prefix + 'name').text
        yield name

def ids_from_author(author, max_results=100):
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
        yield id_

aus = authors_from_id('0908.1736v1')
ids = ids_from_author('Mathias Drton')
print(list(aus))
print(list(ids))
