/***** includes *****/
#include "lfds711_queue_bounded_singleproducer_singleconsumer_internal.h"





/****************************************************************************/
int lfds711_queue_bss_enqueue( struct lfds711_queue_bss_state *qbsss,
                               void *key,
                               void *value )
{
  struct lfds711_queue_bss_element
    *qbsse;
  LFDS711_PAL_ASSERT( qbsss != NULL );
  // TRD : key can be NULL
  // TRD : value can be NULL

  LFDS711_MISC_BARRIER_LOAD;
  lfds711_pal_uint_t number_elements = qbsss->number_elements;
  lfds711_pal_uint_t write_index = qbsss->write_index;
  lfds711_pal_uint_t read_index = qbsss->read_index;

  if( ( (write_index+1) % number_elements ) != read_index )
  {
    qbsse = qbsss->element_array + write_index;

    qbsse->key = key;
    qbsse->value = value;

    LFDS711_MISC_BARRIER_STORE;

    qbsss->write_index = (write_index + 1) % number_elements;

    return 1;
  }

  return 0;
}



uint32 armada_enqueue(struct armada_QbssState* state, uint32 k, uint32 v)
{
 uint32 ret = 0;
  uint32 _0_write__index;
  _0_write__index = (*(state)).write_index;
  //after_0: ;
  uint32 _1_mask;
  _1_mask = (*(state)).mask;
  uint32 _2_read__index;
  _2_read__index = (*(state)).read_index;
  struct BSSQueueElement* _3_e = NULL;
  if ((((_0_write__index) + ((uint32)1)) & (_1_mask)) != (_2_read__index)) {
    _3_e = ((*(state)).element_array) + (_0_write__index);
  //after_2: ;
    (*(_3_e)).key = k;
  //after_3: ;
    (*(_3_e)).value = v;
  //after_4: ;
    (*(state)).write_index = ((_0_write__index) + ((uint32)1)) & (_1_mask);
  //after_5: ;
    ret = (uint32)1;
    return ret;
  //after_6: ;
  }
  //after_1: ;
  ret = (uint32)0;
  return ret;
}


