"""
Created on Mon Dec 17 13:44:23 2018

@author: julesbaudet
"""

import random
import time

maxArticleID = 2**32-1
# http://compoasso.free.fr/primelistweb/page/prime/liste_online_en.php
prime = 4294967311
# We generate random hash function of the form h_i(x) = (ax + b) mod(c)
#a and b are randomly generated coefficients, x is the number of the articles
#c has to be prime so that... COMPLETE

#first we create two lists of random coefficients
def RandomCoeffs(k):
    """generates a list of k different random coefficients"""
    t0 = time.time()
    coeffs = []
    while k>0:
        a = random.randint(0, maxArticleID)
        if a not in coeffs: 
            coeffs.append(a)
        k -= 1
    total_time = time.time() - t0
    print('It took {} time to create the coefficients for the hash functions \n'.format(total_time))
    return coeffs 

#we will only work on the articles that were cited by the users in our user list
def article_list(UserList):
    """ returns the list of all articles related to the users I'm considering"""
    t0 = time.time()
    articles = []
    for user in UserList:
        for article in user:
            if article not in articles:
                articles.append(article)
    total_time = time.time() - t0
    print('It took {} time to return the lists of articles considered \n'.format(total_time))
    return articles

#we now compute the signatures of all users
#we present it as a list "signature" such that signature[i] corresponds to user i's signature

def minhash(UserList, k):
    """ input a matrix with rows corresponding to the articles and column 
    corresponding to users, returns the matrix of signatures. k is the number of hash functions generated"""  
    t0 = time.time()
    
    coeff_a = RandomCoeffs(k)
    coeff_b = RandomCoeffs(k)
    all_signatures = []
    for user in UserList:
        #the signature of my user (all minhashes computed)
        user_signature = []
        for i in range(k):
            #we get the hash of each article
            #to be able to make comparisons, we initialize the variable min_Hash 
            #We give it a value that's bigger than the maximum value taken by our hash functions 
            min_hash = prime + 1
            for article in user:
                #compute the hash value
                hash_val = (coeff_a[i] * article + coeff_b[i]) % prime
                #update the value to get the minimum hash value obtained
                if hash_val < min_hash:
                    min_hash = hash_val
            user_signature.append(min_hash)
        all_signatures.append(user_signature)
    #the matrix all_signatures has rows corresponding to users and column corresponding to the hash function number
    total_time = time.time() - t0
    print(all_signatures[0:5][:50])
    print('It took {} time to create the signature matrix \n'.format(total_time))
    return all_signatures




def similarity(UserList, k):
    """returns the similarity matrix of users. We build it to be an upper triangular matrix not to waste storage or time"""
    t0 = time.time()
    
    signature_matrix = minhash(UserList, k)
    nb_usr = len(UserList)
    nb_hash = len(signature_matrix[0])
    #here we build a full matrix. Possibility: create a 1D array corresponding to a triangular matrix to optimize
    Sim_matrix = [[0 for _ in range(nb_usr)] for _ in range(nb_usr)]
    #take a user i
    for i in range(nb_usr):
        sig_i = signature_matrix[i]
        #we compare user i to all users after him (we build an upper triangular matrix: user i was already compared with users with smaller indexes)
        for j in range(i+1, nb_usr):
            sig_j = signature_matrix[j]
            
            #we now count the number of values in the signature that are equal
            count = 0
            for h in range(nb_hash):
                if sig_i[h] == sig_j[h]:
                    count += 1
            #compute the similarity percentage between user i and user j
            Sim_matrix[i][j] = count/nb_hash
    total_time = time.time() - t0
    print('It took {} time to to create the similarity matrix \n'.format(total_time))
    return Sim_matrix
        


#a little test program :)
def test_matrix(nb_usr = 500, nb_articles = 100):
    """generates a list of lists, where 1 list corresponds to a user and contains a list of articles"""
    #smallest ID of all articles
    t0 = time.time()
    min_articleID = 1000000000
    UserList = []
    for i in range(nb_usr):
        #number of articles cited by the User
        nb_cited = random.randint(1, 100)
        #list of articles cited by i
        art_i = []
        while nb_cited > 0:
            a = random.randint(min_articleID, min_articleID + nb_articles)
            if a not in art_i:
                nb_cited -= 1
                art_i.append(a)
        UserList.append(art_i)
    total_time = time.time() - t0
    print('It took {} time to to create the test matrix \n'.format(total_time))
    return UserList
        
def general_test(k):
    """tests the whole shit for k hash functions"""
    UserList = test_matrix()
    simi = similarity(UserList, k)
    print(simi[0][:100])
    print(simi[1][:100])
    print(UserList[0:3])
