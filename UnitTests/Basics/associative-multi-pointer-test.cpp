////////////////////////////////////////////////////////////////////////////////
/// @brief test suite for TRI_associative_multi_pointer_t
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2012 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Max Neunhoeffer
/// @author Copyright 2014, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include "Basics/AssocMulti.h"
#include "Basics/hashes.h"
#include "Basics/fasthash.h"
#include "Basics/tri-strings.h"
#include "Basics/conversions.h"

#include <vector>

using namespace std;

// -----------------------------------------------------------------------------
// --SECTION--                                                    private macros
// -----------------------------------------------------------------------------

#define INIT_MULTI \
  triagens::basics::AssocMulti<void, void, uint32_t> a1( \
      HashKey, HashElement, IsEqualKeyElement, IsEqualElementElement, IsEqualElementElementByKey);

#define DESTROY_MULTI ;
  
#define ELEMENT(name, v, k) \
  data_container_t name; \
  name.key   = k; \
  name.value = v;

struct data_container_t {
  int value;
  int key;
  data_container_t () : value(0), key(0) {};
  data_container_t (int key, int value) : value(value), key(key) {};
};

static uint64_t HashKey (void const* e) {
  int const* key = (int const*) e;

  return fasthash64(key, sizeof(int), 0x12345678);
}

static uint64_t HashElement (void const* e, bool byKey) {
  data_container_t const* element = (data_container_t const*) e;

  if (byKey) {
    return fasthash64(&element->key, sizeof(element->key), 0x12345678);
  }
  else {
    return fasthash64(&element->value, sizeof(element->value), 0x12345678);
  }
}

static bool IsEqualKeyElement (void const* k, void const* r) {
  int const* key = (int const*) k;
  data_container_t const* element = (data_container_t const*) r;

  return *key == element->key;
}

static bool IsEqualElementElement (void const* l, void const* r) {
  data_container_t const* left = (data_container_t const*) l;
  data_container_t const* right = (data_container_t const*) r;

  return left->value == right->value;
}

static bool IsEqualElementElementByKey (void const* l, void const* r) {
  data_container_t const* left = (data_container_t const*) l;
  data_container_t const* right = (data_container_t const*) r;

  return left->key == right->key;
}

// -----------------------------------------------------------------------------
// --SECTION--                                                 private constants
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                 setup / tear-down
// -----------------------------------------------------------------------------

struct CMultiPointerSetup {
  CMultiPointerSetup () {
    BOOST_TEST_MESSAGE("setup AssocMulti_t");
  }

  ~CMultiPointerSetup () {
    BOOST_TEST_MESSAGE("tear-down AssocMulti_t");
  }
};

// -----------------------------------------------------------------------------
// --SECTION--                                                        test suite
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief setup
////////////////////////////////////////////////////////////////////////////////

BOOST_FIXTURE_TEST_SUITE(CMultiPointerTest, CMultiPointerSetup)

////////////////////////////////////////////////////////////////////////////////
/// @brief test initialisation
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE (tst_init) {
  INIT_MULTI

  BOOST_CHECK_EQUAL((uint32_t) 0, a1.size());

  DESTROY_MULTI
}

////////////////////////////////////////////////////////////////////////////////
/// @brief test unique insertion
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE (tst_insert_few) {
  INIT_MULTI

  void* r = 0;

  ELEMENT(e1, 1, 123);
  BOOST_CHECK_EQUAL(r, a1.insert(&e1, true, false));
  BOOST_CHECK_EQUAL((uint32_t) 1, a1.size());
  BOOST_CHECK_EQUAL(&e1, a1.lookup(&e1));

  BOOST_CHECK_EQUAL(&e1, a1.remove(&e1));
  BOOST_CHECK_EQUAL((uint32_t) 0, a1.size());
  BOOST_CHECK_EQUAL(r, a1.lookup(&e1));

  DESTROY_MULTI
}

// Note MODULUS must be a divisor of NUMBER_OF_ELEMENTS
// and NUMBER_OF_ELEMENTS must be a multiple of 3.
#define NUMBER_OF_ELEMENTS 3000
#define MODULUS 10

BOOST_AUTO_TEST_CASE (tst_insert_delete_many) {
  INIT_MULTI

  unsigned int i, j;
  ELEMENT(e, 0, 0);
  vector<data_container_t*> v;

  data_container_t* n = 0;
  data_container_t* p;
  data_container_t* one_more;

  // Put in some data:
  for (i = 0;i < NUMBER_OF_ELEMENTS;i++) {
    p = new data_container_t(i % MODULUS, i);
    v.push_back(p);
    BOOST_CHECK_EQUAL(n, a1.insert(p, true, false));
  }
  one_more = new data_container_t(NUMBER_OF_ELEMENTS % MODULUS, 
                                  NUMBER_OF_ELEMENTS);

  // Now check it is there (by element):
  for (i = 0;i < NUMBER_OF_ELEMENTS;i++) {
    p = static_cast<data_container_t*>(a1.lookup(v[i]));
    BOOST_CHECK_EQUAL(p, v[i]);
  }
  // This should not be there:
  p = static_cast<data_container_t*>(a1.lookup(one_more));
  BOOST_CHECK_EQUAL(n, p);
  
  // Now check by key:
  std::vector<void*>* res = nullptr;

  for (i = 0;i < MODULUS;i++) {
    int* space = static_cast<int*>(TRI_Allocate(TRI_UNKNOWN_MEM_ZONE,
                                    sizeof(int) * NUMBER_OF_ELEMENTS / MODULUS,
                                    true));
    res = a1.lookupByKey(&i);
    BOOST_CHECK_EQUAL((int) res->size(),
                      (int) (NUMBER_OF_ELEMENTS / MODULUS));
    // Now check its contents:
    for (j = 0; j < res->size(); j++) {
      data_container_t* q = static_cast<data_container_t*> (res->at(j));
      BOOST_CHECK_EQUAL((int) (q->value % MODULUS), (int) i);
      BOOST_CHECK_EQUAL(space[(q->value - i) / MODULUS], 0);
      space[(q->value - i) / MODULUS] = 1;
    }
    TRI_Free(TRI_UNKNOWN_MEM_ZONE, space);
    delete res;
  }

  // Delete some data:
  for (i = 0;i < v.size();i += 3) {
    BOOST_CHECK_EQUAL(v[i], a1.remove(v[i]));
  }
  for (i = 0;i < v.size();i += 3) {
    BOOST_CHECK_EQUAL(n, a1.remove(v[i]));
  }

  // Now check which are there (by element):
  for (i = 0;i < NUMBER_OF_ELEMENTS;i++) {
    p = static_cast<data_container_t*> (a1.lookup(v[i]));
    if (i % 3 == 0) {
      BOOST_CHECK_EQUAL(p,n);
    }
    else {
      BOOST_CHECK_EQUAL(p,v[i]);
    }
  }
  // This should not be there:
  p = static_cast<data_container_t*> (a1.lookup(one_more));
  BOOST_CHECK_EQUAL(n, p);
  
  // Delete some more:
  for (i = 1;i < v.size();i += 3) {
    BOOST_CHECK_EQUAL(v[i], a1.remove(v[i]));
  }
  for (i = 1;i < v.size();i += 3) {
    BOOST_CHECK_EQUAL(n, a1.remove(v[i]));
  }

  // Now check which are there (by element):
  for (i = 0;i < NUMBER_OF_ELEMENTS;i++) {
    p = static_cast<data_container_t*> (a1.lookup(v[i]));
    if (i % 3 == 2) {
      BOOST_CHECK_EQUAL(p,v[i]);
    }
    else {
      BOOST_CHECK_EQUAL(p,n);
    }
  }
  // This should not be there:
  p = static_cast<data_container_t*> (a1.lookup(one_more));
  BOOST_CHECK_EQUAL(n, p);
  
  // Delete the rest:
  for (i = 2;i < v.size();i += 3) {
    BOOST_CHECK_EQUAL(v[i], a1.remove(v[i]));
  }
  for (i = 2;i < v.size();i += 3) {
    BOOST_CHECK_EQUAL(n, a1.remove(v[i]));
  }

  // Now check which are there (by element):
  for (i = 0;i < NUMBER_OF_ELEMENTS;i++) {
    p = static_cast<data_container_t*> (a1.lookup(v[i]));
    BOOST_CHECK_EQUAL(p,n);
  }
  // This should not be there:
  p = static_cast<data_container_t*> (a1.lookup(one_more));
  BOOST_CHECK_EQUAL(n, p);
  // Pull down data again:
  for (i = 0;i < NUMBER_OF_ELEMENTS;i++) {
    delete v[i];
  }
  v.clear();
  delete one_more;

  DESTROY_MULTI
}

////////////////////////////////////////////////////////////////////////////////
/// @brief generate tests
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END ()

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End:
