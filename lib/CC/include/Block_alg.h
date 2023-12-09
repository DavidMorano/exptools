#ifndef BLOCK_ALGH
#define BLOCK_ALGH

#include <generic.h>
#include <rand48.h>
#include <stddef.h>

PT_names 
	PRED(TYPE)	TYPE _PRED
	REL(TYPE)	TYPE _REL
	FUN1(TYPE)	TYPE _FUN1
	FUN2(TYPE)	TYPE _FUN2
PT_end

PT_define Block_algdeclare(TYPE)
typedef int REL(TYPE)(const TYPE*,const TYPE*);
typedef int PRED(TYPE)(const TYPE*);
typedef void FUN1(TYPE)(TYPE*);
typedef void FUN2(TYPE)(ptrdiff_t, TYPE*);

const TYPE* 
bin_loc(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
const TYPE*
bin_loc_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
const TYPE* 
bin_search(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
const TYPE*
bin_search_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
void 
copy(
    TYPE* begin,
    TYPE* end,
    TYPE* result
);
ptrdiff_t 
count(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
ptrdiff_t 
count_p(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end
);
ptrdiff_t 
count_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
TYPE*
set_diff(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
TYPE* 
set_diff_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
void 
fill(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
void 
for_each(
    FUN1(TYPE)* function,
    TYPE* begin,
    TYPE* end
);
void 
generate(
    FUN2(TYPE)* function,
    TYPE* begin,
    TYPE* end
);
TYPE* 
insert(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
insert_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
void 
ins_sort(
    TYPE* begin,
    TYPE* end
);
void 
ins_sort_r(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
);
static void 
ins_sort_chunks(
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end
);
static void 
ins_sort_chunks_r(
    REL(TYPE)* rel_ptr,
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end
);
TYPE* 
set_inter(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
TYPE* 
set_inter_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
void 
merge(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
void 
merge_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
TYPE* 
merge_sort(
    TYPE* begin,
    TYPE* end,
    TYPE* result
);
TYPE* 
merge_sort_r(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end,
    TYPE* result
);
static void 
merge_sort_step(
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end,
    TYPE* result
);
static void 
merge_sort_step_r(
    REL(TYPE)* rel_ptr,
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end,
    TYPE* result
);
const TYPE* 
minimum(
    const TYPE* begin,
    const TYPE* end
);
const TYPE* 
minimum_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin,
    const TYPE* end
);
const TYPE* 
mismatch(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2
);
const TYPE* 
mismatch_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2
);
static TYPE*
ordered_part_ATTLC(
    register TYPE *begin,
    register TYPE *end
);
static TYPE* 
ordered_part_r_ATTLC(
    register REL(TYPE)* rel_ptr,
    register TYPE* begin,
    register TYPE* end
);
TYPE* 
part(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
part_p(
    PRED(TYPE)* pred_ptr,
    TYPE* begin,
    TYPE* end
);
TYPE* 
part_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
part_c(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
part_pc(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
part_rc(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
const TYPE* 
pos(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
const TYPE* 
pos_p(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end
);
const TYPE* 
pos_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
static void 
quicksort_loop_ATTLC(
    register TYPE *begin,
    register TYPE *end
);
static void 
quicksort_loop_r_ATTLC(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
);
const TYPE* 
random(
    const TYPE* begin,
    const TYPE* end
);
TYPE* 
rem(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
rem_p(
    PRED(TYPE)* pred_ptr,
    TYPE* begin,
    TYPE* end
);
TYPE* 
rem_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
rem_c(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
rem_pc(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
rem_rc(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
rem_dup(
    TYPE* begin,
    TYPE* end
);
TYPE*
rem_dup_r(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
);
TYPE* 
rem_dup_c(
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
void 
reverse(
    TYPE* begin,
    TYPE* end
);
void 
reverse_c(
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
const TYPE* 
rt_pos(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
const TYPE* 
rt_pos_p(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end
);
const TYPE* 
rt_pos_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
);
void 
rotate(
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end
);
void 
rotate_c(
    ptrdiff_t number,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
const TYPE* 
search(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2
);
const TYPE* 
search_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2
);
void 
select(
    ptrdiff_t nth,
    TYPE* begin,
    TYPE* end
);
void 
select_r(
    REL(TYPE)* rel_ptr,
    ptrdiff_t nth,
    TYPE* begin,
    TYPE* end
);
TYPE* 
set_insert(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
set_insert_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
set_remove(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
set_remove_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
set_union(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
TYPE* 
set_union_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
void 
shuffle(
    TYPE* begin,
    TYPE* end
);
void 
shuffle_c(
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
void 
sort(
    TYPE* begin,
    TYPE* end
);
void 
sort_r(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
);
TYPE* 
part_s(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
part_ps(
    PRED(TYPE)* pred_ptr,
    TYPE* begin,
    TYPE* end
);
TYPE* 
part_rs(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
part_sc(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
part_psc(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
part_rsc(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
rem_s(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
rem_ps(
    PRED(TYPE)* pred_ptr,
    TYPE* begin,
    TYPE* end
);
TYPE* 
rem_rs(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
);
TYPE* 
rem_sc(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
rem_psc(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
rem_rsc(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
void 
sort_s(
    TYPE* begin,
    TYPE* end
);
void 
sort_rs(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
);
void 
subs(
    const TYPE &value,
    TYPE new_value,
    TYPE* begin,
    TYPE* end
);
void 
subs_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE new_value,
    TYPE* begin,
    TYPE* end
);
void 
subs_c(
    const TYPE &value,
    TYPE new_value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
void 
subs_rc(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE new_value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
set_sdiff(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
TYPE* 
set_sdiff_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2,
    TYPE* result
);
TYPE* 
unique(
    TYPE* begin,
    TYPE* end
);
TYPE* 
unique_r(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
);
TYPE* 
unique_c(
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
TYPE* 
unique_rc(
    REL(TYPE)* rel_ptr,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
);
PT_end
				


PT_define bin_locimplement(TYPE)
const TYPE* 
bin_loc(
    register const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  while (5 < end-begin)
    {
      register const TYPE *index = begin + ((end - begin) >> 1);

      if (value < *index)
        end = index;
      else
        begin = index + 1;
    }

  while (begin < end)
    if (!(value < *--end))
      return end + 1;

  return end;
} 
PT_end

PT_define bin_loc_rimplement(TYPE)

const TYPE*
bin_loc_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  register const TYPE *temp = &value;
  while (5 < end-begin)
    {
      register const TYPE *index = begin + ((end - begin) >> 1);

      if ((*rel_ptr)(temp, index) < 0)
        end = index;
      else
        begin = index + 1;
    }

  while (begin < end)
    if (!((*rel_ptr)(temp, --end) < 0))
      return end + 1;

  return end;
} 
PT_end

PT_define bin_searchimplement(TYPE)
bin_locimplement(TYPE)

const TYPE* 
bin_search(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
){
  const TYPE *index = bin_loc(value, begin, end);

  if (begin < index && !(*(index - 1) < value))
    return index - 1;

  else
    return 0;
} 
PT_end

PT_define bin_search_rimplement(TYPE)
bin_loc_rimplement(TYPE)

const TYPE*
bin_search_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end
){
  const TYPE *index = bin_loc_r(rel_ptr, value, begin, end);

  if (begin < index && !((*rel_ptr)(index - 1, &value) < 0))
    return index - 1;

  else
    return 0;
} 
PT_end

PT_define copyimplement(TYPE)
void 
copy(
    register TYPE* begin,
    register TYPE* end,
    register TYPE* result
){
  if (begin < result)
    {
      result += end - begin;
      while (begin < end)
        *--result = *--end;
    }
  else if (result < begin)
    while (begin < end)
      *result++ = *begin++;
} 
PT_end

PT_define countimplement(TYPE)
ptrdiff_t 
count(
    register const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  register ptrdiff_t n = 0;

  while (begin < end)
    if (*begin++ == value)
      n++;

  return n;
} 
PT_end

PT_define count_pimplement(TYPE)
ptrdiff_t 
count_p(
    register PRED(TYPE)* pred_ptr,
    register const TYPE* begin,
    register const TYPE* end
){
  register ptrdiff_t n = 0;

  while (begin < end)
   if ((*pred_ptr)(begin++))
     n++;

  return n;
} 
PT_end

PT_define count_rimplement(TYPE)
ptrdiff_t 
count_r(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  register const TYPE *temp = &value;
  register ptrdiff_t n = 0;

  while (begin < end)
    if ((*rel_ptr)(begin++, temp) == 0)
      n++;

  return n;
} 
PT_end

PT_define set_diffimplement(TYPE)
TYPE* 
set_diff(
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    if (*begin1 < *begin2)
      *result++ = *begin1++;
    else if (!(*begin2++ < *begin1))
      begin1++;

  while (begin1 < end1)
    *result++ = *begin1++;

  return result;
} 
PT_end

PT_define set_diff_rimplement(TYPE)
TYPE* 
set_diff_r(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    {
      register int c = (*rel_ptr)(begin2, begin1);
      if (0 < c)
        *result++ = *begin1++;
      else
        {
          if (c == 0)
            begin1++;
          begin2++;
        }
    }

  while (begin1 < end1)
    *result++ = *begin1++;

  return result;
} 
PT_end

PT_define fillimplement(TYPE)
void 
fill(
    register const TYPE &value,
    register TYPE* begin,
    register TYPE* end
){
  while (begin < end)
    *begin++ = value;
} 
PT_end

PT_define for_eachimplement(TYPE)
void 
for_each(
    register FUN1(TYPE)* function,
    register TYPE* begin,
    register TYPE* end
){
  while (begin < end)
    (*function)(begin++);
} 
PT_end

PT_define generateimplement(TYPE)
void 
generate(
    FUN2(TYPE)* function,
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *index = begin;

  for (; begin < end; begin++)
    (*function)(begin - index, begin);
} 
PT_end

PT_define insertimplement(TYPE)
bin_locimplement(TYPE)
copyimplement(TYPE)
TYPE* 
insert(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
  begin = (TYPE*)bin_loc(value, begin, end);

  copy(begin, end, begin + 1);

  *begin = value;

  return begin;
} 
PT_end

PT_define insert_rimplement(TYPE)
bin_loc_rimplement(TYPE)
copyimplement(TYPE)
TYPE* 
insert_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
  begin = (TYPE*)bin_loc_r(rel_ptr, value, begin, end);

  copy(begin, end, begin + 1);

  *begin = value;

  return begin;
} 
PT_end

PT_define ins_sortimplement(TYPE)
minimumimplement(TYPE)
void 
ins_sort(
    register TYPE* begin,
    register TYPE* end
){
  if (end - begin < 2)  /* size < 2 */
    return;

  TYPE *r = (TYPE*)minimum(begin, end); /* create a sentinel */
  TYPE temp = *begin;          /* swap */
  *begin = *r;
  *r = temp;

  begin++; /* there is no need to insert the second element */

  while (++begin < end)
    {
      register TYPE value = *begin;
      register TYPE *index = begin;

      while (value < *--index)
        *(index + 1) = *index;

      *(index + 1) = value;
    }
} 
PT_end

PT_define ins_sort_rimplement(TYPE)
void 
ins_sort_r(
    register REL(TYPE)* rel_ptr,
    register TYPE* begin,
    TYPE* end
){
  register TYPE *index = begin;

  while (++index < end)
    {
      TYPE value = *index;
      register TYPE *temp = &value;
      register TYPE *current = index;

      for (; begin < current && (*rel_ptr)(temp , current - 1) < 0; current--)
        *current = *(current - 1);

      *current = value;
    }
} 
PT_end

PT_define set_interimplement(TYPE)
TYPE* 
set_inter(
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    if (*begin2 < *begin1)
      begin2++;
    else if (*begin1 < *begin2)
      begin1++;
    else
      {
        *(result++) = *(begin1++);
        begin2++;
      }
  return result;
} 
PT_end

PT_define set_inter_rimplement(TYPE)
TYPE* 
set_inter_r(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    {
      register int c = (*rel_ptr)(begin2, begin1);

      if (c < 0)
        begin2++;
      else if (0 < c)
        begin1++;
      else
        {
          *(result++) = *(begin1++);
          begin2++;
        }
    }
  return result;
} 
PT_end

PT_define mergeimplement(TYPE)
void 
merge(
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    *result++ = (*begin2 < *begin1 ? *begin2++ : *begin1++);

  while (begin1 < end1)
    *result++ = *begin1++;

  while (begin2 < end2)
    *result++ = *begin2++;
} 
PT_end

PT_define merge_rimplement(TYPE)
void 
merge_r(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    *result++ = ((*rel_ptr)(begin2, begin1) < 0 ? *begin2++ : *begin1++);

  while (begin1 < end1)
    *result++ = *begin1++;

  while (begin2 < end2)
    *result++ = *begin2++;
} 
PT_end

PT_define merge_sort_stepimplement(TYPE)
mergeimplement(TYPE)
static void 
merge_sort_step(
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end,
    TYPE* result
){
  ptrdiff_t m = 2 * number;

  while (begin + m < end)
    {
      merge(begin, begin + number, begin + number, begin + m, result);
      begin += m;
      result += m;
    }

  if (begin + number + 1 < end)
    merge(begin, begin + number, begin + number, end, result);
  else
    while (begin < end)
      *result++ = *begin++;
} 
PT_end

PT_define ins_sort_chunksimplement(TYPE)
ins_sortimplement(TYPE)
static void 
ins_sort_chunks(
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end
){
  for (; begin + number < end; begin += number)
    ins_sort(begin, begin + number);

  ins_sort(begin, end);
} 
PT_end

PT_define merge_sortimplement(TYPE)
merge_sort_stepimplement(TYPE)
ins_sort_chunksimplement(TYPE)
TYPE* 
merge_sort(
    TYPE* begin,
    TYPE* end,
    TYPE* result
){
  ptrdiff_t number = 8, length = end - begin;

  ins_sort_chunks(number, begin, end);

  for (; number < length;
       number += number, end = begin, begin = result, result = end)
    merge_sort_step(number, begin, begin + length, result);

  return begin;
} 
PT_end

PT_define merge_sort_step_rimplement(TYPE)
merge_rimplement(TYPE)
static void 
merge_sort_step_r(
    REL(TYPE)* rel_ptr,
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end,
    TYPE* result
){
  ptrdiff_t m = 2 * number;

  while (begin + m < end)
    {
      merge_r(rel_ptr, begin, begin + number, begin + number, begin + m,
            result);
      begin += m;
      result += m;
    }

  if (begin + number + 1 < end)
    merge_r(rel_ptr, begin, begin + number, begin + number, end, result);
  else
    while (begin < end)
      *result++ = *begin++;
} 
PT_end

PT_define ins_sort_chunks_rimplement(TYPE)
ins_sort_rimplement(TYPE)
static void 
ins_sort_chunks_r(
    REL(TYPE)* rel_ptr,
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end
){
  for (; begin + number < end; begin += number)
    ins_sort_r(rel_ptr, begin, begin + number);

  ins_sort_r(rel_ptr, begin, end);
} 
PT_end

PT_define merge_sort_rimplement(TYPE)
merge_sort_step_rimplement(TYPE)
ins_sort_chunks_rimplement(TYPE)
TYPE* 
merge_sort_r(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end,
    TYPE* result
){
  ptrdiff_t number = 8, length = end - begin;

  ins_sort_chunks_r(rel_ptr, number, begin, end);

  for (; number < length;
       number += number, end = begin, begin = result, result = end)
    merge_sort_step_r(rel_ptr, number, begin, begin + length, result);

  return begin;
} 
PT_end

PT_define minimumimplement(TYPE)
const TYPE* 
minimum(
    register const TYPE* begin,
    register const TYPE* end
){
    register const TYPE *index = begin;

    while (++begin < end)
      if(*begin < *index)
	index = begin;

    return index;
} 
PT_end

PT_define minimum_rimplement(TYPE)
const TYPE* 
minimum_r(
    REL(TYPE)* rel_ptr,
    const TYPE* begin,
    const TYPE* end
){
    register const TYPE *index = begin;

    while (++begin < end)
      if((*rel_ptr)(begin,index) < 0)
	index = begin;

    return index;
} 
PT_end

PT_define mismatchimplement(TYPE)
const TYPE* 
mismatch(
    const TYPE* begin1,
    const TYPE* end1,
    const TYPE* begin2,
    const TYPE* end2
){
    register ptrdiff_t len =
      end1 - begin1 < end2 - begin2 ? end1 - begin1 : end2 - begin2;

    while (0 < len--){
      if(!(*begin1 == *begin2++)) return begin1;
      begin1++;
    }
    return 0;
} 
PT_end

PT_define mismatch_rimplement(TYPE)
const TYPE* 
mismatch_r(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2
){
    register ptrdiff_t len =
    end1 - begin1 < end2 - begin2 ? end1 - begin1 : end2 - begin2;

    while (0 < len--){
	if((*rel_ptr)(begin1, begin2++) != 0)return begin1;
	begin1++;
    }
    return 0;
} 
PT_end

PT_define partimplement(TYPE)
TYPE* 
part(
    register const TYPE &value,
    register TYPE* begin,
    register TYPE* end
){
  for (;;)
    {
      for (;;begin++)
        if (begin >= end)
          return end;
        else if (!(*begin == value))
          break;

      for (;;)
        if (begin >= --end)
          return end;
        else if (*end == value)
          break;

      {
        register TYPE temp = *begin;
        *begin++ = *end;
        *end = temp;
      }
    }
} 
PT_end

PT_define part_pimplement(TYPE)
TYPE* 
part_p(
    register PRED(TYPE)* pred_ptr,
    register TYPE* begin,
    register TYPE* end
){
  for (;;)
    {
      for (;;begin++)
        if (begin >= end)
          return end;
        else if (!(*pred_ptr)(begin))
          break;

      for (;;)
        if (begin >= --end)
          return end;
        else if ((*pred_ptr)(end))
          break;

      {
        register TYPE temp = *begin;
        *begin++ = *end;
        *end = temp;
      }
    }
} 
PT_end

PT_define part_rimplement(TYPE)
TYPE* 
part_r(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register TYPE* begin,
    register TYPE* end
){
  register const TYPE *temp = &value;

  for (;;)
    {
      for (;;begin++)
        if (begin >= end)
          return end;
        else if ((*rel_ptr)(begin, temp) != 0)
          break;

      for (;;)
        if (begin >= --end)
          return end;
        else if ((*rel_ptr)(end, temp) == 0)
          break;

      {
        register TYPE temp = *begin;
        *begin++ = *end;
        *end = temp;
      }
    }
} 
PT_end

PT_define part_cimplement(TYPE)
TYPE* 
part_c(
    register const TYPE &value,
    const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register TYPE *last = result + (end - begin);

  for (; begin < end; begin++)
    if (*begin == value)
      *(result++) = *begin;
    else
      *(--last) = *begin;

  return last;
} 
PT_end

PT_define part_pcimplement(TYPE)
TYPE* 
part_pc(
    register PRED(TYPE)* pred_ptr,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register TYPE *last = result + (end - begin);

  for (; begin < end; begin++)
    if ((*pred_ptr)(begin))
      *(result++) = *begin;
    else
      *--last = *begin;

  return last;
} 
PT_end

PT_define part_rcimplement(TYPE)
TYPE* 
part_rc(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register TYPE *last = result + (end - begin);
  register const TYPE *temp = &value;

  for (; begin < end; begin++)
    if ((*rel_ptr)(begin, temp) == 0)
      *(result++) = *begin;
    else
      *(--last) = *begin;

  return last;
} 
PT_end

PT_define posimplement(TYPE)
const TYPE* 
pos(
    register const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  while (begin < end)
    if (*begin++ == value)
      return begin - 1;

  return 0;
} 
PT_end

PT_define pos_pimplement(TYPE)
const TYPE* 
pos_p(
    register PRED(TYPE)* pred_ptr,
    register const TYPE* begin,
    register const TYPE* end
){
  while (begin < end)
    if ((*pred_ptr)(begin++))
      return begin - 1;

  return 0;
} 
PT_end

PT_define pos_rimplement(TYPE)
const TYPE* 
pos_r(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  register const TYPE *temp = &value;

  while (begin < end)
    if ((*rel_ptr)(begin++, temp) == 0)
      return begin - 1;

  return 0;
} 
PT_end

PT_define randomimplement(TYPE)
const TYPE* 
random(
    const TYPE* begin,
    const TYPE* end
){

  if (begin < end)
    return begin + (ptrdiff_t)(drand48() * (end - begin));
  else
    return 0;
} 
PT_end

PT_define remimplement(TYPE)
TYPE* 
rem(
    register const TYPE &value,
    register TYPE* begin,
    register TYPE* end
){
  for (;;)
    {
      for (;;begin++)
        if (begin >= end)
          return end;
        else if (*begin == value)
          break;

      for (;;)
        if (begin >= --end)
          return end;
        else if (!(*end == value))
          break;

      *begin++ = *end;
    }
} 
PT_end

PT_define rem_pimplement(TYPE)
TYPE* 
rem_p(
    register PRED(TYPE)* pred_ptr,
    register TYPE* begin,
    register TYPE* end
){
  for (;;)
    {
      for (;;begin++)
        if (begin >= end)
          return end;
        else if ((*pred_ptr)(begin))
          break;

      for (;;)
        if (begin >= --end)
          return end;
        else if (!(*pred_ptr)(end))
          break;

      *begin++ = *end;
    }
} 
PT_end

PT_define rem_rimplement(TYPE)
TYPE* 
rem_r(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register TYPE* begin,
    register TYPE* end
){
  register const TYPE *temp = &value;
  for (;;)
    {
      for (;;begin++)
        if (begin >= end)
          return end;
        else if ((*rel_ptr)(begin, temp) == 0)
          break;

      for (;;)
        if (begin >= --end)
          return end;
        else if ((*rel_ptr)(end, temp) != 0)
          break;

      *begin++ = *end;
    }
} 
PT_end

PT_define rem_cimplement(TYPE)
TYPE* 
rem_c(
    register const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  for (; begin < end; begin++)
    if (!(*begin == value))
      *result++ = *begin;

  return result;
} 
PT_end

PT_define rem_pcimplement(TYPE)
TYPE* 
rem_pc(
    register PRED(TYPE)* pred_ptr,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  for (; begin < end; begin++)
    if (!(*pred_ptr)(begin))
      *result++ = *begin;

  return result;
} 
PT_end

PT_define rem_rcimplement(TYPE)
TYPE* 
rem_rc(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register const TYPE *temp = &value;

  for (; begin < end; begin++)
    if ((*rel_ptr)(begin, temp) != 0)
      *result++ = *begin;

  return result;
} 
PT_end

PT_define rem_dupimplement(TYPE)
posimplement(TYPE)
TYPE* 
rem_dup(
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *index = begin;
  register TYPE *m;

  for(;index < end; index++)
    if (pos(*index, begin, index) != 0)
      break;

  m = index;

  while (++index < end)
    if (pos(*index, begin, m) == 0)
      *m++ = *index;

  return m;
} 
PT_end

PT_define rem_dup_rimplement(TYPE)
pos_rimplement(TYPE)
TYPE* 
rem_dup_r(
    REL(TYPE)* rel_ptr,
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *index = begin;
  register TYPE *m;

  for(;index < end; index++)
    if (pos_r(rel_ptr, *index, begin, index) != 0)
      break;

  m = index;

  while (++index < end)
    if (pos_r(rel_ptr, *index, begin, m) == 0)
      *m++ = *index;

  return m;
} 
PT_end

PT_define rem_dup_cimplement(TYPE)
posimplement(TYPE)
TYPE* 
rem_dup_c(
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register TYPE *m = result;

  for (; begin < end; begin++)
    if (!pos(*begin, result, m))
      *m++ = *begin;

  return m;
} 
PT_end

PT_define rem_dup_rcimplement(TYPE)
pos_rimplement(TYPE)
TYPE* 
rem_dup_rc(
    REL(TYPE)* rel_ptr,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register TYPE *m = result;

  for (; begin < end; begin++)
    if (pos_r(rel_ptr, *begin, result, m) == 0)
      *m++ = *begin;

  return m;
} 
PT_end

PT_define reverseimplement(TYPE)
void 
reverse(
    register TYPE* begin,
    register TYPE* end
){
  while (begin < --end)
    {
      register TYPE temp = *begin;
      *begin++ = *end;
      *end = temp;
    }
} 
PT_end

PT_define reverse_cimplement(TYPE)
void 
reverse_c(
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  while (begin < end--)
    *result++ = *end;
} 
PT_end

PT_define rt_posimplement(TYPE)
const TYPE* 
rt_pos(
    register const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  while (begin < end)
    if (*--end == value)
      return end;

  return 0;
} 
PT_end

PT_define rt_pos_pimplement(TYPE)
const TYPE* 
rt_pos_p(
    register PRED(TYPE)* pred_ptr,
    register const TYPE* begin,
    register const TYPE* end
){
  while (begin < end)
    if ((*pred_ptr)(--end))
      return end;

  return 0;
} 
PT_end

PT_define rt_pos_rimplement(TYPE)
const TYPE* 
rt_pos_r(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register const TYPE* begin,
    register const TYPE* end
){
  register const TYPE *temp = &value;

  while (begin < end)
    if ((*rel_ptr)(--end, temp) == 0)
      return end;

  return 0;
} 
PT_end



PT_define rotateimplement(TYPE)
reverseimplement(TYPE)
void 
rotate(
    ptrdiff_t number,
    TYPE* begin,
    TYPE* end
){
  if (begin >= end)
    return;

  number %= end - begin;

  if (number == 0)
    return;

  if (number < 0)
    number += (end - begin);

  reverse(begin, end);
  reverse(begin, begin + number);
  reverse(begin + number, end);
} 
PT_end

PT_define rotate_cimplement(TYPE)
copyimplement(TYPE)
void 
rotate_c(
    ptrdiff_t number,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
){
  if (begin >= end)
    return;

  number %= end - begin;

  if (number == 0)
    {
      copy((TYPE*)begin, (TYPE*)end, result);
      return;
    }

  if (number < 0)
    number += (end - begin);

  copy((TYPE*)end - number, (TYPE*)end, result);
  copy((TYPE*)begin, (TYPE*)end - number, result + number);
} 
PT_end

PT_define searchimplement(TYPE)
const TYPE* 
search(
    register const TYPE* begin1,
    const TYPE* end1,
    register const TYPE* begin2,
    const TYPE* end2
){
  register ptrdiff_t d1, d2, k;

  if (begin2 >= end2)
    return begin1;

  d1 = end1 - begin1;
  d2 = end2 - begin2;

  if (d1 < d2)
    return 0;

  k = 0;

  while (k < d2)
    if (begin1[k] == begin2[k])
      k++;
    else if (d1 == d2)
      return 0;
    else
      {
        k = 0;
        begin1++;
        d1--;
      }

  return begin1;
} 
PT_end

PT_define search_rimplement(TYPE)
const TYPE* 
search_r(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin1,
    const TYPE* end1,
    register const TYPE* begin2,
    const TYPE* end2
){
  register ptrdiff_t d1, d2, k;

  if (begin2 >= end2)
    return begin1;

  d1 = end1 - begin1;
  d2 = end2 - begin2;

  if (d1 < d2)
    return 0;

  k = 0;

  while (k < d2)
    if ((*rel_ptr)(begin1 + k, begin2 + k) == 0)
      k++;
    else if (d1 == d2)
      return 0;
    else
      {
        k = 0;
        begin1++;
        d1--;
      }

  return begin1;
} 
PT_end

PT_define selectimplement(TYPE)
ins_sortimplement(TYPE)
minimumimplement(TYPE)
ordered_part_ATTLCimplement(TYPE)
void 
select(
    ptrdiff_t nth,
    TYPE* begin,
    TYPE* end
){
  if (begin >= end || nth <= 0 || end - begin < nth)
    return;

  for (;;)
    if (end - begin < 6)
      {
        ins_sort(begin, end);
        return;
      }
    else if (nth < 4)
      {
        while (nth--)
          {
            register TYPE *r = (TYPE*)minimum(begin, end);
            register TYPE temp = *begin;
            *begin = *r;
            *r = temp;
          }
        return;
      }
    else
      {
        TYPE *index = ordered_part_ATTLC(begin, end);

        if (index - begin >= nth)
          end = index;
        else
          {
            nth -= index - begin;
            begin = index;
          }
      }
} 
PT_end

PT_define select_rimplement(TYPE)
ins_sort_rimplement(TYPE)
minimum_rimplement(TYPE)
ordered_part_r_ATTLCimplement(TYPE)
void 
select_r(
    REL(TYPE)* rel_ptr,
    ptrdiff_t nth,
    TYPE* begin,
    TYPE* end
){
  if (begin >= end || nth <= 0 || end - begin < nth)
    return;

  for (;;)
    if (end - begin < 6)
      {
        ins_sort_r(rel_ptr, begin, end);
        return;
      }
    else if (nth < 4)
      {
        while (nth--)
          {
            register TYPE *r = (TYPE*)minimum_r(rel_ptr, begin, end);
            register TYPE temp = *begin;
            *begin++ = *r;
            *r = temp;
          }
        return;
      }
    else
      {
        TYPE *index = ordered_part_r_ATTLC(rel_ptr, begin, end);

        if (index - begin >= nth)
          end = index;
        else
          {
            nth -= index - begin;
            begin = index;
          }
      }
} 
PT_end

PT_define set_insertimplement(TYPE)
bin_locimplement(TYPE)
copyimplement(TYPE)
TYPE* 
set_insert(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
  TYPE *index = (TYPE*)bin_loc(value, begin, end);

  if (begin < index && !(*(index - 1) < value))
    return 0;

  else
    {
      copy(index, end, index + 1);
      *index = value;
      return index;
    }
} 
PT_end

PT_define set_insert_rimplement(TYPE)
bin_loc_rimplement(TYPE)
copyimplement(TYPE)
TYPE* 
set_insert_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
  TYPE *index = (TYPE*)bin_loc_r(rel_ptr, value, begin, end);

  if (begin < index && !((*rel_ptr)(index - 1, &value) < 0))
    return 0;

  else
    {
      copy(index, end, index + 1);
      *index = value;
      return index;
    }
} 
PT_end

PT_define set_removeimplement(TYPE)
bin_locimplement(TYPE)
copyimplement(TYPE)
TYPE* 
set_remove(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
    TYPE *index = (TYPE*)bin_loc(value, begin, end);

    if(
	begin < index && 
	!(*(index - 1) < value)
    ){
	copy(index, end, index - 1);
	return end-1;
    }else{
	return end;
    }
} 
PT_end

PT_define set_remove_rimplement(TYPE)
bin_loc_rimplement(TYPE)
copyimplement(TYPE)
TYPE* 
set_remove_r(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
    TYPE *index = (TYPE*)bin_loc_r(rel_ptr, value, begin, end);

    if(
	begin < index && 
	!((*rel_ptr)(index - 1, &value) < 0)
    ){
	copy(index, end, index - 1);
	return end-1;
    }else{
	return end;
    }
} 
PT_end

PT_define set_unionimplement(TYPE)
TYPE* 
set_union(
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
    while(begin1 < end1 && begin2 < end2){
	if(*begin2 < *begin1){
	    *result++ = *begin2++;
	}else{
	    if(*begin1 < *begin2){
		*result++ = *begin1++;
	    }else{
		*result++ = *begin2++;
		begin1++;
	    }
	}
    }
    while (begin1 < end1)
	*result++ = *begin1++;

    while (begin2 < end2)
	*result++ = *begin2++;

  return result;
} 
PT_end

PT_define set_union_rimplement(TYPE)
TYPE* 
set_union_r(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    {
      register int c = (*rel_ptr)(begin2, begin1);

      if (c < 0)
        *result++ = *begin2++;
      else
        {
          *result++ = *begin1++;

          if (c == 0)
            begin2++;
        }
    }

  while (begin1 < end1)
    *result++ = *begin1++;

  while (begin2 < end2)
    *result++ = *begin2++;

  return result;
} 
PT_end

PT_define shuffleimplement(TYPE)
randomimplement(TYPE)
void 
shuffle(
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *index = begin + 1;

  while (index < end)
    {
      register TYPE *r = (TYPE*)random(begin, index + 1);
      register TYPE temp = *index;
      *index++ = *r;
      *r = temp;
    }
} 
PT_end

PT_define shuffle_cimplement(TYPE)
randomimplement(TYPE)
void 
shuffle_c(
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register TYPE *result_end = result;

  while (begin < end)
    {
      register TYPE *r = (TYPE*)random(result, result_end + 1);
      *result_end++ = *r;
      *r = *begin++;
    }
} 
PT_end

PT_define ordered_part_ATTLCimplement(TYPE)
randomimplement(TYPE)
static TYPE*
ordered_part_ATTLC(
    register TYPE *begin,
    register TYPE *end
){
  TYPE *old_begin = begin;

  register TYPE value = *random(begin, end);

  begin--;

  for (;;)
    {
      while (*++begin < value);

      while (value < *--end);

      if (begin < end)
        {
          register TYPE temp = *begin;
          *begin = *end;
          *end = temp;
        }
      else
        return (begin == old_begin) ? begin + 1 : begin;
    }
} 
PT_end

PT_define quicksort_loop_ATTLCimplement(TYPE)
ordered_part_ATTLCimplement(TYPE)
static void 
quicksort_loop_ATTLC(
    register TYPE *begin,
    register TYPE *end
){
  while (10 < end - begin)
    {
      register TYPE *index = ordered_part_ATTLC(begin, end);

      if (end - index < index - begin)
        {
          quicksort_loop_ATTLC(index, end);
          end = index;
        }
      else
        {
          quicksort_loop_ATTLC(begin, index);
          begin = index;
        }
    }
} 
PT_end

PT_define sortimplement(TYPE)
ordered_part_ATTLCimplement(TYPE)
quicksort_loop_ATTLCimplement(TYPE)
ins_sortimplement(TYPE)
void 
sort(
    TYPE* begin,
    TYPE* end
){
  quicksort_loop_ATTLC(begin, end);
  ins_sort(begin, end);
} 
PT_end

PT_define ordered_part_r_ATTLCimplement(TYPE)
randomimplement(TYPE)
static TYPE* 
ordered_part_r_ATTLC(
    register REL(TYPE)* rel_ptr,
    register TYPE* begin,
    register TYPE* end
){
  TYPE* old_begin = begin;

  TYPE value = *random(begin, end);

  register TYPE *temp = &value;

  begin--;

  for (;;)
    {
      while ((*rel_ptr)(++begin, temp) < 0);

      while ((*rel_ptr)(temp, --end) < 0);

      if (begin < end)
        {
          register TYPE temp = *begin;
          *begin = *end;
          *end = temp;
        }
      else
        return (begin==old_begin) ? begin + 1 : begin;
    }
} 
PT_end

PT_define quicksort_loop_r_ATTLCimplement(TYPE)
ordered_part_r_ATTLCimplement(TYPE)
static void 
quicksort_loop_r_ATTLC(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
){
  while (10 < end - begin)
    {
      TYPE *index = ordered_part_r_ATTLC(rel_ptr, begin, end);

      if (end - index < index - begin)
        {
          quicksort_loop_r_ATTLC(rel_ptr, index, end);
          end = index;
        }
      else
        {
          quicksort_loop_r_ATTLC(rel_ptr, begin, index);
          begin = index;
        }
    }
} 
PT_end

PT_define sort_rimplement(TYPE)
ordered_part_r_ATTLCimplement(TYPE)
quicksort_loop_r_ATTLCimplement(TYPE)
ins_sort_rimplement(TYPE)
void 
sort_r(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
){
  quicksort_loop_r_ATTLC(rel_ptr, begin, end);
  ins_sort_r(rel_ptr, begin, end);
} 
PT_end

PT_define part_simplement(TYPE)
rotateimplement(TYPE)
TYPE* 
part_s(
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
  if (end - begin > 1)
    {
      TYPE *middle = begin + ((end - begin) >> 1);
      TYPE *first_half = part_s(value, begin, middle);
      TYPE *second_half = part_s(value, middle, end);

      rotate(first_half - middle, first_half, second_half);

      return first_half + (second_half - middle);
    }

  else if (begin < end)

    return *begin == value ? begin + 1 : begin;

  else

    return end;
} 
PT_end

PT_define part_psimplement(TYPE)
rotateimplement(TYPE)
TYPE* 
part_ps(
    PRED(TYPE)* pred_ptr,
    TYPE* begin,
    TYPE* end
){
  if (end - begin > 1)
    {
      TYPE *middle = begin + ((end - begin) >> 1);
      TYPE *first_half = part_ps(pred_ptr, begin, middle);
      TYPE *second_half = part_ps(pred_ptr, middle, end);

      rotate(first_half - middle, first_half, second_half);

      return first_half + (second_half - middle);
    }

  else if (begin < end)

    return (*pred_ptr)(begin) ? begin + 1 : begin;

  else

    return end;
} 
PT_end

PT_define part_rsimplement(TYPE)
rotateimplement(TYPE)
TYPE* 
part_rs(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    TYPE* begin,
    TYPE* end
){
  if (end - begin > 1)
    {
      TYPE *middle = begin + ((end - begin) >> 1);
      TYPE *first_half = part_rs(rel_ptr, value, begin, middle);
      TYPE *second_half = part_rs(rel_ptr, value, middle, end);

      rotate(first_half - middle, first_half, second_half);

      return first_half + (second_half - middle);
    }

  else if (begin < end)

    return ((*rel_ptr)(begin, &value) == 0) ? begin + 1 : begin;

  else

    return end;
} 
PT_end

PT_define part_scimplement(TYPE)
part_cimplement(TYPE)
reverseimplement(TYPE)
TYPE* 
part_sc(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
){
  TYPE *m = part_c(value, begin, end, result);
  reverse(m, result + (end - begin));
  return m;
} 
PT_end

PT_define part_pscimplement(TYPE)
part_pcimplement(TYPE)
reverseimplement(TYPE)
TYPE* 
part_psc(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
){

  TYPE *m = part_pc(pred_ptr, begin, end, result);
  reverse(m, result + (end - begin));
  return m;
} 
PT_end

PT_define part_rscimplement(TYPE)
part_rcimplement(TYPE)
reverseimplement(TYPE)
TYPE* 
part_rsc(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
){
  TYPE *m = part_rc(rel_ptr, value, begin, end, result);
  reverse(m, result + (end - begin));
  return m;
} 
PT_end

PT_define rem_simplement(TYPE)
TYPE* 
rem_s(
    register const TYPE &value,
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *m;

  while (begin < end && !(*begin == value))
    begin++;

  if (begin >= end)
    return end;

  m = begin;

  while (++begin < end)
    if (!(*begin == value))
      *m++ = *begin;

  return m;
} 
PT_end

PT_define rem_psimplement(TYPE)
TYPE* 
rem_ps(
    register PRED(TYPE)* pred_ptr,
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *m;

  while (begin < end && !(*pred_ptr)(begin))
    begin++;

  if (begin >= end)
    return end;

  m = begin;

  while (++begin < end)
    if (!(*pred_ptr)(begin))
      *m++ = *begin;

  return m;
} 
PT_end

PT_define rem_rsimplement(TYPE)
TYPE* 
rem_rs(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register TYPE* begin,
    register TYPE* end
){
  register const TYPE *temp = &value;
  register TYPE *m;

  while (begin < end && (*rel_ptr)(begin, temp) != 0)
    begin++;

  if (begin >= end)
    return end;

  m = begin;

  while (++begin < end)
    if ((*rel_ptr)(begin, temp) != 0)
      *m++ = *begin;

  return m;
} 
PT_end

PT_define rem_scimplement(TYPE)
rem_cimplement(TYPE)
TYPE* 
rem_sc(
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
){
  return rem_c(value, begin, end, result);
} 
PT_end

PT_define rem_pscimplement(TYPE)
rem_pcimplement(TYPE)
TYPE* 
rem_psc(
    PRED(TYPE)* pred_ptr,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
){
  return rem_pc(pred_ptr, begin, end, result);
} 
PT_end

PT_define rem_rscimplement(TYPE)
rem_rcimplement(TYPE)
TYPE* 
rem_rsc(
    REL(TYPE)* rel_ptr,
    const TYPE &value,
    const TYPE* begin,
    const TYPE* end,
    TYPE* result
){
  return rem_rc(rel_ptr, value, begin, end, result);
} 
PT_end

PT_define sort_simplement(TYPE)
ins_sortimplement(TYPE)
merge_sortimplement(TYPE)
void 
sort_s(
    TYPE* begin,
    TYPE* end
){
  TYPE *index = new TYPE[end-begin];

  if (index == 0)
    {
      ins_sort(begin, end);
      return;
    }

  if (merge_sort(begin, end, index) == index)
    {
      TYPE *i = index;

      while (begin < end)
        *begin++ = *i++;
    }
  delete [end-begin]index;
} 
PT_end

PT_define sort_rsimplement(TYPE)
ins_sort_rimplement(TYPE)
merge_sort_rimplement(TYPE)
void 
sort_rs(
    REL(TYPE)* rel_ptr,
    TYPE* begin,
    TYPE* end
){
  TYPE* index = new TYPE[end-begin];

  if (index == 0)
    {
      ins_sort_r(rel_ptr, begin, end);
      return;
    }

  if (merge_sort_r(rel_ptr, begin, end, index) == index)
    {
      TYPE *i = index;

      while (begin < end)
        *begin++ = *i++;
    }
  delete [end-begin]index;
} 
PT_end

PT_define subsimplement(TYPE)
void 
subs(
    register const TYPE &value,
    register TYPE new_value,
    register TYPE* begin,
    register TYPE* end
){
  for (; begin < end; begin++)
    if (*begin == value)
      *begin = new_value;
} 
PT_end

PT_define subs_rimplement(TYPE)
void 
subs_r(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register TYPE new_value,
    register TYPE* begin,
    register TYPE* end
){
  register const TYPE *temp = &value;

  for (; begin < end; begin++)
    if ((*rel_ptr)(begin, temp) == 0)
      *begin = new_value;
} 
PT_end

PT_define subs_cimplement(TYPE)
void 
subs_c(
    register const TYPE &value,
    register TYPE new_value,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  for (; begin < end; begin++)
    *result++ = (*begin == value ? new_value : *begin);
} 
PT_end

PT_define subs_rcimplement(TYPE)
void 
subs_rc(
    register REL(TYPE)* rel_ptr,
    const TYPE &value,
    register TYPE new_value,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  register const TYPE *temp = &value;

  for (; begin < end; begin++)
    *result++ = ((*rel_ptr)(begin, temp) == 0 ? new_value : *begin);
} 
PT_end

PT_define set_sdiffimplement(TYPE)
TYPE* 
set_sdiff(
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    if (*begin1 < *begin2)
      *result++ = *begin1++;
    else if (*begin2 < *begin1)
      *result++ = *begin2++;
    else
      begin1++ ,begin2++;

  while (begin1 < end1)
    *result++ = *begin1++;

  while (begin2 < end2)
    *result++ = *begin2++;

  return result;
} 
PT_end

PT_define set_sdiff_rimplement(TYPE)
TYPE* 
set_sdiff_r(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin1,
    register const TYPE* end1,
    register const TYPE* begin2,
    register const TYPE* end2,
    register TYPE* result
){
  while (begin1 < end1 && begin2 < end2)
    {
      register int c = (*rel_ptr)(begin2, begin1);

      if (0 < c)
        *result++ = *begin1++;
      else if (c < 0)
        *result++ = *begin2++;
      else
        begin1++, begin2++;
    }

  while (begin1 < end1)
    *result++ = *begin1++;

  while (begin2 < end2)
    *result++ = *begin2++;

  return result;
} 
PT_end

PT_define uniqueimplement(TYPE)
TYPE* 
unique(
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *m;

  if (begin >= end)
    return begin;

  while (++begin < end)
    if (*(begin - 1) == *begin)
      break;

  if (begin == end)
    return begin;

  m = begin - 1;

  while (++begin < end)
    if (!(*m == *begin))
      *++m = *begin;

  return m + 1;
} 
PT_end

PT_define unique_rimplement(TYPE)
TYPE* 
unique_r(
    register REL(TYPE)* rel_ptr,
    register TYPE* begin,
    register TYPE* end
){
  register TYPE *m;

  if (begin >= end)
    return begin;

  while (++begin < end)
    if (!(*rel_ptr)(begin - 1, begin))
      break;

  if (begin == end)
    return begin;

  m = begin - 1;

  while (++begin < end)
    if ((*rel_ptr)(m, begin))
      *++m = *begin;

  return m + 1;
} 
PT_end

PT_define unique_cimplement(TYPE)
TYPE* 
unique_c(
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  if (begin >= end)
    return result;

  *result = *begin;

  while (++begin < end)
    if (!(*result == *begin))
      *++result = *begin;

  return result + 1;
} 
PT_end

PT_define unique_rcimplement(TYPE)
TYPE* 
unique_rc(
    register REL(TYPE)* rel_ptr,
    register const TYPE* begin,
    register const TYPE* end,
    register TYPE* result
){
  if (begin >= end)
    return result;

  *result = *begin;

  while (++begin < end)
    if ((*rel_ptr)(result, begin))
      *++result = *begin;

  return result + 1;
} 
PT_end

#endif
