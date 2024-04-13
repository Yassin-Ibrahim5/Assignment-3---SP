// Authors: Mazen Ahmed Mohamed ElShazly - Resizing, Color Inversion, Frame, Infrared - 20230579
// Authors: Yassin Ibrahim Samir Hafez Mohamed - Black & White, Flip Horizontally/Vertically, Merge, Edge Detection, Sunlight - 20230463
// Authors: Ziyad Mohamed Ahmed ElHawary - Grayscale, Darken/Brighten, Blur, Rotate, Purple - 20230564
// Date: 10/4/2024
// Section number: 2
#include "Image_Class.h"
#include <stdexcept>
using namespace std;
// This function converts the input image to grayscale and saves the result to a new file
void greyscale(Image image)
{
    // Iterate over all pixels in the image
    for (int i = 0; i < image.width; ++i)
    {

        for (int j = 0; j < image.height; ++j)
        {
            unsigned int average = 0;
            for (int k = 0; k < 3; ++k) // each pixel has three channels: red, green, and blue
            {
                average = average + image(i, j, k);
            }
            // Divide the sum by 3 to get the average
            average = average / 3;
            image(i, j, 0) = average;
            image(i, j, 1) = average;
            image(i, j, 2) = average;
        }
    }

    // Prompt the user for a file name and save the grayscale image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    image.saveImage(file_name);
}
// This function converts the input image to black and white (binary)
// and saves the result to a new file
void black_and_white(Image image)
{
    // Iterate over all pixels in the image
    for (int i = 0; i < image.width; ++i)
    {

        for (int j = 0; j < image.height; ++j)
        {
            unsigned int average = 0;
            for (int k = 0; k < 3; ++k) // each pixel has three channels: red, green, and blue
            {
                average = average + image(i, j, k);
            }
            // Divide the sum by 3 to get the average
            average = average / 3;
            if (average < 125)
            {
                // If the average value is less than 125, set the pixel to black
                average = 0;
            }
            else
            {
                // Otherwise, set the pixel to white
                average = 255;
            }
            // Update the color channels of the image
            image(i, j, 0) = average;
            image(i, j, 1) = average;
            image(i, j, 2) = average;
        }
    }

    // Prompt the user for a file name and save the black and white image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    image.saveImage(file_name);
}
// This function takes an image and inverts the colors of each pixel
// in the image by subtracting the color value from 255.
// The function then prompts the user for a file name and saves the
// inverted image to a new file using the Image class's saveImage() function.
void invert_colors(Image image)
{
    // Iterate over all pixels in the image
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k) // each pixel has three channels: red, green, and blue
            {
                // Subtract the color value from 255 to invert the color
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

    // Prompt the user for a file name and save the inverted image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    image.saveImage(file_name);
}// This function flips the input image horizontally
void flip_horizontally(Image image)
{
    // Create a new image with the same dimensions as the input image
    Image final_image(image.width, image.height);

    // Iterate through each pixel in the new image
    for (int i = 0; i < final_image.width; ++i)
    {
        for (int j = 0; j < final_image.height; ++j)
        {
            // Copy the color values to the corresponding location in the new image
            // but flip it horizontally
            for (int k = 0; k < 3; ++k)
            {
                final_image(i, j, k) = image(image.width - i, j, k);
            }
        }
    }

    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin >> file_name;
    // Save the flipped image to the specified file
    final_image.saveImage(file_name);
}
// This function flips the input image vertically
void flip_vertically(Image image)
{
    // Create a new image with the same dimensions as the input image
    Image final_image(image.width, image.height);

    // Iterate through each pixel in the original image
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            // Copy the color values to the corresponding location in the new image
            // but flip it vertically
            for (int k = 0; k < 3; ++k)
            {
                final_image(i, image.height - 1 - j, k) = image(i, j, k);
            }
        }
    }

    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin >> file_name;
    // Save the flipped image to the specified file
    final_image.saveImage(file_name);
}
// This function darkens the input image by a specified factor
void darken(Image image, const float factory /* = -0.5 */)
{
    // Create a new image with the same dimensions as the input image
    Image new_image(image.width, image.height);

    // Iterate through each pixel in the input image
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            // Iterate through the color channels
            for (int k = 0; k < 3; ++k)
            {
                // Calculate the new color value by multiplying the input color value with the specified factor
                int new_pixel = (int)(image(i, j, k) * factory);
                // Make sure the new pixel value is within the range [0, 255]
                new_pixel = min(max(new_pixel, 0), 255);
                // Assign the new pixel value to the new image
                new_image(i, j, k) = new_pixel;
            }
        }
    }

    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin >> file_name;
    // Save the darkened image to the specified file
    new_image.saveImage(file_name);
}
// This function lightens the input image by a specified factor
void lighten(Image image, const float factor /* = 0.5 */)
{
    // Create a new image with the same dimensions as the input image
    Image new_image(image.width, image.height);

    // Iterate through each pixel in the input image
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            // Iterate through the color channels
            for (int k = 0; k < 3; ++k)
            {
                // Calculate the new color value by multiplying the input color value with the specified factor
                int new_pixel = (int)(image(i, j, k) * factor);
                // Make sure the new pixel value is within the range [0, 255]
                new_pixel = min(max(new_pixel, 0), 255);
                // Assign the new pixel value to the new image
                new_image(i, j, k) = new_pixel;
            }
        }
    }

    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin >> file_name;
    // Save the lightened image to the specified file
    new_image.saveImage(file_name);
}
// This function resizes the input image to the specified width and height
void resize_pic(Image image, int width, int height) {
    double r1 = (double)image.width / width;
    double r2 = (double)image.height / height;

    // Create a new image with the desired dimensions
    Image image2(width, height);

    // Iterate through each pixel in the new image
    for (int i = 0; i < image2.width; ++i)
    {
        for (int j = 0; j < image2.height; ++j)
        {
            // Calculate the corresponding location in the original image
            double x = i * r1;
            double y = j * r2;

            // Iterate through the color channels
            for (int k = 0; k < image2.channels; ++k)
            {
                // Round the color value and assign it to the corresponding pixel
                image2(i, j, k) = round(image(x, y, k));
            }
        }
    }

    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin >> file_name;
    // Save the resized image to the specified file
    image2.saveImage(file_name);
}//w h must be int
void crop_pic(Image image, int start1, int start2, int width, int height) {
    // Create a new image with the desired dimensions
    Image image2(width, height);
    // Iterate through each pixel in the new image
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // Calculate the corresponding location in the original image
            int x = i + start1 ;
            int y = j + start2 ;

            // Iterate through the color channels
            for (int k = 0; k < image2.channels; ++k)
            {
                // Round the color value and assign it to the corresponding pixel
                image2(i, j, k) = image(x, y, k);
            }
        }
    }
    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin>> file_name;
    // Save the resized image to the specified file
    image2.saveImage(file_name);
}
void blur(Image image, int box_size) {
    Image temp_image(image.width, image.height);
    double r1 = (double) image.width / 300;
    double r2 = (double) image.height / 300;
    // Create a new image with the desired dimensions
    Image image2(300, 300);
    // Iterate through each pixel in the new image
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            // Calculate the corresponding location in the original image
            double x = i * r1;
            double y = j * r2;

            // Iterate through the color channels
            for (int k = 0; k < image2.channels; ++k) {
                // Round the color value and assign it to the corresponding pixel
                image2(i, j, k) = round(image(x, y, k));
            }
        }
    }
    box_size = max(box_size, 5);
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {

            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            int count = 0;
            for (int m = i - box_size / 2; m <= i + box_size / 2; ++m) {
                for (int n = j - box_size / 2; n <= j + box_size / 2; ++n) {
                    if (m >= 0 && m < image2.width && n >= 0 && n < image2.height) {
                        sum_r += image2(m, n, 0);
                        sum_g += image2(m, n, 1);
                        sum_b += image2(m, n, 2);
                        count++;
                    }
                }
            }
            int avg_r = sum_r / count;
            int avg_g = sum_g / count;
            int avg_b = sum_b / count;
            temp_image(i, j, 0) = min(255, max(0, avg_r));
            temp_image(i, j, 1) = min(255, max(0, avg_g));
            temp_image(i, j, 2) = min(255, max(0, avg_b));
        }
    }
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            image2(i, j, 0) = temp_image(i, j, 0);
            image2(i, j, 1) = temp_image(i, j, 1);
            image2(i, j, 2) = temp_image(i, j, 2);
        }
    }
    double R1 = (double) image2.width / image.width;
    double R2 = (double) image2.height / image.height;
    // Create a new image with the desired dimensions
    Image image3(image.width, image.height);
    // Iterate through each pixel in the new image
    for (int i = 0; i < image3.width; ++i) {
        for (int j = 0; j < image3.height; ++j) {
            // Calculate the corresponding location in the original image
            double x = i * R1;
            double y = j * R2;

            // Iterate through the color channels
            for (int k = 0; k < image3.channels; ++k) {
                // Round the color value and assign it to the corresponding pixel
                image3(i, j, k) = round(image2(x, y, k));
            }
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg,.bmp,.png,.tga) >>";
    cin >> file_name;
    image3.saveImage(file_name);
}
void frame_pic(Image image, int r, int g, int b) {
    // Top Horizontal line
    for (int k = image.width*0.02; k < image.width - image.width*0.02; ++k){
        for (int l = image.width * 0.01; l < image.width * 0.026 ; ++l){
            for (int s = 0; s < image.channels; ++s){
                image(k, l, 0) = r;
                image(k, l, 1) = g;
                image(k, l, 2) = b;
            }
        }
    }
    // Left Vertical Row
    for (int k = image.width *0.01; k < image.width * 0.026 ; ++k){
        for (int l = image.width *0.01; l < image.height -image.width * 0.01 ; ++l){
            for (int s = 0; s < image.channels; ++s){
                image(k, l, 0) = r;
                image(k, l, 1) = g;
                image(k, l, 2) = b;
            }
        }
    }
    // Bottom Horizontal Line
    for (int k = image.width*0.02 ; k < image.width - image.width*0.02; ++k){
        for (int l = image.height - image.width * 0.026; l < image.height - image.width * 0.01 ; ++l){
            for (int s = 0; s < image.channels; ++s){
                image(k, l, 0) = r;
                image(k, l, 1) = g;
                image(k, l, 2) = b;
            }
        }
    }
    // Right Vertical Line
    for (int k = image.width -image.width * 0.026; k < image.width - image.width * 0.01; ++k){
        for (int l = image.width *0.01; l < image.height - image.width *0.01 ; ++l){
            for (int s = 0; s < image.channels; ++s){
                image(k, l, 0) = r;
                image(k, l, 1) = g;
                image(k, l, 2) = b;
            }
        }
    }

    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin >> file_name;
    // Save the resized image to the specified file
    image.saveImage(file_name);
}//rgb values must be int between 0 and 255
void purple_pic(Image image) {

    // Iterate through each pixel in the new image
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            // Iterate through the color channels
            for (int k = 0; k < image.channels; ++k)
            {

                image(i,j,0) = image(i,j,0) ;
                image(i,j,1) = (image(i,j,1)+23)/1.48 ;
                image(i,j,2) = image(i,j,2);
            }
        }
    }

    // Prompt the user to enter a filename for the new image
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    // Get the filename input by the user
    cin>> file_name;
    // Save the resized image to the specified file
    image.saveImage(file_name);
}
void detect_edges(Image image)
{
    // Turn the image greyscale before starting edge detection (to make detecting varying intensities easier)
    Image image2(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image.getPixel(i, j, k);
            }
            avg /= 3;
            image.setPixel(i, j, 0, avg);
            image.setPixel(i, j, 1, avg);
            image.setPixel(i, j, 2, avg);
        }
    }
    image2 = image;
    // Initialize the gradient matrices for the x and y-axis used for Sobel Edge detection
    int Gx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    int Gy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };
    Image image3(image.width, image.height);
    double magnitude;
    // Loop over the pixels of the image starting at (1,1) to get the 8 adjacent pixels
    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {
            int sumX = 0, sumY = 0;
            for (int k = 0; k < 3; ++k) {
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        int pixelX = x + i;
                        int pixelY = y + j;
                        // Multiply the pixel in the image to its corresponding element in the gradient matrix (x or y)
                        sumX += image2.getPixel(pixelX, pixelY, k) * Gx[x + 1][y + 1];
                        sumY += image2.getPixel(pixelX, pixelY, k) * Gy[x + 1][y + 1];
                    }
                }
                // To get the final color value of the pixel, add the pixel in the x and y squared and take the square root of the result
                magnitude = sqrt(sumX * sumX + sumY * sumY);
                image3.setPixel(i, j, k, (magnitude > 255 ? 255 : magnitude));
            }
        }
    }
    // Loop over the resulting image removing any color that isn't black or white by making it black for isolated edges
    for (int i = 0; i < image3.width; ++i)
    {
        for (int j = 0; j < image3.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (image3(i, j, k) != 255 && image3(i, j, k) != 0)
                {
                    image3(i, j, k) = 0;
                }
            }
        }
    }
    Image final(image.width, image.height);
    // Turn the image black and white and invert the black and the white
    for (int i = 0; i < image3.width; ++i)
    {
        for (int j = 0; j < image3.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
            {
                avg += image3(i, j, k);
            }
            avg /= 3;
            if (avg < 126)
            {
                avg = 0;
            }else
            {
                avg = 255;
            }
            final(i, j, 0) = avg;
            final(i, j, 1) = avg;
            final(i, j, 2) = avg;
            final(i, j, 0) = 255 - final(i, j, 0);
            final(i, j, 1) = 255 - final(i, j, 1);
            final(i, j, 2) = 255 - final(i, j, 2);
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    final.saveImage(file_name);
}
void infrared(Image image)
{
    Image image2(image.width, image.height);
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    image2 = image;
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            image2(i, j, 0) = (image(i, j, 0) + 255) /2;
            image2(i, j, 1) = (255 - image2(i, j, 1)) / 1.2;
            image2(i, j, 2) = (255 - image2(i, j, 2)) / 1.2;
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    image2.saveImage(file_name);
}
void sunlight(Image image)
{
    Image final_image(image.width, image.height);
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            final_image(i, j, 0) = image(i, j, 0);
            final_image(i, j, 1) = image(i, j, 1);
            final_image(i, j, 2) = (image(i, j, 2) + 70) / 2;
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    final_image.saveImage(file_name);
}
void merge(Image image1, Image image2)
{
    int width, height;
    if (image1.width > image2.width)
    {
        width = image2.width;
    }else
    {
        width = image1.width;
    }
    if (image1.height > image2.height)
    {
        height = image2.height;
    } else
    {
        height = image1.height;
    }
    double r1 = width, r2 = height;
    Image image1_resized(width, height);
    Image image2_resized(width, height);
    r1 /= width;
    r2 /= height;
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image1_resized(i, j, k) = round(image1(i * r1, j * r2, k));
            }
        }
    }
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image2_resized(i, j, k) = round(image2(i * r1, j * r2, k));
            }
        }
    }
    Image merged(width, height);
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (j % 2 == 0)
                {
                    merged(i, j, k) = image1_resized(i, j, k);
                }
                else
                {
                    merged(i, j, k) = image2_resized(i, j, k);
                }
            }
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    merged.saveImage(file_name);
}
void rotate90(Image image)
{
    int new_width = image.height, new_height = image.width;
    Image image2(new_width, new_height);
    Image final_image(new_width, new_height);
    for (int i = 0; i < image.height; ++i)
    {
        for (int j = 0; j < image.width; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image2(i, j, k) = image(j, i, k);
            }
        }
    }
    for (int i = 0; i < final_image.width; ++i)
    {
        for (int j = 0; j < final_image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                final_image(i, j, k) = image2(image2.width - i, j, k);
            }
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    final_image.saveImage(file_name);
}
void rotate180(Image image)
{
    Image image2(image.width, image.height);
    Image final_image(image.width, image.height);
    for (int i = 0; i < image2.width; i++)
    {
        for (int j = 0; j < image2.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                image2(i, j, k) = image(i, image2.height - 1 - j, k);
            }
        }
    }
    for (int i = 0; i < final_image.width; i++)
    {
        for (int j = 0; j < final_image.height; j++)
        {
            for (int k = 0; k < final_image.channels; k++)
            {
                final_image(i, j, k) = image2(image.width - i, j, k);
            }
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    final_image.saveImage(file_name);
}
void rotate270(Image image)
{
    int new_width = image.height, new_height = image.width;
    Image final_image(new_width, new_height);
    Image image2(new_width, new_height);
    for (int i = 0; i < image.height; ++i)
    {
        for (int j = 0; j < image.width; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image2(i, j, k) = image(j, i, k);
            }
        }
    }
    for (int i = 0; i < final_image.width; i++)
    {
        for (int j = 0; j < final_image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                final_image(i, j, k) = image2(i, image2.height - 1 - j, k);
            }
        }
    }
    string file_name;
    cout << "Please enter a name for the new file with a valid extension (.jpg, .bmp, .png, .tga) >>";
    cin >> file_name;
    final_image.saveImage(file_name);
}
void menu()
{
    while (true)
    {
        cout << "1) Greyscale Image\n2) Black and White Image\n3) Color Inversion\n4) Flip Horizontally or Vertically\n5) Darken or Brighten an Image\n6) Resize Image\n7) Crop Image\n8) Blur Image\n9) Frame Pic\n10) Purple Filter\n11) Detect Edges\n12) Infrared\n13) Add Natural Sunlight\n14) Merge 2 Images\n15) Rotate\n16) Exit\n";
        string choice1;
        cin >> choice1;
        while (choice1 != "1" && choice1 != "2" && choice1 != "3" && choice1 != "4" && choice1 != "5" && choice1 != "6" && choice1 != "7" && choice1 != "8" && choice1 != "9" && choice1 != "10" && choice1 != "11"&& choice1 != "12" &&choice1 != "13" &&choice1 != "14" &&choice1 != "15" &&choice1 != "16")
        {
            cout << "Invalid input. Please enter a valid choice >>" << endl;
            cout << "1) Greyscale Image\n2) Black and White Image\n3) Color Inversion\n4) Flip Horizontally or Vertically\n5) Darken or Brighten an Image\n6) Resize Image\n7) crop\n8)Blur \n9)Frame Pic \n10)Purple Filter \n11)Detect Edges \n12)Infrared \n13)Sunlight \n14)Merge \n15)Rotate \n16)Exit \n";
            cin >> choice1;
        }
        if (choice1 == "16")
        {
            break;
        }
        while (choice1 == "1")
        {
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            //sets the image value to the name entered by the user
            Image image(image_name);
            //calls the grey scale function
            greyscale(image);
            menu();
        }
        if (choice1 == "2")
        {
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            //calls the black and white function
            black_and_white(image);
            menu();
        }
        if (choice1 == "3")
        {
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            invert_colors(image);
            menu();
        }
        if (choice1 == "4")
        {
            string choice2;
            cout << "Enter whether you want to flip horizontally or vertically >>\n";
            cout << "1) Horizontally\n2) Vertically\n";
            cin >> choice2;
            while (choice2 != "1" && choice2 != "2")
            {
                cout << "Invalid input. Please enter a valid choice >>\n";
                cout << "Enter whether you want to flip horizontally or vertically >>\n";
                cout << "1) Horizontally\n2) Vertically\n";
                cin >> choice2;
            }
            if (choice2 == "1")
            {
                cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
                string image_name;
                cin >> image_name;
                Image image(image_name);
                //calls the flip horizontally function
                flip_horizontally(image);
                menu();
            }
            if (choice2 == "2")
            {
                cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
                string image_name;
                cin >> image_name;
                Image image(image_name);
                //calls the flip vertically function
                flip_vertically(image);
                menu();
            }
        }
        if (choice1 == "5")
        {
            string choice2;
            cout << "Enter whether you want to darken or lighten an image >>\n";
            cout << "1) Darken\n2) Lighten\n";
            cin >> choice2;
            while (choice2 != "1" && choice2 != "2")
            {cout << "Invalid input. Please enter a valid choice >>\n";
                cout << "Enter whether you want to darken or lighten an image >>\n";
                cout << "1) Darken\n2) Lighten\n";
                cin >> choice2;
            }
            if (choice2 == "1")
            {
                cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
                string image_name;
                cin >> image_name;
                Image image(image_name);
                //calls the darken function
                darken(image, 0.5);
                menu();
            }
            if (choice2 == "2")
            {
                cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
                string image_name;
                cin >> image_name;
                Image image(image_name);
                //calls the lighten function
                lighten(image, 1.5);
                menu();
            }
        }
        if (choice1 == "6")
        {
            int width;
            int height;
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            cout << "Enter width >>";
            cin >> width;
            cout << "Enter height >>";
            cin >> height;
            //calls the resize function
            resize_pic(image, width, height);
            menu();
        }
        if (choice1 == "7"){
            int start1;
            int start2;
            int width;
            int height;
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            cout << "Enter starting points >>";
            cin >> start1 >> start2;
            while (start1 > image.width || start2 > image.height)
            {
                cout << "Starting point must be within the image dimensions" << endl;
                cout << "Enter starting point >>";
                cin >> start1 >> start2;
            }
            cout << "Enter width >>";
            cin >> width;
            cout << "Enter height >>";
            cin >> height;
            //calls the crop function
            crop_pic(image_name,start1,start2,width,height);
            menu();
        }
        if (choice1 == "8"){
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);

            //calls the crop function
            blur(image_name, 8);
            menu();
        }
        if (choice1 == "9"){
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            int r,g,b;
            cin >> image_name;
            cout<<"Enter Frame RGB values:";
            cin >> r >> g >> b;
            Image image(image_name);
            //calls the crop function
            frame_pic(image_name, r, g, b);
            menu();
        }
        if (choice1 == "10"){
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            //calls the purple function
            purple_pic(image_name);
            menu();
        }
        if (choice1 == "11"){
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            //calls the detect edge function
            detect_edges(image_name);
            menu();
        }
        if (choice1 == "12"){
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            //calls the infrared function
            infrared(image_name);
            menu();
        }
        if (choice1 == "13"){
            cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image_name;
            cin >> image_name;
            Image image(image_name);
            //calls the sunlight function
            sunlight(image_name);
            menu();
        }
        if (choice1 == "14"){
            cout << "Enter the name of the first image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            string image1_name,image2_name;
            cin >> image1_name;
            Image image(image1_name);
            cout << "Enter the name of the second image with a valid extension (.jpg, .bmp, .png, .tga) >>";
            cin>>image2_name;
            Image image2(image2_name);
            //calls the merge function
            merge(image1_name,image2_name);
            menu();
        }
        if (choice1 == "15"){
            string choice2;
            cout<<"Choose Rotate Degree \n";
            cout<<"1) Rotate 90 \n2) Rotate 180 \n3) Rotate 270 \n";
            cin >> choice2;
            while (choice2 != "1" && choice2 != "2" && choice2 != "3")
            {cout << "Invalid input. Please enter a valid choice >>\n";
                cout<<"Choose Rotate Degree \n";
                cout<<"1) Rotate 90 \n2) Rotate 180 \n3) Rotate 270 \n";
                cin >> choice2;
            }
            if (choice2 == "1")
            {
                cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
                string image_name;
                cin >> image_name;
                Image image(image_name);
                //calls the rotate90 function
                rotate90(image);
            }
            if (choice2 == "2")
            {
                cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
                string image_name;
                cin >> image_name;
                Image image(image_name);
                //calls the rotate180 function
                rotate180(image);
            }
            if (choice2 == "3")
            {
                cout << "Enter the name of the image with a valid extension (.jpg, .bmp, .png, .tga) >>";
                string image_name;
                cin >> image_name;
                Image image(image_name);
                //calls the rotate270 function
                rotate270(image);
            }
            menu();
        }
    }
}
int main()
{
    cout << "Welcome user!\nPlease choose a filter you want to apply to an image >>\n";
    menu();
    return 0;
}