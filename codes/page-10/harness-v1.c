#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include<unistd.h>

#define SIZE 50

int main(int argc, char **argv){
    // 因为总是要在 xmlChar* 和char*之间进行类型转换，所以定义了一个宏 BAD_CAST
    // #define BAD_CAST (xmlChar *)
    
    char input[SIZE] = {0};
    read(STDIN_FILENO, input, SIZE);

    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
    xmlNodePtr rootNode = xmlNewNode(NULL, BAD_CAST input);
    xmlFreeDoc(doc);
    
    return 0;
}