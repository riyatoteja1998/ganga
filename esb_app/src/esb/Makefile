SQL_FUN     =  ../DB-ACCESS/insertion.c ../DB-ACCESS/check_all_routes.c ../DB-ACCESS/check_transport.c ../DB-ACCESS/check_transform.c ../DB-ACCESS/db_connection.h
XML_FUN = ../BMD/xml_parsing.c ../BMD/xml_header.h ../BMD/validate_request.c ../BMD/bmd_parse_main.c
LIBXML     =   `xml2-config --libs` `xml2-config --cflags`
LIBSQL     =  `mysql_config --cflags --libs`
esb:  esb.c 
	gcc ${XML_FUN} esb.c ${SQL_FUN} -o esb ${LIBSQL} ${LIBXML}

clean:
	rm esb
