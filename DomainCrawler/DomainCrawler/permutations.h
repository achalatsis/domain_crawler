//
//  permutations.h
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 28/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#ifndef DomainCrawler_permutations_h
#define DomainCrawler_permutations_h

/**
 * The alphabet for creating the permutations.
 * Valid are considered all permutations of 1+ of the symbols bellow.
 * Repetitions are allowed.
 */
static const char base37[37];

/**
 * Given a string, advances the string lexicographically by one.
 @param string The string to advance
 @param digit The digit of the string you want advanced. Normally this should be pointing at the last digit.
 @return Returns a new string advanced by one from the input. You cannot rely on this string, it will be freed sometime in the future. You have to copy it if you want to keep it.
 */
char* incrementString(char *string, char *digit);

#endif
