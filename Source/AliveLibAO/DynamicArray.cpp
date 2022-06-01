#include "stdafx_ao.h"
#include "DynamicArray.hpp"
#include "Function.hpp"
#include "stdlib.hpp"

namespace AO {

DynamicArray::DynamicArray(s32 startingSize)
{
    const auto sizeInBytes = startingSize * sizeof(void*);
    field_0_array = reinterpret_cast<void**>(alloc_450740(sizeInBytes));

    if (field_0_array)
    {
        memset(field_0_array, 0, sizeInBytes);
        field_6_max_size = static_cast<s16>(startingSize);
        field_8_expand_size = 10;
    }
}

DynamicArray::~DynamicArray()
{
    ao_delete_free_450770(field_0_array);
}

s16 DynamicArray::Push_Back(void* item)
{
    if (!item || !field_0_array)
    {
        return 0;
    }

    if (field_4_used_size == field_6_max_size)
    {
        // Inlined expand call?
        const s16 newSizeElements = field_6_max_size + field_8_expand_size;
        const auto newArraySizeBytes = newSizeElements * sizeof(void*);
        auto pNewArray = reinterpret_cast<void**>(alloc_450740(newArraySizeBytes));
        if (!pNewArray)
        {
            return 0;
        }

        // Clear new memory + copy in old array
        memset(pNewArray, 0, newArraySizeBytes);
        memcpy(pNewArray, field_0_array, field_4_used_size * sizeof(void*));

        // Free old array + assign new values
        ao_delete_free_450770(field_0_array);
        field_0_array = pNewArray;
        field_6_max_size = newSizeElements;
    }

    field_0_array[field_4_used_size++] = item;
    return 1;
}

s16 DynamicArray::Remove_Item(void* item)
{
    for (s16 idx = 0; idx < field_4_used_size; idx++)
    {
        void* pCurrentItem = field_0_array[idx];
        if (!pCurrentItem)
        {
            break;
        }

        if (pCurrentItem == item)
        {
            field_4_used_size--;

            // Overwrite the items to remove with the item from the end
            field_0_array[idx] = field_0_array[field_4_used_size];
            return 1;
        }
    }
    return 0;
}

} // namespace AO
