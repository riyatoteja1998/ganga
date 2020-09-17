#include<stdio.h>
#include "xml_header.h"
#include<stdlib.h>
#include "munit.h"
#include <libxml/parser.h>

//Setup Function
static void *insert_setup(const MunitParameter params[], void *user_data)
{
   char *doc = "/home/harshal/Desktop/bmd.xml";
   bmd *b = (bmd*)malloc(sizeof(bmd));
   b->envelop_value = extract_envelop(doc);
   b->payload = extract_payload(doc);
   return b;
}

//Test Function
static MunitResult test_insert_file(const MunitParameter params[], void *fixture)
{
  
  //bmd *b = bmd_attributes();
  bmd *b = (bmd*)fixture;
 int success = insert_esbrequest(b->envelop_value->Sender,b->envelop_value->Destination,b->envelop_value->MessageType,b->envelop_value->ReferenceID,"x","1","1");
 munit_assert_int(success,==,1);
  return MUNIT_OK;
}
//Free Function
static void insert_tear_down(void *fixture)
{
  bmd *b = (bmd*)fixture;
  free(b->payload);
  free(b->envelop_value);
  free(b);

}
//Naming Test Function
MunitTest tests[] = {
    {
        "/insert_test",   /* name */
        test_insert_file,  /* test function */
        insert_setup,     /* setup function for the test */
        insert_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
  static const MunitSuite suite = {
    "/tests",                 /* name */
    tests,                    /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};


int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}   
