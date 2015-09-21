/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef MY_BLOB_STATS
    #include <project.h>
    
    void blob_detect();
    uint16 blob_count(int);
    int blob_comp(const void *a, const void *b);
    int to_nearest_blob(int colour, int size);
    
    
    typedef struct
    {
        int colour;
        uint32 size;
        uint32 x_sum,y_sum;
    } blob;

    
#endif
/* [] END OF FILE */
