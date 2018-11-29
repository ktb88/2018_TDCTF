#ifndef PHP_KOU_H
#define PHP_KOU_H
 
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include <php.h>
#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>
 
#define PHP_KOU_VERSION "0.1"
#define PHP_KOU_EXTNAME "kou"
 
#ifndef PHP_KOU_VERSION_STRING
#define PHP_KOU_VERSION_STRING "0.1"
#endif
 
#define KOU_NS "Kou"
 
static PHP_MINFO_FUNCTION(kou);
static PHP_MINIT_FUNCTION(kou);

PHP_FUNCTION(login);
PHP_FUNCTION(loadFile);


extern zend_module_entry kou_module_entry;
#define phpext_kou_extension_ptr &kou_module_entry



#endif  /* PHP_KOU_H */
