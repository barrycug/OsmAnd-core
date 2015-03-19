#ifndef _OSMAND_CORE_DATA_COMMON_TYPES_H_
#define _OSMAND_CORE_DATA_COMMON_TYPES_H_

#include <OsmAndCore/stdlib_common.h>
#include <functional>

#include <OsmAndCore/QtExtensions.h>
#include <QString>

#include <OsmAndCore.h>
#include <OsmAndCore/CommonTypes.h>
#include <OsmAndCore/PointsAndAreas.h>
#include <OsmAndCore/Bitmask.h>

namespace OsmAnd
{
    enum class ObfDataType
    {
        Map = 0,
        Routing = 1,
        Address = 2,
        POI = 3,
        Transport = 4
    };

    typedef Bitmask<ObfDataType> ObfDataTypesMask;

    inline ObfDataTypesMask fullObfDataTypesMask()
    {
        return ObfDataTypesMask()
            .set(ObfDataType::Map)
            .set(ObfDataType::Routing)
            .set(ObfDataType::Address)
            .set(ObfDataType::POI)
            .set(ObfDataType::Transport);
    }

    class ObfSectionInfo;

    union OSMAND_CORE_API ObfObjectId
    {
        uint64_t id;

#if !defined(SWIG)
        inline operator uint64_t() const
        {
            return id;
        }

        inline bool operator==(const ObfObjectId& that)
        {
            return this->id == that.id;
        }

        inline bool operator!=(const ObfObjectId& that)
        {
            return this->id != that.id;
        }

        inline bool operator==(const uint64_t& that)
        {
            return this->id == that;
        }

        inline bool operator!=(const uint64_t& that)
        {
            return this->id != that;
        }
#endif // !defined(SWIG)

        inline static ObfObjectId invalidId()
        {
            ObfObjectId invalidId;
            invalidId.id = std::numeric_limits<uint64_t>::max();
            return invalidId;
        }

        inline bool isOsmId() const
        {
            return (static_cast<int64_t>(id) > 0);
        }

        inline int64_t getOsmId() const
        {
            if (!isOsmId())
                return -1;
            return static_cast<int64_t>(id >> 1);
        }

        QString toString() const;

        static ObfObjectId generateUniqueId(
            const uint64_t rawId,
            const uint32_t offsetInObf,
            const std::shared_ptr<const ObfSectionInfo>& obfSectionInfo);

        static ObfObjectId generateUniqueId(
            const uint32_t offsetInObf,
            const std::shared_ptr<const ObfSectionInfo>& obfSectionInfo);

        static ObfObjectId fromRawId(const uint64_t rawId);
    };

#if !defined(SWIG)
    static_assert(sizeof(ObfObjectId) == 8, "ObfObjectId must be 8 bytes in size");
#endif // !defined(SWIG)

    union ObfMapSectionDataBlockId
    {
        uint64_t id;
        struct
        {
            int sectionRuntimeGeneratedId;
            uint32_t offset;
        };

#if !defined(SWIG)
        inline operator uint64_t() const
        {
            return id;
        }

        inline bool operator==(const ObfMapSectionDataBlockId& that)
        {
            return this->id == that.id;
        }

        inline bool operator!=(const ObfMapSectionDataBlockId& that)
        {
            return this->id != that.id;
        }

        inline bool operator==(const uint64_t& that)
        {
            return this->id == that;
        }

        inline bool operator!=(const uint64_t& that)
        {
            return this->id != that;
        }
#endif // !defined(SWIG)
    };

#if !defined(SWIG)
    static_assert(sizeof(ObfMapSectionDataBlockId) == 8, "ObfMapSectionDataBlockId must be 8 bytes in size");
#endif // !defined(SWIG)

    enum class RoutingDataLevel
    {
        Basemap,
        Detailed,

        __LAST
    };
    enum {
        RoutingDataLevelsCount = static_cast<int>(RoutingDataLevel::__LAST)
    };

    union ObfRoutingSectionDataBlockId
    {
        uint64_t id;
        struct
        {
            int sectionRuntimeGeneratedId;
            uint32_t offset;
        };

#if !defined(SWIG)
        inline operator uint64_t() const
        {
            return id;
        }

        inline bool operator==(const ObfRoutingSectionDataBlockId& that)
        {
            return this->id == that.id;
        }

        inline bool operator!=(const ObfRoutingSectionDataBlockId& that)
        {
            return this->id != that.id;
        }

        inline bool operator==(const uint64_t& that)
        {
            return this->id == that;
        }

        inline bool operator!=(const uint64_t& that)
        {
            return this->id != that;
        }
#endif // !defined(SWIG)
    };

#if !defined(SWIG)
    static_assert(sizeof(ObfRoutingSectionDataBlockId) == 8, "ObfRoutingSectionDataBlockId must be 8 bytes in size");
#endif // !defined(SWIG)

    class ObfRoutingSectionInfo;
    typedef std::function < bool(
        const std::shared_ptr<const ObfRoutingSectionInfo>& section,
        const ObfObjectId roadId,
        const AreaI& bbox) > FilterRoadsByIdFunction;

    union ObfPoiCategoryId
    {
        // ((subcategory_order << 7) | category_order)

        uint32_t id;
        struct
        {
            uint32_t subCategoryIndex : 25;
            uint32_t mainCategoryIndex : 7;
        };

#if !defined(SWIG)
        inline operator uint32_t() const
        {
            return id;
        }

        inline bool operator==(const ObfPoiCategoryId& that)
        {
            return this->id == that.id;
        }

        inline bool operator!=(const ObfPoiCategoryId& that)
        {
            return this->id != that.id;
        }

        inline bool operator==(const uint32_t& that)
        {
            return this->id == that;
        }

        inline bool operator!=(const uint32_t& that)
        {
            return this->id != that;
        }
#endif // !defined(SWIG)
    };

#if !defined(SWIG)
    static_assert(sizeof(ObfPoiCategoryId) == 4, "ObfPoiCategoryId must be 4 bytes in size");
#endif // !defined(SWIG)

    enum class ObfAddressBlockType
    {
        CitiesOrTowns = 1,
        Villages = 3,
        Postcodes = 2,
    };
}

#endif // !defined(_OSMAND_CORE_DATA_COMMON_TYPES_H_)
