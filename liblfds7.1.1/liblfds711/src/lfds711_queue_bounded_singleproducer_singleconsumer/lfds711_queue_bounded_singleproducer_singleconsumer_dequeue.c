/***** includes *****/
#include "lfds711_queue_bounded_singleproducer_singleconsumer_internal.h"





/****************************************************************************/
int lfds711_queue_bss_dequeue( struct lfds711_queue_bss_state *qbsss,
                               void **key,
                               void **value )
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

  if( read_index != write_index )
  {
    qbsse = qbsss->element_array + read_index;

    if( key != NULL )
      *key = qbsse->key;

    if( value != NULL )
      *value = qbsse->value;

    qbsss->read_index = (read_index + 1) % number_elements;

    LFDS711_MISC_BARRIER_STORE;

    return 1;
  }

  return 0;
}


uint32 armada_dequeue(struct armada_QbssState* state, uint32* k, uint32* v)
{
  LFDS711_MISC_BARRIER_LOAD;
  uint32 ret = 0;
  uint32 _4_write__index;
  _4_write__index = (*(state)).write_index;
  uint32 _5_mask;
  _5_mask = (*(state)).mask;
  uint32 _6_read__index;
  _6_read__index = (*(state)).read_index;
  struct armada_BSSQueueElement* _7_e = NULL;
  uint32 _8_key = 0;
  uint32 _9_value = 0;
  if ((_6_read__index) != (_4_write__index)) {
    _7_e = ((*(state)).element_array) + (_6_read__index);
    if ((k) != (NULL)) {
      _8_key = (*(_7_e)).key;
      *k = _8_key;
    }
    if ((v) != (NULL)) {
      _9_value = (*(_7_e)).value;
      *v = _9_value;
    }
    (*(state)).read_index = ((_6_read__index) + ((uint32)1)) & (_5_mask);
    LFDS711_MISC_BARRIER_STORE;
    ret = (uint32)1;
    return ret;
  }
  ret = (uint32)0;
  return ret;
}