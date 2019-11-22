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
  lfds711_pal_uint_t number_elements = qbsss->number_elements;
  lfds711_pal_uint_t write_index = qbsss->write_index;
  lfds711_pal_uint_t read_index = qbsss->read_index;
  // TRD : key can be NULL
  // TRD : value can be NULL

  LFDS711_MISC_BARRIER_LOAD;

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

