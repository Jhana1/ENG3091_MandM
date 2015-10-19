#include <stdlib.h>
#include <project.h>
#include <my_camera_functions.h>
#include <blob_stats.h>

#define NUMBER_OF_BLOBS 255
#define PIXELS_FROM_CENTRE 4

//typedef struct
//{
//    int colour;
//    uint16 size;
//    uint32 x_sum,y_sum;
//} blob;

blob blobs[NUMBER_OF_BLOBS];

//int blob_comp(const void *a, const void *b);
//int blob_pos_sort(const void *a, const void *b);

void blob_detect()
{
	int labels[88];
	int x,y,keep,drop,colour,current_available_label = 0;
    int i;
	memset(blobs,0,sizeof(blobs));
	memset(labels,-1,sizeof(labels));
	for(y = 1; y < 144; y++)
	{
		for(x = 1; x < 88; x++)
		{
			if(PixelColour(x,y) == NONE)
			{
				labels[x] = -1;
			}
			else if(PixelColour(x,y) == PixelColour(x-1,y))
			{
				if(PixelColour(x,y) == PixelColour(x,y-1) && labels[x] != labels[x-1])
				{
					keep = labels[x-1];
					drop = labels[x];

					//Merge Blobs
					blobs[labels[x-1]].size += blobs[labels[x]].size;
					blobs[labels[x-1]].x_sum += blobs[labels[x]].x_sum;
					blobs[labels[x-1]].y_sum += blobs[labels[x]].y_sum;

					//Drop Blob
					blobs[labels[x]].colour = NONE;
					blobs[labels[x]].size = 0;
					blobs[labels[x]].x_sum = 0;
					blobs[labels[x]].y_sum = 0;
					for(i = x; i < 88; i++)
					{
						if(labels[i] == drop)
						{
							labels[i] = keep;
						}
					}
				}
				labels[x] = labels[x-1];
			}
			else if(PixelColour(x,y) == PixelColour(x,y-1))
			{
				// Same as above, but not to the left. An "Edge"
				labels[x] = labels[x];
			}
			else
			{
				//New Label
				labels[x] = current_available_label++;
			}
			if(labels[x] != -1)
			{
				blobs[labels[x]].colour = PixelColour(x,y);
				blobs[labels[x]].size++;
				blobs[labels[x]].x_sum += x;
				blobs[labels[y]].y_sum += (y^2);
			}
		}
	}
    // THE MOST IMPORTANT LINE IN BLOB STATS
    qsort(blobs,NUMBER_OF_BLOBS,sizeof(blob),blob_comp);           
}

uint16 blob_count(int size)
{
	uint16 count = 0; 
    int i;
	for(i = 0; i < NUMBER_OF_BLOBS; i++)
	{
		if(blobs[i].size >= size)
		{
			count++;
		}
	}
	return count;
}

int blob_comp(const void *a, const void *b)
{
    blob b1 = *((blob *) a);
    blob b2 = *((blob *) b);
    
    if(b1.size > b2.size)
    {
        return -1;
    }
    else if(b2.size > b1.size)
    {
        return 1;
    }
    else return 0;
}

int to_nearest_blob(int colour,int size,int centre_threshold,int centre_pixel)
{
     // 0 center, + => Blob to Right, - => Blob to Left, -1 No blobs big enough

    int cx, cy, i;
    for(i = 0; i < 255; i++)
    {
        if(blobs[i].size < size)
        {
            return -1;
        }
        if(blobs[i].colour == colour)
        {
            cx = blobs[i].x_sum/blobs[i].size;
            cy = blobs[i].y_sum/blobs[i].size;
            Camera_framebuffer[cy][cx][0] = 255;
            Camera_framebuffer[cy][cx][2] = 255;
            if((cx - centre_pixel) >= -centre_threshold && (cx- 44 - centre_pixel) <= centre_threshold)
            {
                return 0;
            }
            else
            {
            	return cx-44;
            }
        }
    }
    return -1;
}

uint8 size_of_biggest_colour(int colour)
{
    int i;
    for(i = 0; i < 255; i++)
    {
        if(blobs[i].colour == colour)
        {
            return blobs[i].size;   
        }
    }
    return 0;
}

int get_blob(int position, int size)
{
    int i = 0, count = 0;
    for(i = 0; i < 255; i++)
    {
        if(blobs[i].size > size)
        {
            if(count == position)
            {
                return blobs[i].colour;
            }
            else
            {
                count++;
            }
        }
    }
}

void blob_instruction_read()
{
    int i, j;
//    int cx0 = blobs[0].x_sum/blobs[0].size;
//    int cx1 = blobs[1].x_sum/blobs[1].size;
//    int cx2 = blobs[2].x_sum/blobs[2].size;
//    int cx3 = blobs[3].x_sum/blobs[3].size;
//    int cx[] = {cx0, cx1, cx2, cx3};
//    int indexes[4];
//    for(i = 0; i < 4; i++){
//        int current_max = 0;
//        int current_j = 0;
//        for (j = 0; j < 4; j++){
//            if (cx[j] > current_max){
//                current_max = cx[j];
//                current_j = j;
//            }
//        }
//        indexes[i] = current_j;
//        cx[j] = 0;
//    }
    instruction_blob_stuff();
}

void instruction_blob_stuff()
{
     // 0 center, + => Blob to Right, - => Blob to Left, -1 No blobs big enough
    int cx, cy, i;
    int c[4],ind[4], min = 10000;
    for(i = 0; i < 4; i++)
    {
        cx = blobs[i].x_sum/blobs[i].size;
        cy = blobs[i].y_sum/blobs[i].size;
        Camera_framebuffer[cy][cx][0] = 255;
        Camera_framebuffer[cy][cx][2] = 255;
        c[i] = cx;
        s[i] = 1000;
    }
    for(i = 0; i < 4; i++)
    {
        if(c[i] < s[0])
        {
            ind[0] = i;
            s[0] = c[i];
        }
    }
    for(i = 0; i < 4; i++)
    {   
        if(c[i] > s[0] && c[i] < s[1])
        {
            ind[1] = i;
            s[1] = c[i];
        }
    }
    for(i = 0; i < 4; i++)
    {
        if(c[i] > s[1] && c[i] < s[2])
        {
            ind[2] = i;
            s[2] = c[i];
        }
    }
    for(i = 0; i < 4; i++)
    {
        if(c[i] > s[2])
        {
            ind[3] = i;
            s[2] = c[i];
        }
    }
    for(i = 0; i < 4; i++)
    {
        stack[i] = blobs[ind[i]].colour;
    }
}