#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct TokenizerT_ {
	char* str;
		//is the string argument that is being tokenized
	int cur_index;
		//is the index used to traverse string argument
	char* cur_type;
		//is the current type of token being detected
};


typedef struct TokenizerT_ TokenizerT;

/*******************
 * creates tmp pointer to store string argument and then returns the pointer back to main
 ******************/

TokenizerT *TKCreate( char * ts ) {
	
	TokenizerT *tmp = (TokenizerT*)malloc(sizeof(TokenizerT));
	tmp->str = (char*)malloc(strlen(ts)*sizeof(char));
	strcpy(tmp->str,ts);

	return tmp;
}

/*******************
 * TKDestroy frees up space allocated to TokenizerT *tk 
 ******************/


void TKDestroy( TokenizerT * tk ) {
	free(tk);

}

/*******************
 * punctDetect is called by checkFirstType so detect what kind of symbol is being read,
 * the symbol type is being returned and the symbol name is being printed out to screen.
 ******************/

char* punctDetect(char c, TokenizerT *tktmp, int* pncptr){
	if(c == '.'){
		printf("period");
		return "period";
	}
	if(c == '('){
		printf("left parenthesis ");
		return "left parenthesis";
	}
	if(c == ')'){
		printf("right parenthesis ");
		return "right parenthesis";
	}
	if(c == '{'){
		printf("left bracket ");
		return "left bracket";
	}
	if(c == '}'){
		printf("right bracket ");
		return "right bracket";
	}
	if(c == '['){
		printf("left brace ");
		return "left brace";
	}
	if(c == ']'){
		printf("right brace ");
		return "right brace";
	}
	if(c == ';'){
		printf("semi-colon ");
		return "semi-colon";
	}
	if(c == '%'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("modulus/equals ");
			return "modulus/equals";
		}
		printf("modulus ");
		return "modulus";
	}


	if(c == '='){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("equality ");
			return "equality";
		}
		printf("equal sign ");
		return "equal sign";

	}

	if(c == '*'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("multiply/equals ");
			return "multiply/equals";
		}
		printf("multiplication sign ");
		return "multiplication sign";
	}
	if(c == '/'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("division/equals ");
			return "division/equals";
		}
		printf("division sign ");
		return "division sign";
	}
	if(c == '-'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("subtraction/equals ");
			return "subtraction/equals";
		}
		if(tktmp->str[tktmp->cur_index +1] == '-'){
			*pncptr = 1;
			printf("decrease ");
			return "decrease";
		}
		printf("subtraction sign ");
		return "subtraction sign";
	}
	if(c == '+'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("addition/equals ");
			return "addition/equals";
		}
		if(tktmp->str[tktmp->cur_index +1] == '+'){
			*pncptr = 1;
			printf("increase ");
			return "increase";
		}
		printf("addition sign ");
		return "addition sign";
	}
	if(c == '<'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("less than/equals ");
			return "less than/equals";
		}else if(tktmp->str[tktmp->cur_index +1] == '<'){
			*pncptr = 1;
			return "shift left";
		}
		printf("less than sign ");
		return "less than sign";
	}
	if(c == '>'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("greater than/equals ");
			return "greater than/equals";
		}else if(tktmp->str[tktmp->cur_index +1] == '>'){
			*pncptr = 1;
			return "shift right";
		}
		printf("greater than sign ");
		return "greater than sign";
	}
	if(c == '!'){
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("not equal to ");
			return "not equal to";
		}
		printf("negation ");
		return "negation";
	}
	if(c == '&'){
		if(tktmp->str[tktmp->cur_index +1] == '&'){
			*pncptr = 1;
			printf("logical and ");
			return "logical and";
		}
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("bitwise and/equal ");
			return "and";
		}
		printf("bitwise and ");
		return("bitwise and");
	}
	if(c == '^'){
		printf("bitwise exclusive or ");
		return("bitwise exclusive or ");
	}
	if(c == '|'){
		if(tktmp->str[tktmp->cur_index +1] == '|'){
			*pncptr = 1;
			printf("logical or ");
			return "logical or";
		}
		if(tktmp->str[tktmp->cur_index +1] == '='){
			*pncptr = 1;
			printf("bitwise or/ equals ");
			return "logical or";
		}

		printf("bitwise or ");
		return("bitwise or ");
	}
	if(c ==','){
		printf("comma ");
		return("comma");
	}
	if(c== '~'){
		printf("1's comp ");
		return "comp";
	}
	if(c == '"'){
		printf("double quote ");
		return "double quote";	
	}
	if(c == '\''){
		printf("single quote ");
		return "single quote";
	}
	if(c == '\\'){
		printf("backslash ");
		return("backslash");
	}


/*******************
 * if read symbol is not found here then it is unrecognized and therefore invalid. Malformed punctuation is printed out onto screen. 
 ******************/

	printf("unrecognized/malformed punctuation");
	return "unspecified";
}

/*******************
 * checkFirstType is called inside TKGetNextToken to detect what kind of character is first of each token.
 * three choices consisting of "alpha"/"integer"/"punct", if "punct" is detected then it called punctDetect
 ******************/

char *checkFirstType(char c, TokenizerT * tktmp, int* puncptr){

	if(isalpha(c)){
		return "alpha";
	}else if(isdigit(c)){
		return "integer";
	}else if(ispunct(c)){
		return punctDetect(c, tktmp,puncptr);
	}


	return NULL;

}

/*****************************************************************************
 * checkTypeOctal,checkTypeAlnum, checkTypeInt, checkTypeFloat, checkTypeHex are all used within TKGetNextToken to detect whether the current character meets the 
 * requirement to be appended to the current token being examined
 ****************************************************************************/


char* checkTypeOctal(char c){
	if(('0'<=c) && (c<='7')){
		return "octal";
	}
	return NULL;
}

char* checkTypealnum(char c){
	if(isalnum(c)){
		return "alnum";
	}

	return NULL;	
}
char* checkTypeInt(char c){
	if(isdigit(c)){
		return "integer";
	}
	return NULL;

}

char* checkTypeFloat(char c){
	if(('0' <= c )&&(c <= '9')){
		return "float";
	}
	if((c == 'e') || (c == 'E')){
		return "float";
	}
	return NULL;
}

char* checkTypeHex(char c){

	if(('0'<=c) && (c<='9')){
		return "hex";

	}
	if(('a'<=c)&&(c<='f')){
		return "hex";
	}

	if(('A' <= c)&&(c <= 'F')){
		return "hex";
	}


	return NULL;

}

/*******************
 * TKGetNextToken is used to retreive the next token from the string argument.
 * TKGetNextToken is separated into 5 sections: whitespace check, check first type, alpha check, integer check, and shiftleft/shiftright check.
 * More about how TKGetNextToken can be read in the readme that is included
 ******************/

char *TKGetNextToken( TokenizerT * tk ) {
	char* ret = (char*)malloc(2*sizeof(char));
	int i = 1;
	char* first = 0;
	char* prevtype = first;
	char* type = 0;
	int checkE = 0;
	int secondPunct = 0;
	int *secPuncPtr = &secondPunct;

	if(tk->str[tk->cur_index] == ' ' || tk->str[tk->cur_index]== '\n' || tk->str[tk->cur_index]== '\r'|| tk->str[tk->cur_index]== '\t'|| tk->str[tk->cur_index]== '\v'){
		tk->cur_index++;
		tk->cur_type = "whitespace";
		return NULL;
	}


	if(prevtype == first){
		type = checkFirstType(tk->str[tk->cur_index], tk, secPuncPtr);
		ret[0] = tk->str[tk->cur_index];
		tk->cur_index++;
		prevtype = type;
		if(secondPunct == 1){
			secondPunct = 0;
			ret[i] = tk->str[tk->cur_index];
			tk->cur_index++;
			i++;
		}


	}
	if(prevtype == "alpha"){
		tk->cur_type = "word";

		while(tk->cur_index < strlen(tk->str)){
			type = checkTypealnum(tk->str[tk->cur_index]);
			if(type=="alnum"){
				ret = (char*)realloc(ret,sizeof(ret)+(2*sizeof(char)));
				ret[i] = tk->str[tk->cur_index];
				tk->cur_index++;
				i++;
			}else{
				return ret;
			}
		}
		return ret;

	}
	if(prevtype =="integer"){
		if(ret[0]=='0'){
			if((tk->str[tk->cur_index] == 'x') || (tk->str[tk->cur_index] == 'X')){
				tk->cur_type = "hex";
				ret = (char*)realloc(ret,sizeof(ret)+1);
				ret[i] = tk->str[tk->cur_index];
				tk->cur_index++;
				i++;
				while(tk->cur_index < strlen(tk->str)){
					type = checkTypeHex(tk->str[tk->cur_index]);
					if(type == "hex"){
						ret = (char*)realloc(ret,sizeof(ret)+1);
						ret[i] = tk->str[tk->cur_index];
						tk->cur_index++;
						i++;
					}else{
						return ret;
					}

				}	
			}else if( '0' <= tk->str[tk->cur_index] && tk->str[tk->cur_index]<='7' ){
				tk->cur_type = "octal";
				while(tk->cur_index < strlen(tk->str)){
					type = checkTypeOctal(tk->str[tk->cur_index]);
					if(type == "octal"){
						ret = (char*)realloc(ret,sizeof(ret)+1);
						ret[i] = tk->str[tk->cur_index];
						tk->cur_index++;
						i++;
					}else{
						return ret;
					}	
				}		
			}else if((tk->str[tk->cur_index] == '.')) {
				if((tk->str[tk->cur_index +1] >= '0') && (tk->str[tk->cur_index + 1] <= '9')){
					ret = (char*)realloc(ret,sizeof(ret)+1);
					ret[i] = tk->str[tk->cur_index];
					tk->cur_index++;
					i++;
					ret = (char*)realloc(ret,sizeof(ret)+1);
					ret[i] = tk->str[tk->cur_index];
					tk->cur_index++;
					i++;

					tk->cur_type = "float";
					while(tk->cur_index < strlen(tk->str)){
						type = checkTypeFloat(tk->str[tk->cur_index]);
						if(type== "float"){
							if((tk->str[tk->cur_index] == 'e') && (checkE != 0)){
								return ret;
							}
							if((tk->str[tk->cur_index] == 'e') && checkE ==0){
								checkE =1;
								if(  (tk->str[tk->cur_index + 1]!= '+')&& (tk->str[tk->cur_index + 1]!= '-') ){
									return ret;
								}else if( (tk->str[tk->cur_index + 2] > '9') || (tk->str[tk->cur_index + 2]< '0')){
									return ret;
								}
								ret = (char*)realloc(ret,sizeof(ret)+1);
								ret[i] = tk->str[tk->cur_index];
								tk->cur_index++;
								i++;
								ret = (char*)realloc(ret,sizeof(ret)+1);
								ret[i] = tk->str[tk->cur_index];
								tk->cur_index++;
								i++;
								ret = (char*)realloc(ret,sizeof(ret)+1);
								ret[i] = tk->str[tk->cur_index];
								tk->cur_index++;
								i++;
								continue;
							}
							ret = (char*)realloc(ret,sizeof(ret)+1);
							ret[i] = tk->str[tk->cur_index];
							tk->cur_index++;
							i++;			
						}else{
							return ret;
						}
					}
					return ret;


				}
			}else if((tk->str[tk->cur_index] >= '8') || (tk->str[tk->cur_index] <= '0') ){
				tk->cur_type = "zero";
				return ret;
			}else{
				tk->cur_type = "integer"; 
				while(tk->cur_index < strlen(tk->str)){
					type = checkTypeInt(tk->str[tk->cur_index]);
					if(type=="integer"){
						printf("you made it here\n");
						ret = (char*)realloc(ret,sizeof(ret)+1);
						ret[i] = tk->str[tk->cur_index];
						tk->cur_index++;
						i++;
					}else{
						return ret;
					}
				}	
			}
		}

		while(tk->cur_index < strlen(tk->str)){
			tk->cur_type = "integer";
			type = checkTypeInt(tk->str[tk->cur_index]);
			if(type == "integer"){
				ret = (char*)realloc(ret,sizeof(ret)+1);
				ret[i] = tk->str[tk->cur_index];
				tk->cur_index++;
				i++;
				continue;
			}else if(tk->str[tk->cur_index] == '.'){

				if((tk->str[tk->cur_index] == '.')) {
					if((tk->str[tk->cur_index +1] >= '0') && (tk->str[tk->cur_index + 1] <= '9')){
						ret = (char*)realloc(ret,sizeof(ret)+1);
						ret[i] = tk->str[tk->cur_index];
						tk->cur_index++;
						i++;
						ret = (char*)realloc(ret,sizeof(ret)+1);
						ret[i] = tk->str[tk->cur_index];
						tk->cur_index++;
						i++;

						tk->cur_type = "float";
						while(tk->cur_index < strlen(tk->str)){
							type = checkTypeFloat(tk->str[tk->cur_index]);
							if(type=="float"){
								if((tk->str[tk->cur_index] == 'e' || tk->str[tk->cur_index] == 'E' ) && (checkE != 0)){
									return ret;
								}
								if((tk->str[tk->cur_index] == 'e' || tk->str[tk->cur_index] == 'E' ) && checkE ==0){
									checkE =1;
									if(  (tk->str[tk->cur_index + 1]!= '+')&& (tk->str[tk->cur_index + 1]!= '-') ){
										return ret;
									}else if( (tk->str[tk->cur_index + 2] > '9') || (tk->str[tk->cur_index + 2]< '0')){
										return ret;
									}
									ret = (char*)realloc(ret,sizeof(ret)+1);
									ret[i] = tk->str[tk->cur_index];
									tk->cur_index++;
									i++;
									ret = (char*)realloc(ret,sizeof(ret)+1);
									ret[i] = tk->str[tk->cur_index];
									tk->cur_index++;
									i++;
									ret = (char*)realloc(ret,sizeof(ret)+1);
									ret[i] = tk->str[tk->cur_index];
									tk->cur_index++;
									i++;
									continue;
								} 
								ret = (char*)realloc(ret,sizeof(ret)+1);
								ret[i] = tk->str[tk->cur_index];
								tk->cur_index++;
								i++;
							}else{
								return ret;
							}
						}
						return ret;
					}
				}
				return ret;
			}else if(tk->str[tk->cur_index] == 'e' || tk->str[tk->cur_index] == 'E'){
				while(tk->cur_index < strlen(tk->str)){
					type = checkTypeFloat(tk->str[tk->cur_index]);
					if(type=="float"){
						if((tk->str[tk->cur_index] == 'e' || tk->str[tk->cur_index] == 'E' ) && (checkE != 0)){
							return ret;
						}
						if((tk->str[tk->cur_index] == 'e' || tk->str[tk->cur_index] == 'E' ) && checkE ==0){
							checkE =1;
							if(  (tk->str[tk->cur_index + 1]!= '+')&& (tk->str[tk->cur_index + 1]!= '-') ){
								return ret;
							}else if( (tk->str[tk->cur_index + 2] > '9') || (tk->str[tk->cur_index + 2]< '0')){
								return ret;
							}
							ret = (char*)realloc(ret,sizeof(ret)+1);
							ret[i] = tk->str[tk->cur_index];
							tk->cur_index++;
							i++;
							ret = (char*)realloc(ret,sizeof(ret)+1);
							ret[i] = tk->str[tk->cur_index];
							tk->cur_index++;
							i++;
							ret = (char*)realloc(ret,sizeof(ret)+1);
							ret[i] = tk->str[tk->cur_index];
							tk->cur_index++;
							i++;
							tk->cur_type = "float";
							continue;
						}
						ret = (char*)realloc(ret,sizeof(ret)+1);
						ret[i] = tk->str[tk->cur_index];
						tk->cur_index++;
						i++;
					}else{
						return ret;
					}
				}

				return ret;	
			}
			return ret;
		}
		tk->cur_type = prevtype; 
		return ret;
	}
	if(prevtype== "shift left" ){
		if(tk->str[tk->cur_index] == '='){
			ret = (char*)realloc(ret,sizeof(ret)+1);
			ret[i] = tk->str[tk->cur_index];
			tk->cur_index++;
			i++;
			printf("shiftleft/equals ");
		}else{
			printf("shift left ");
		}


	}else if(prevtype=="shift right"){
		if(tk->str[tk->cur_index] == '='){
			ret = (char*)realloc(ret,sizeof(ret)+1);
			ret[i] = tk->str[tk->cur_index];
			tk->cur_index++;
			i++;
			printf("shiftright/equals ");
		}else{
			printf("shift left ");
		}

	}

	tk->cur_type = prevtype; 
	return ret;
}


int main(int argc, char **argv) {
	//checks to make sure there is the right amount of arguments being inputed into the program. there has to be atleast 1 and no more than 1 input or else 
	//an error message is displayed
	if(argc < 2){
		fprintf(stderr,"not enough arguements \n");
		exit(1);
	}else if(argc > 2){
		fprintf(stderr,"too many arguements \n");
		exit(1);

	}
	

	//a TokenizerT type pointer is created and named t1, it is allocated enough size to store its data
	//then the string located in argv[1] is passed through TKCreate and then t1 points to the resulting pointer created by TKCreate
	TokenizerT *t1 = (TokenizerT*)malloc(sizeof(TokenizerT));
	t1 = TKCreate(argv[1]);

	t1->cur_index = 0;
	char* token = (char*)malloc((strlen(t1->str)+1)*sizeof(char));


	//while current index is less than the length of the string argument, we will traverse the string and obtain all of the possible defined tokens
	while(t1->cur_index < strlen(t1->str)){

		token = TKGetNextToken(t1);

		if(strcmp(t1->cur_type,"word")==0){
			printf("word ");
		}else if(strcmp(t1->cur_type,"integer") ==0){
			printf("decimal integer constant ");
		}else if(strcmp(t1->cur_type ,"octal")==0){
			printf("octal constant ");
		}else if(strcmp(t1->cur_type,"hex") ==0){
			printf("hexadecimal constant ");
		}else if(strcmp(t1->cur_type,"float")==0){
			printf("float ");
		}else if(strcmp(t1->cur_type, "whitespace")==0){
			continue;
		}else if(strcmp(t1->cur_type,"zero")==0){
			printf("zero ");
		}

		printf("\"%s\" \n",token);

		//frees the memory allocated to the token
		free(token);
		
	}
	//frees the memory allocated to the string argument inside t1
	free(t1->str);
	
	//called TKDestroy which will free the memory allocated to t1
	TKDestroy(t1);


	return 0;
}
