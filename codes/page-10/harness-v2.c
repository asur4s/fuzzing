// harness-v2.c
#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include<unistd.h>

int main(int argc, char **argv){
    // 因为总是要在 xmlChar* 和char*之间进行类型转换，所以定义了一个宏 BAD_CAST
    // #define BAD_CAST (xmlChar *)

    xmlDocPtr doc = xmlReadFile(argv[1], NULL, 0);
    if(doc != NULL){
        xmlFreeDoc(doc);
    }
    
    return 0;
}