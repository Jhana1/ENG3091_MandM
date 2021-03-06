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
    void blob_instruction_read();
    int get_blob(int position, int size);
    int blob_pos_sort(const void *a, const void *b);
    uint16 blob_count(int);
    int blob_comp(const void *a, const void *b);
    int to_nearest_blob(int colour, int size, int centre_threshold, int centre_pixel);
    uint8 size_of_biggest_colour(int colour);
    void instruction_blob_stuff();
    
    int s[4];
    
    typedef struct
    {
        int colour;
        uint32 size;
        uint32 x_sum,y_sum;
    } blob;

    
#endif
/* [] END OF FILE */
