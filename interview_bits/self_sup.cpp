char ** b;
struct node{
    int isChild ;
    node *child[26] ;
    count[26];
};

node getNode()
{
    node Node = (node)malloc(sizeof(struct node));
    Node->isChild =0;
    int i =0;
    for ( ; i<25; i++)
    {
        Node->child[i] = NULL;
        Node->count[i]=0;
    }
    return Node;
}

void Insert_string( node root, char *s)
{
    int i =0;
    if (s == NULL)
     return;
    node t = root;
    int f =0 , f1 =0;
    for (; s[i] ; i++){
      if(t->child[s[i]-'a'] != NULL){
         t->count[s[i]- 'a'] =1;
         t= t->child[s[i]-'a'];
      }
      else{
        t= t->child[s[i]-'a'] = getNode();
      }
    }
    t->isChild =1;
}

void display( node t ,char *s)
{
    if ( t->isChild ==1)
    {
        printf("%s\n",s);
    }
    int i ;
    for ( i =0; i <26 ; i++){
        if ( t->child[i] && t->count[i] != 0)
         {
            s[strlen(s)] = i+'a';

        	display(t->child[i],s);
			s[strlen(s)-1] = '\0';

 		}else if(t->child[i]&&t->count[i] == 0){
 		    s[strlen(s)] = i + 'a';
 		   // printf("%s\n",s);
 		    s[strlen(s)-1] = '\0';
 		}
    }


void dump( node t, char **A , int n )
}