//
//  main.cpp
//  Boyer_Moore
//
//  Created by maria benkhadra on 20/12/2018.
//  Copyright © 2018 maria benkhadra. All rights reserved.
//


# include <climits>
# include <cstring>
# include <cstdio>
#include  <iostream>
//function that returns each position at which the desired pattern occurs
# define NO_OF_CHARS 256

// The function for Boyer Moore's last character heuristic
void BoyerMoore(char *str, int size, int l[NO_OF_CHARS])
{
    int i;
    
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        l[i] = -1;
    
    // Fill the actual value of last occurrence of a character = last character shift
    for (i = 0; i < size; i++)
        l[(int) str[i]] = i;
}

void search(char *txt, char *pat)
{
    int n = strlen(txt);
    int m = strlen(pat);
    int l[NO_OF_CHARS];
    
    BoyerMoore(pat, m, l);
    
    int s = 0; // s is the shift of the pattern with respect to the text
    while (s <= (n - m))
    {
        int j = m - 1;
        
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        
        if (j < 0)
        {
            printf("\n pattern found at position = %d ", s);
            
            s += (s + m < n) ? m - l[txt[s + m]] : 1;
            
        }
        
        else
            s += std::max(1, j - l[txt[s + j]]);
    }
}

/* Desired test  */
int main()
{
    char txt[] = "maria yassine arXiv: xxxx.xxxxx and they fusolai arXiv: xxxx.xxrza they blablabla arXiv: xxxx.xxrzx";
    char pat[] = "arXiv: ";
    search(txt, pat);
    return 0;
} 
