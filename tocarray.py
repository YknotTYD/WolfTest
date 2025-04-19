#!/usr/bin/env python3

from PIL import Image
import numpy as np
import sys

def convert_image_to_array(image_path):

    img = Image.open(image_path)

    if img.mode != 'RGB':
        img = img.convert('RGB')

    img_array = np.array(img)
    height, width, channels = img_array.shape

    print(f"const int IMAGE_WIDTH = {width};")
    print(f"const int IMAGE_HEIGHT = {height};")
    print(f"const unsigned char image_data[{height}][{width}][{channels}] = {{")

    for y in range(height):
        print("    {")
        for x in range(width):
            r, g, b = img_array[y, x]
            print(f"        {{{r}, {g}, {b}}},", end=("" if x < width-1 else "\n"))
        print("    },")
    
    print("};")
    return img_array

if __name__ == "__main__":
    
    image_path = sys.argv[1]
    convert_image_to_array(image_path)
