#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Dec  8 23:55:49 2018

@author: deivis
"""
-------------------------------------------------------------------------------

Data requirements (just for Linear Regression class, not for the FillMatrix): 
    
Features is a (full) matrix:
                | Math | Theoretical | Practical | Chemistry |
----------------|---------------------------------------------
Fermat thm      | 0.9
Gravity measure |
Penicilin       |            1.0
Motion          |


Ratings is a list of person's rated papers:
    
        | Fermat thm | Gravity measure | Penicilin | Motion
--------|--------------------------------------------------
Dr. John|     5             2                0         4

-------------------------------------------------------------------------------

We assume that John's rating is the result of the function of the following form:
    
Rating(paper) = a_1 * Math + a_2 * Theoretical + a_3 * Practical + b

Therefore, knowing the features of every paper John rated and the ratings he gave, 
we can deduce the weights (a_1, a_2, a_3, b) and thus predict the other ones.

-------------------------------------------------------------------------------
Example how to use the Linear Regression class:
    
    
features = [[0.7, 0.3, 0.7, 0.9],
            [0.1, 1, 0.7, 0.1],
            [1, 0.2, 0.2, 0.9],
            [0.9, 0.3, 0.1, 0.9]]

rankings = [4,0,5,5]


sample = LinearRegression(features, rankings)
sample.perform_LR()

print('weights : ' + str(sample.weights))
print('the additional coefficient b : ' + str(sample.b))

new_paper_features = [0.8,0.3,0.7,0.9]
print('the prediction of the rating of the paper with the following features : ')
print('features : ' + str(new_paper_features))
print('predicted rank : ' + str(sample.predict(new_paper_features)))
    
"""

class LinearRegression:
    def __init__(self,features,ratings,alpha = 0.001 ,max_iterations = 10000, max_error = 0.1, rating_accurary = 2):
        self.features = features
        self.ratings = ratings 
        
        self.alpha = alpha
        self.max_iterations = max_iterations
        self.max_error = max_error
        self.accuracy = rating_accurary
        
        self.num_features = len(features[0])
        self.num_papers = len(features)
        
        self.fitted = [0 for _ in range(self.num_papers)]
        self.gradient = [0 for _ in range(self.num_features)]
        self.weights = [0 for _ in range(self.num_features)]
        self.b = 0
        
    def perform_LR(self):
        if len(self.features) == len(self.ratings):
            self.optimize()
        else:
            print('sizes do not match')

        
    def dc_dw_i(self,j):
        total = 0
        for i in range(len(self.features)):
            total += 2 * (self.fitted[i] - self.ratings[i]) * self.features[i][j]
        return total
        
        
    def dc_db(self):
       total = 0
       for i in range(self.num_papers):
           total += 2 * self.num_papers * (self.fitted[i] - self.ratings[i])
       return total


    def update_gradient(self):
        for i in range(self.num_features):
            self.gradient[i] = self.dc_dw_i(i)
        self.gradient.append(self.dc_db())

    def update_weights(self):
        for i in range(self.num_features):
            self.weights[i] -= self.alpha * self.gradient[i]
        self.b -= self.alpha * self.gradient[-1]
            
    def optimize(self):
        for i in range(self.max_iterations):
            self.update_gradient()
            self.update_weights()
            self.update_fitted()
            error = self.residual_sum_of_squares()
            if error < self.max_error:
                print('the desired error was achieved after : ' + str(i) + ' steps')
                break
     
    def update_fitted(self):
        for i in range(self.num_papers):
            count = 0
            for j in range(len(self.features[0])):
                count += self.weights[j] * self.features[i][j]
            count += self.b
            self.fitted[i] = count
    
    def residual_sum_of_squares(self):
        error = 0
        for i in range(self.num_papers):
            error += (self.fitted[i] - self.ratings[i]) ** 2
        return error
    
    def predict(self,features):
        rank = 0
        for i in range(len(features)):
            rank += features[i] * self.weights[i]
        rank += self.b
        return round(rank, self.accuracy)
  
    
"""   
-------------------------------------------------------------------------------

Data requirements: 
    
Features is a (full) matrix:
                | Math | Theoretical | Practical | Chemistry |
----------------|---------------------------------------------
Fermat thm      | 0.9
Gravity measure |
Penicilin       |            1.0
Motion          |


Ratings is a list of person's rated papers:
    
        | Fermat thm | Gravity measure | Penicilin | Motion
--------|--------------------------------------------------
Dr. John|   None            1                1         1
Dr. Tom |     4             2                0         4
Dr. Kim |     5           None             None        1
Dr. Nick|     0             0              None        4
Dr. Jake|     1             5                0       None

-------------------------------------------------------------------------------
Example how to use the Fill Matrix class:
    
    
features = [[0.7, 0.3, 0.7, 0.9],
            [0.1, 1, 0.7, 0.1],
            [1, 0.2, 0.2, 0.9],
            [0.9, 0.3, 0.1, 0.9]]

rankings = [[4,0,5,5],
            [None,5,1,1],
            [4,1,None,0],
            [4,0,None,5],
            [None,5,5,0]]

sample = FillMatrix(rankings, features)
sample.fill()
"""


class FillMatrix:
    def __init__(self,matrix,features):
        self.matrix = matrix
        self.features = features
        
        self.is_relevant = []
        self.n = len(matrix)
        self.m = len(matrix[0])
        
        self.weights = []
        self.b = 0
        
    def fill(self):
        for i in range(self.n):
            relevant_ratings = self.get_rated_papers(i)
            #if all the ratings are known
            if sum(self.is_relevant) == self.m:
                continue
            relevant_features = self.get_relevant_features()
            new_person = LinearRegression(relevant_features,relevant_ratings)
            new_person.perform_LR()
            self.fill_ranks(i, new_person)
        self.print_nicely()
            
    def get_rated_papers(self,i):
        rated_papers = []
        self.is_relevant = [False for _ in range(self.m)]
        for j in range(self.m):
            if self.matrix[i][j] != None:
                rated_papers.append(self.matrix[i][j])
                self.is_relevant[j] = True
        return rated_papers
    
    def get_relevant_features(self):
        relevant_features = []
        for i in range(self.m):
            if self.is_relevant[i]:
                relevant_features.append(self.features[i])
        return relevant_features
            
    def fill_ranks(self, index, person):
        for i in range(self.m):
            if not self.is_relevant[i]:
                predicted_rating = person.predict(self.features[i])
                self.matrix[index][i] = predicted_rating
                
    def print_nicely(self):
        print('-' * self.n * 3)
        for i in range(self.n):
            print(self.matrix[i])
