#include <stdio.h>
#include <string.h>
#include <iostream>
#include <memory>
#include <fitsio.h>
#include <opencv2/imgproc.hpp>



// Create a FITS primary array containing a 2D image and write it to disk.
int write_fits_image() {
    fitsfile *fptr;
    int status;
    long fpixel, nelements, exposure;
    unsigned short *array[200];
    char filename[] = "atestfil.fit";
    int bitpix = USHORT_IMG;
    long naxis = 2;
    long naxes[2] = {300, 200};

    array[0] = (unsigned short *)malloc(naxes[0] * naxes[1] * sizeof(unsigned short));

    for (int ii = 1; ii < naxes[1]; ++ii) {
        array[ii] = array[ii-1] + naxes[0];
    }
    remove(filename);

    status = 0;

    if (fits_create_file(&fptr, filename, &status)) {
        std::runtime_error("FITS writer failed to create file with status " + status);
    }
    if (fits_create_img(fptr, bitpix, naxis, naxes, &status)) {
        std::runtime_error("FITS writer failed to image with status " + status);
    }
    for (int jj = 0; jj < naxes[1]; ++jj) {
        for (int ii = 0; ii < naxes[0]; ++ii) {
            array[jj][ii] = ii + jj;
        }
    }
    fpixel = 1;
    nelements = naxes[0] * naxes[1];

    if (fits_write_img(fptr, TUSHORT, fpixel, nelements, array[0], &status)) {
        std::runtime_error("FITS writer failed to write image with status " + status);
    }
    free(array[0]);

    exposure = 1500;

    if (fits_update_key(fptr, TLONG, "EXPOSURE", &exposure, "Total exposure time", &status)) {
        std::runtime_error("FITS writer failed to write exposure with status " + status);
    }
    if (fits_close_file(fptr, &status)) {
        std::runtime_error("FITS writer failed to close the file with status " + status);
    }
    return status;
}

// Given the name of a FITS file, open it and return a Mat.
cv::Mat fits_to_cv(const std::string& filename) {
    int status;
    fitsfile *fptr;
    long width;
    long height;

    if (!fits_open_file(&fptr, filename.c_str(), READONLY, &status)) {
        std::runtime_error("couldn't open the file");
    }

    fits_read_key_lng(fptr, "NAXIS1", &width, NULL, &status);
    fits_read_key_lng(fptr, "NAXIS2", &height, NULL, &status);
    std::cout << "width: " << width << "   height: " << height << std::endl;
    return cv::Mat();
}


int main(int argc, char *argv[]){
    std::cout << "Fritz!" << std::endl;

    if (argc != 2) {
        std::cout << "Usage: fritzio [filename].fits" << std::endl;
        return(2);
    }
    const std::string filename(argv[1]);
    //read_fits_image(argv[1]);
    //write_fits_image();
    cv::Mat img = fits_to_cv(filename);
}
