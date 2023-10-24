#include "chain_decode.h"

#include <stdio.h>

#include <stdlib.h>
#include "pico/stdlib.h"
#include "consts.h"
#include "varint.h"

// Function to initialize the frame buffer
void initialize_frame_buffer(uint16_t *frame_buffer, uint16_t color)
{
    int num_pixels = WIDTH * HEIGHT;

    for (int i = 0; i < num_pixels; i++)
    {
        frame_buffer[i] = color;
    }
}

// Function to read the delimiter value and determine the color
uint16_t read_delimiter_value(unsigned char byte)
{
    return (byte & ~DELIMITER) != 0 ? WHITE : BLACK;
}

void process_nibble(unsigned char nibble, unsigned int *x, unsigned int *y)
{
    // why is this flipped????
    if (nibble & N)
        (*x)--;
    if (nibble & E)
        (*y)++;
    if (nibble & S)
        (*x)++;
    if (nibble & W)
        (*y)--;
}

// Function to set a pixel on the frame buffer
void set_pixel(uint16_t *frame_buffer, unsigned int x, unsigned int y, uint16_t color)
{
    if (x < WIDTH && y < HEIGHT)
    {
        frame_buffer[y * WIDTH + x] = color;
    }
    else
    {
        printf("oob, x %u, y %u", x, y);
    }
}

// Function to decode the chain coded frame
void decode_chain_coded_frame(const unsigned char *encodedData, unsigned long long length, uint16_t *frame_buffer)
{
    const unsigned char *ptr = encodedData;
    unsigned long long bytes_processed = 0;
    unsigned char bytes_read;

    // Read background color and initialize frame buffer
    uint16_t bgColor = read_delimiter_value(*ptr);
    initialize_frame_buffer(frame_buffer, bgColor);
    ptr++;
    bytes_processed++;

    // Dynamic array for contour points
    Point *contourPoints = NULL;
    unsigned int numPoints = 0;
    unsigned int contours = 0;

    while (bytes_processed < length)
    {
        // Decode the starting positions
        unsigned long long startX = varint_decode(ptr, length - bytes_processed, &bytes_read);
        ptr += bytes_read;
        bytes_processed += bytes_read;

        unsigned long long startY = varint_decode(ptr, length - bytes_processed, &bytes_read);
        ptr += bytes_read;
        bytes_processed += bytes_read;

        // Reset contour points and add the starting point
        free(contourPoints);
        contourPoints = NULL;
        numPoints = 0;
        contourPoints = (Point *)malloc(sizeof(Point));
        contourPoints[0].x = startX;
        contourPoints[0].y = startY;
        numPoints++;

        while (bytes_processed < length)
        {
            char dataByte = *ptr;
            ptr++;
            bytes_processed++;

            if ((dataByte & DELIMITER) == DELIMITER)
            {
                contours++;

                uint16_t contourColor = read_delimiter_value(dataByte);
                // Process the contour points
                if (numPoints == 1)
                {
                    set_pixel(frame_buffer, contourPoints[0].x, contourPoints[0].y, contourColor);
                }
                else
                {
                    // Draw the polygon (for now, let's just draw the outline)
                    for (unsigned int i = 0; i < numPoints; i++)
                    {
                        set_pixel(frame_buffer, contourPoints[i].x, contourPoints[i].y, contourColor);
                    }
                }

                break;
            }

            char highNibble = (dataByte & 0xF0) >> 4;
            char lowNibble = dataByte & 0x0F;

            // Process and store the points for high and low nibbles
            Point lastPoint = contourPoints[numPoints - 1];
            process_nibble(highNibble, &lastPoint.x, &lastPoint.y);
            contourPoints = (Point *)realloc(contourPoints, (numPoints + 1) * sizeof(Point));
            contourPoints[numPoints] = lastPoint;
            numPoints++;

            lastPoint = contourPoints[numPoints - 1];
            process_nibble(lowNibble, &lastPoint.x, &lastPoint.y);
            contourPoints = (Point *)realloc(contourPoints, (numPoints + 1) * sizeof(Point));
            contourPoints[numPoints] = lastPoint;
            numPoints++;
        }
    }
    free(contourPoints);
}
