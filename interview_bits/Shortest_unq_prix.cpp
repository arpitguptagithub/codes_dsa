#include <bits/stdc++.h>
using namespace std;

char **b;
typedef struct trie_node{
	int isChild;
	struct trie_node *child[26];//childnode pointers
	int count[26];
} *Trie;

Trie getNode(){
	Trie node = (Trie)malloc(sizeof(struct trie_node)); 
	node->isChild = 0;
	int i;
	for(i=0; i<25; i++) {
		node->child[i] = NULL; 
		node->count[i] = 0;
	}
	return node;
}

void Insert_string(Trie root,char *s){
	int i ;
	if(s == NULL) 
		return ;
	Trie t = root;
	int flag =0,flag2 =0;
	for(i=0; s[i]; i++) {
		if(t->child[s[i]-'a'] != NULL ){
		    	t->count[s[i]-'a'] = 1;
			t = t->child[s[i]-'a'];
		
		
		}	
		else{
			t = t->child[s[i]-'a'] = getNode();
		}	
	}
   
    	t->isChild = 1;
}

void display(Trie t,char *s){
	if(t->isChild == 1){
		printf("%s\n",s);
	}
	int i;
	for (i=0; i<26; i++) {
		if(t->child[i]&&t->count[i] != 0){
            s[strlen(s)] = i + 'a';
			display(t->child[i],s);
			s[strlen(s)-1] = '\0';
 		}else if(t->child[i]&&t->count[i] == 0){
 		    s[strlen(s)] = i + 'a';
 		   // printf("%s\n",s);
 		    s[strlen(s)-1] = '\0';
 		}
	}
}
void dump1( Trie t,char *A,int l, int curindex){
	int j =0;
	int i =0;
	int flag = 0;
	char s[500] = {'\0'};
	while(A[i]&&t){
		flag = 0;
		if(t->child[A[i]-'a']&&t->count[A[i]-'a'] != 0){
		  // 	printf("dadad\n");
			s[curindex++] = A[i];
		    t= t->child[A[i]-'a'];	
		}else if(t->child[A[i]-'a']&&t->count[A[i]-'a'] == 0){
		        s[curindex++] = A[i];
		    	s[curindex] = '\0';
				b[l] = (char*)malloc(sizeof(char)*(strlen(s)+1));
				strcpy(b[l],s);
				return;
		
		}
		i++;
		
	}
}


void dump( Trie t,char **A,int n){
	int i =0;
	for(i=0;i<n;i++){
		dump1(t,A[i],i,0);
	}
}

char** prefix(char** A, int n1) {
	Trie root = getNode();
	
	int i =0;
	for(i=0;i<n1;i++){
		Insert_string(root,A[i]);
	}
	char a[100] = {'\0'};
//	display(root,a);
	
	free(b);
	b = (char **)malloc(sizeof(char*)*5000);
	
	dump( root,A,n1);
	return b;
}

int main ()
{

	char *a = {"aa"};
	char **n = &a;
  cout<< prefix ( n, 1);

	return 0 ;
}