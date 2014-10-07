#ifndef _OSMAND_CORE_I_MAP_RASTER_BITMAP_TILE_PROVIDER_H_
#define _OSMAND_CORE_I_MAP_RASTER_BITMAP_TILE_PROVIDER_H_

#include <OsmAndCore/stdlib_common.h>

#include <OsmAndCore/QtExtensions.h>
#include <QtGlobal>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OsmAndCore/CommonSWIG.h>
#include <OsmAndCore/Map/MapCommonTypes.h>
#include <OsmAndCore/Map/IMapTiledDataProvider.h>

class SkBitmap;

namespace OsmAnd
{
    class OSMAND_CORE_API IMapRasterBitmapTileProvider : public IMapTiledDataProvider
    {
        Q_DISABLE_COPY_AND_MOVE(IMapRasterBitmapTileProvider);
    private:
    protected:
        IMapRasterBitmapTileProvider();
    public:
        virtual ~IMapRasterBitmapTileProvider();

        virtual uint32_t getTileSize() const = 0;
        virtual float getTileDensityFactor() const = 0;
    };
	
    SWIG_EMIT_DIRECTOR_BEGIN(IMapRasterBitmapTileProvider);
        SWIG_EMIT_DIRECTOR_CONST_METHOD_NO_ARGS(
            ZoomLevel,
            getMinZoom);
        SWIG_EMIT_DIRECTOR_CONST_METHOD_NO_ARGS(
            ZoomLevel,
            getMaxZoom);
        SWIG_EMIT_DIRECTOR_METHOD(
            bool,
            obtainData,
            /*SWIG_OMIT(const)*/ TileId tileId,
            const ZoomLevel zoom,
            std::shared_ptr<MapTiledData>& outTiledData,
            const IQueryController* const queryController);
        SWIG_EMIT_SHARED_PTR_REFERENCE_ASSIGN(MapTiledData);
        SWIG_EMIT_DIRECTOR_CONST_METHOD_NO_ARGS(
            uint32_t,
            getTileSize);
        SWIG_EMIT_DIRECTOR_CONST_METHOD_NO_ARGS(
            float,
            getTileDensityFactor);
    SWIG_EMIT_DIRECTOR_END(IMapRasterBitmapTileProvider);

    class OSMAND_CORE_API RasterBitmapTile : public MapTiledData
    {
        Q_DISABLE_COPY_AND_MOVE(RasterBitmapTile);

    private:
    protected:
    public:
        RasterBitmapTile(
            const std::shared_ptr<const SkBitmap>& bitmap,
            const AlphaChannelData alphaChannelData,
            const float densityFactor,
            const TileId tileId,
            const ZoomLevel zoom);
        virtual ~RasterBitmapTile();

        std::shared_ptr<const SkBitmap> bitmap;
        AlphaChannelData alphaChannelData;
        float densityFactor;

        virtual void releaseConsumableContent();
    };
}

#endif // !defined(_OSMAND_CORE_I_MAP_RASTER_BITMAP_TILE_PROVIDER_H_)