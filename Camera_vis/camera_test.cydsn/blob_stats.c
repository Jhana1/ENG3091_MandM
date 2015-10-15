#include <stdlib.h>
#include <project.h>
#include <my_camera_functions.h>

#define NUMBER_OF_BLOBS 255
#define PIXELS_FROM_CENTRE 4

typedef struct
{
    int colour;
    uint16 size;
    uint32 x_sum,y_sum;
} blob;

blob blobs[NUMBER_OF_BLOBS];

int blob_comp(const void *a, const void *b);

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
