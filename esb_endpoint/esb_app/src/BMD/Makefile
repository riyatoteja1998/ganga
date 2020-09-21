XML_HANDLER = ./xml_parsing.c ./xml_header.h ./xmltojson.c
SQL_API     =  ../DB-ACCESs/check_all_routes.c ../DB-ACCESs/check_transport.c ../DB-ACCESs/check_transform.c ../DB-ACCESs/db_connection.h
XML_LIB     =   `xml2-config --cflags` `xml2-config --libs`
SQL_LIB     =  `mysql_config --cflags --libs`
example: validate_request.c
	gcc validate_request.c ${XML_HANDLER} ${SQL_API} -o example ${SQL_LIB} ${XML_LIB}

clean:
	rm example
