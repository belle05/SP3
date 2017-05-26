#ifndef SPFIARPARSER_H_
#define SPFIARPARSER_H_
#include <stdbool.h>

bool spParserIsInt(const char* str){
	long num=0;
	for(unsigned int i=0; i<sizeof(str); i++){
		if(isdigit(str[i])){
			num+=10*num+(long)str[i];
			if (num>=4294967295) {
				return false;
			}
		} else {
			return false;
		}
	}
	return true;
}


