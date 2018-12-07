#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

/*
Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16 
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4 
Explanation: The two words can be "ab", "cd".
Example 3:

Input: ["a","aa","aaa","aaaa"]
Output: 0 
Explanation: No such pair of words.
*/

// n columns * n rows triangular matrix
class TriangularMatrix
{
public:
   TriangularMatrix( int n )
   {
      this->n = n;
      this->buffer = NULL;

      if ( n > 0 ) {
         int number_of_slots = (1 + n) * n / 2;

         this->buffer = (int *)malloc(sizeof(int) * number_of_slots);

         for ( int i = 0; i < number_of_slots; i++ ) {
            this->buffer[i] = -1;
         }
      }
   }

   ~TriangularMatrix()
   {
      if ( this->buffer )
         free( this->buffer );
   }

   // i is row, j is col, i >= col
   void put_value( int i, int j, int val ) {
      if ( i < j ) {
         return put_value(j, i, val);
      }

      this->buffer[(1 + i) * i / 2 + j] = val;
   }

   int get_value( int i, int j ) {
      if ( i < j ) {
         return get_value(j, i);
      }

      return this->buffer[(1 + i) * i / 2 + j];
   }

private:
   int n;
   int * buffer;
};

class Solution
{
public:
   static int isIntersectString(std::string & a, std::string & b)
   {
      for ( int i = 0; i < a.size(); i++ )
      {
         for ( int j = 0; j < b.size(); j++ )
         {
            if ( a[i] == b[j] )
               return 1;
         }
      }

      return 0;
   }

   static void calculateIntersect(std::vector<std::string> & words, TriangularMatrix & intersectMatrix)
   {
      for ( int i = 0; i < words.size(); i++ )
      {
         for ( int j = 0; j < words.size(); j++ )
         {
            if ( i < j )
               continue;

            intersectMatrix.put_value(i, j, isIntersectString( words[i], words[j] ));
         }
      }
   }

   static void calculateProduct(std::vector<std::string> & words, TriangularMatrix & productMatrix)
   {
      for ( int i = 0; i < words.size(); i++ )
      {
         for ( int j = 0; j < words.size(); j++ )
         {
            if ( i < j )
               continue;

            productMatrix.put_value( i, j, words[i].size() * words[j].size() );
         }
      }
   }

   static int maxProduct(std::vector<std::string> & words)
   {
      int maximum = 0;

      TriangularMatrix intersectMatrix(words.size());
      TriangularMatrix productMatrix(words.size());

      calculateIntersect(words, intersectMatrix);
      calculateProduct(words, productMatrix);

      for ( int i = 0; i < words.size(); i++ )
      {
         for ( int j = 0; j < words.size(); j++ )
         {
            if ( i < j )
               continue;

            if ( intersectMatrix.get_value(i, j) == 1 )
            {
               printf( "words[%d] = %s intersect words[%d] = %s\n", i, words[i].c_str(), j, words[j].c_str() );
               continue;
            }

            if ( maximum < productMatrix.get_value(i, j) )
               maximum = productMatrix.get_value(i, j);
         }
      }

      return maximum;
   }
};

int main()
{
   std::vector<std::string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
   int expected = 16;
   int output = Solution::maxProduct(words);

   if ( expected != output ) {
      printf( "error result %d, expected %d\n", output, expected );
   } else {
      printf( "correct, result %d\n", output );
   }

   return 0;
}
