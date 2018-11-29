PHP_ARG_ENABLE(kou, whether to enable php-kou,
[  --enable-pkou     Enable php-kou])
 
dnl Check whether the extension is enabled at all
if test "$PHP_KOU" = "yes"; then
 
  dnl Finally, tell the build system about the extension and what files are needed
 
  AC_DEFINE(HAVE_KOU, 1, [Whether you have php-kou])
 
  PHP_NEW_EXTENSION(kou, php_kou.c, $ext_shared)
  PHP_SUBST(KOU_SHARED_LIBADD)
 
fi

