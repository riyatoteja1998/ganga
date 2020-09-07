#include<stdio.h>
#include "xml_header.h"
#include<stdlib.h>
#include "munit.h"
#include <libxml/parser.h>

bmd *bmd_attributes()
{
  bmd *b = (bmd*)malloc(sizeof(bmd));
  bmd_envelop *e = (bmd_envelop*)malloc(sizeof(bmd_envelop));
  e->Sender = "756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA";
  e->Destination = "6393F82F-4687-433D-AA23-1966330381FE";
  e->CreationDateTime = "2020-08-12T05:18:00+0000";
  e->MessageID = "A9ECAEF2-107A-4452-9553-043B6D25386E";
  e->MessageType = "CreditReport";
  e->ReferenceID = "INV-PROFILE-889712";
  e->Signature = "63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c";
  b->envelop_value = e;
  b->payload = "001-01-1234";
  return b;
}

static void *bmd_setup(const MunitParameter params[], void *user_data)
{
   char *doc = "/home/harshal/Desktop/bmd.xml";
   bmd *b = (bmd*)malloc(sizeof(bmd));
   b->envelop_value = extract_envelop(doc);
   b->payload = extract_payload(doc);
   return b;
}


static MunitResult parse_test_xml_file(const MunitParameter params[], void *fixture)
{
  bmd *b = (bmd*)fixture;
  bmd *expected_b = bmd_attributes();
  munit_assert_string_equal(b->envelop_value->Sender,expected_b->envelop_value->Sender);
  munit_assert_string_equal(b->envelop_value->Destination,expected_b->envelop_value->Destination);
  munit_assert_string_equal(b->envelop_value->MessageType,expected_b->envelop_value->MessageType);
  munit_assert_string_equal(b->envelop_value->CreationDateTime,expected_b->envelop_value->CreationDateTime);
  munit_assert_string_equal(b->envelop_value->MessageID,expected_b->envelop_value->MessageID);
  munit_assert_string_equal(b->envelop_value->Signature,expected_b->envelop_value->Signature);
  munit_assert_string_equal(b->envelop_value->ReferenceID,expected_b->envelop_value->ReferenceID);
  munit_assert_string_equal(b->payload,expected_b->payload);
  return MUNIT_OK;
}

static void bmd_tear_down(void *fixture)
{
  bmd *b = (bmd*)fixture;
  free(b->envelop_value);
  free(b->payload);
  free(b);

}

MunitTest tests[] = {
    {
        "/bmd_test",   /* name */
        parse_test_xml_file,  /* test function */
        bmd_setup,     /* setup function for the test */
        bmd_tear_down, /* tear_down */
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

