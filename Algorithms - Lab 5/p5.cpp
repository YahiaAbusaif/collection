//hadn't time for implement the solution
// first you need to find the longest common subsequence (LCS) between the 2 string S1 and S2
//then for each letter in string S1 if it's mention in LCS don't put it else put it in the correct place 
//ex answer=LCS= BDEF and s1=ABCDEFFG ,A didn't mention so add  it to answer=ABDEF B mention so ignore it ,C didn't mention so add it after B answer=ABCDEF , DEF already mention skip them 
//FG didn't so add it to answer
//after finish S1 repeat on S2
//now answer contain  shortest string that has both str1and str2 as subsequences
//complixty: |S1|.|S2| +|S1|+|S2| where |S1| is the length of S1