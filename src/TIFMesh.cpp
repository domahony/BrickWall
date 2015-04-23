/*
 * TIFMesh.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: domahony
 */

#include <string>
#include <iostream>
#include "TIFMesh.h"
#include "xtiffio.h"
#include "tiffio.h"
#include "geo_normalize.h"

namespace app {
namespace gl {

TIFMesh::
TIFMesh(const std::string& path) {

	TIFF *tif = 0;
	tif = XTIFFOpen(path.c_str(), "r");

	GTIF* gtif = GTIFNew(tif);
	GTIFDefn def;
	GTIFGetDefn(gtif, &def);

	double x = 0;
	double y = 0;
	GTIFImageToPCS(gtif, &x, &y);
    std::cout << x << " x " << y << std::endl;

    auto nstrips = TIFFNumberOfStrips(tif);
    auto strip_size = TIFFStripSize(tif);

    std::cout << "NStrips: " << nstrips<< std::endl;
    std::cout << "Strip Size: " << strip_size << std::endl;

    tstrip_t strip = 0;

    unsigned char* buf[2];

    int prev = 0;
    int cur = 1;

    buf[prev] = static_cast<unsigned char*>(_TIFFmalloc(TIFFStripSize(tif)));
    buf[cur] = static_cast<unsigned char*>(_TIFFmalloc(TIFFStripSize(tif)));


    TIFFReadEncodedStrip(tif, 0, buf[prev], -1);

    for (int i = 1; i < TIFFNumberOfStrips(tif); i++) {

    	TIFFReadEncodedStrip(tif, i, buf[cur], -1);
    	for (int j = 0; j < TIFFStripSize(tif); j += sizeof(short)) {
    		std::cout << j << ": "
    				<< static_cast<short>(buf[cur][j]) << ", "
    				<< static_cast<short>(buf[prev][j])
    				<< std::endl;
    	}

     	prev = (prev + 1)  % 2;
    	cur = (cur + 1)  % 2;
    	std::cout << "Prev: " << prev << ", Cur: " << cur << std::endl;
    }

    /*
    for (int i = 0; i < TIFFStripSize(tif); i += sizeof(short)) {
    	std::cout << i << ": " << static_cast<short>(buf[i]) << std::endl;
    }
    */

    if (0 && tif) {
        tdata_t buf;
        tstrip_t strip;

        buf = _TIFFmalloc(TIFFStripSize(tif));
        for (strip = 0; strip < TIFFNumberOfStrips(tif); strip++)
            TIFFReadEncodedStrip(tif, strip, buf, (tsize_t) -1);
        _TIFFfree(buf);
        TIFFClose(tif);
    }

	int w, h;

    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);

    std::cout << h << " x " << w << std::endl;

    std::exit(0);
}

} /* namespace gl */
} /* namespace app */
