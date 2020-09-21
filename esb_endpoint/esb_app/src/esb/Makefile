SQL_FUN     =  ../DB-ACCESS/insertion.c ../DB-ACCESS/check_all_routes.c ../DB-ACCESS/check_transport.c ../DB-ACCESS/check_transform.c 
XML_FUN = ../BMD/xml_parsing.c ../BMD/xml_header.h ../BMD/validate_request.c ../BMD/bmd_parse_main.c
LIBXML     =   `xml2-config --libs` `xml2-config --cflags`
LIBSQL     =  `mysql_config --cflags --libs`
a:  esb.c 
	gcc ${XML_FUN} esb.c ${SQL_FUN} -o a ${LIBSQL} ${LIBXML}

clean:
	rm a
