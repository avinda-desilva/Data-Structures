/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<3>> tile_colors;
     map<Point<3>, TileImage*> color_to_tile;

     //Find average color of every tile
     for (unsigned int i = 0; i < theTiles.size(); i++) {
       LUVAPixel color = theTiles[i].getAverageColor();
       color_to_tile[convertToXYZ(color)] = &theTiles[i];
       tile_colors.push_back(convertToXYZ(color));
     }

     KDTree<3>::KDTree color_tree(tile_colors);

     MosaicCanvas::MosaicCanvas *canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     for (int x = 0; x < theSource.getRows(); x++) {
         for (int y = 0; y < theSource.getColumns(); y++) {
             LUVAPixel sourceColor = theSource.getRegionColor(x, y);
             //map will return the tile similar to the color of the source region.
             TileImage* theTile = color_to_tile[color_tree.findNearestNeighbor(convertToXYZ(sourceColor))];
             canvas->setTile(x, y, theTile);
         }
     }

     //return canvas
     return canvas;
}
