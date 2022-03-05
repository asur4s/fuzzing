#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>


int main(int argc, char **argv){
    // 因为总是要在 xmlChar* 和char*之间进行类型转换，所以定义了一个宏 BAD_CAST
    // #define BAD_CAST (xmlChar *)
    xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
    xmlNodePtr rootNode = xmlNewNode(NULL, BAD_CAST"root");
    printf("success\n");
    xmlFreeDoc(doc);
    return 0;
}

