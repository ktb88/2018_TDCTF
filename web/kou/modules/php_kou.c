#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_kou.h"
#include <string.h>

static zend_function_entry tf_functions[] = {
    PHP_FE(login, NULL)
    PHP_FE(loadFile, NULL)
    {NULL, NULL, NULL}
};
 
zend_module_entry kou_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_KOU_EXTNAME,
    tf_functions,
    PHP_MINIT(kou),
    NULL, 
    NULL,
    NULL,
    PHP_MINFO(kou),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_KOU_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
 
ZEND_GET_MODULE(kou)

unsigned int loginchk(char *id,char *pw){
    if(strncmp(id,"kou",32)==0 && strncmp(pw,"1e0c6abede7ff7184c3cefe606f9760a",32)==0){
        return 1;
    }
    return 0;
}

PHP_FUNCTION(login)
{   
    char *id;
    char *pw;
    size_t id_len;
    size_t pw_len;

    char _id[33];
    char _pw[32];

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &id, &id_len, &pw, &pw_len) == FAILURE) {
        php_printf("no parameter given");
        RETURN_NULL();
    }
    
    strcpy(_id,id);
    strcpy(_pw,pw);
    
    if(!loginchk(_id,_pw)) RETURN_FALSE;
    
    RETURN_TRUE;
}

PHP_FUNCTION(loadFile)
{
    char *name;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name,&len) == FAILURE) {
        php_printf("no parameter given");
        RETURN_NULL();
    }
    FILE *fp;
    char buf[1024];
    char filename[1024];
    memset(&filename, 0, sizeof(filename));
	memset(&buf, 0, sizeof(buf));
    strcat(filename,"board/");
    strcat(filename,name);
    fp = fopen(filename,"r");
    if(fp){
        while(!feof(fp)){
            fread(buf, sizeof(char),sizeof(buf), fp);
            php_printf("%s",buf);
        }
        fclose(fp);
        RETURN_TRUE;
    }
    RETURN_FALSE;
}

static PHP_MINFO_FUNCTION(kou)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "Kou Support", "enabled");
    php_info_print_table_row(2, "Kou Module Version", PHP_KOU_VERSION);
    php_info_print_table_end();
 
    php_info_print_table_start();
    php_info_print_table_header(3, "Version Info", "Compiled", "Linked");
    php_info_print_table_row(3, "Kou Library", PHP_KOU_VERSION_STRING, "0.1");
    php_info_print_table_end();
 
    DISPLAY_INI_ENTRIES();
}
 
static PHP_MINIT_FUNCTION(kou)
{
    REGISTER_NS_STRING_CONSTANT("Kou", "VERSION", "0.1", CONST_PERSISTENT | CONST_CS);
 
    return SUCCESS;
}
