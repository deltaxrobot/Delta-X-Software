
// *******************************************************************************
// GenDC.h
// GenDC structures and defines header.
// Version 1.1.0.00
//
//-----------------------------------------------------------------------------
//  Copyright (c) 2018 by Matrox Electronic Systems Ltd.
//  Section: GenDC
//  Project: GenICam
//  Author:  Stephane Maurice
//  $Header$ GenDC.H
//
//  License: This file is published under the license of the EMVA GenICam  Standard Group.
//  A text file describing the legal terms is included in  your installation as 'GenICam_license.pdf'.
//  If for some reason you are missing  this file please contact the EMVA or visit the website
//  (http://www.genicam.org) for a full copy.
//
//  THIS SOFTWARE IS PROVIDED BY THE EMVA GENICAM STANDARD GROUP "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE EMVA GENICAM STANDARD  GROUP
//  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT  LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  DATA, OR PROFITS;
//  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  THEORY OF LIABILITY,
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
#pragma once
// Prevent multiple GenDC.H inclusion.
#ifndef GenDCH
#define GenDCH

// Headers:
#ifndef _STDINT
#include <stdint.h>
#endif
#ifndef PFNC_H
#include "PFNC.h"
#endif
#include <stddef.h> // size_t

// GenDC standard values:
// -----------------------------------
// -----------------------------------
#define GDC_SIGNATURE               0x43444E47 // "GNDC" Signature (not null terminated)
#define GDC_VERSION_MAJOR           0x01
#define GDC_VERSION_MINOR           0x00
#define GDC_VERSION_SUBMINOR        0x00

// Header Types
#define GDC_HEADER_TYPE_MASK        0xF000
#define GDC_GENERIC_HEADER          0x0000
#define GDC_CONTAINER_HEADER        0x1000
#define GDC_COMPONENT_HEADER        0x2000
#define GDC_PART_HEADER             0x4000 // 0x4000-0x4FFF reserved for sub Part Headers type.
#define GDC_FLOW_TABLE_HEADER       0x7000

// Component Types (from SFNC)
#define GDC_UNDEFINED_COMPONENT     0x00
#define GDC_INTENSITY               0x01
#define GDC_INFRARED                0x02
#define GDC_ULTRAVIOLET             0x03
#define GDC_RANGE                   0x04
#define GDC_REFLECTANCE             0x05
#define GDC_CONFIDENCE              0x06
#define GDC_DISPARITY               0x07
#define GDC_SCATTER                 0x08
#define GDC_MULTISPECTRAL           0x09
#define GDC_EXTENDED_COMPONENT      0x8000
#define GDC_METADATA                GDC_EXTENDED_COMPONENT+0x0001
#define GDC_CUSTOM_COMPONENT        GDC_EXTENDED_COMPONENT+0x7F00    // + 0x0-0xFE valid
#define GDC_RESERVED_COMPONENT      GDC_EXTENDED_COMPONENT+0x7FFF

// Part types
#define GDC_GENERIC_PART_TYPE_MASK  GDC_PART_HEADER+0x0F00
#define GDC_GENERIC_PART_METADATA   GDC_PART_HEADER+0x0000
#define GDC_GENERIC_PART_1D         GDC_PART_HEADER+0x0100
#define GDC_GENERIC_PART_2D         GDC_PART_HEADER+0x0200
#define GDC_GENERIC_PART_CUSTOM     GDC_PART_HEADER+0x0F00

#define GDC_METADATA_GENICAM_CHUNK  GDC_GENERIC_PART_METADATA+0
#define GDC_METADATA_GENICAM_XML    GDC_GENERIC_PART_METADATA+1
#define GDC_METADATA_CUSTOM(x)      GDC_GENERIC_PART_METADATA+0xF0+x // + 0x0-0xF valid
#define GDC_1D                      GDC_GENERIC_PART_1D+0x00
#define GDC_1D_CUSTOM(x)            GDC_GENERIC_PART_1D+0xF0+x       // + 0x0-0xF valid
#define GDC_2D                      GDC_GENERIC_PART_2D+0x00
#define GDC_2D_JPEG                 GDC_GENERIC_PART_2D+0x01
#define GDC_2D_JPEG2000             GDC_GENERIC_PART_2D+0x02
#define GDC_2D_H264                 GDC_GENERIC_PART_2D+0x03
#define GDC_2D_CUSTOM(x)            GDC_GENERIC_PART_2D+0xF0+x       // + 0x0-0xF valid
#define GDC_CUSTOM(x)               GDC_GENERIC_PART_CUSTOM+x        // + 0x0-0xFE valid


// GenDC objects forward declarations:
// -----------------------------------
// -----------------------------------
struct GenDCContainerHeader;
struct GenDCComponentHeader;
struct GenDCPartHeader;

// GenDC types definitions.
// ------------------------
// ------------------------
// Pack all the structures.
#pragma pack(push, 1)

// GenDC Container typedef and enumerations.
enum    GenDCSignature : uint32_t               { Signature_GNDC = GDC_SIGNATURE };
typedef uint8_t GenDCVersionField;
enum    GenDCVersionValue : GenDCVersionField   { VersionMajorCurrent    = GDC_VERSION_MAJOR,
                                                  VersionMinorCurrent    = GDC_VERSION_MINOR,
                                                  VersionSubMinorCurrent = GDC_VERSION_SUBMINOR
                                                }; // Ex: Version 01.01.00
enum    GenDCReservedValue                      { ReservedDefaultValue = 0x00 };
typedef uint16_t GenDCHeaderTypeShared;
enum    GenDCHeaderType : GenDCHeaderTypeShared { TypeHeaderMask = GDC_HEADER_TYPE_MASK,
                                                  TypeGeneric    = GDC_GENERIC_HEADER,
                                                  TypeContainer  = GDC_CONTAINER_HEADER,
                                                  TypeComponent  = GDC_COMPONENT_HEADER,
                                                  TypePart       = GDC_PART_HEADER,
                                                  TypeFlowTable  = GDC_FLOW_TABLE_HEADER
                                                };
typedef uint32_t GenDCHeaderSize;
typedef uint16_t GenDCHeaderFlags;
union   GenDCContainerFlagsGroup;
typedef uint64_t GenDCContainerId;
typedef uint64_t GenDCDataSize;
typedef int64_t  GenDCOffset;
typedef uint32_t GenDCDescriptorSize;
typedef GenDCContainerHeader GenDCDescriptor;
typedef uint32_t GenDCContainerSectionFlag;
typedef uint32_t GenDCComponentCount;
typedef uint8_t  GenDCContainerBuffer;
typedef uint64_t GenDCContainerBufferSize;

typedef uint8_t  GenDCData;
typedef uint8_t  GenDCDataU8;
typedef uint16_t GenDCDataU16;
typedef uint32_t GenDCDataU32;
typedef uint64_t GenDCDataU64;
typedef void     GenDCDataVoid;
typedef struct   uint24_t /* 3 bytes pixel. Ex: RGB8. */
{
    // Storage for the RGB or BGR 8 bit values
    uint8_t PixelValue[3];

    // Default copy constructor.
    uint24_t(const uint24_t &GenDCDataU24Source)
    {
        for (int j = 0; j < 3; j++)
            PixelValue[j] = GenDCDataU24Source.PixelValue[j];
    };

    // Default conversion.
    operator uint32_t() const
    {
        uint32_t PixelValue32;
        for (int j = 0; j < 3; j++)
            ((uint8_t*)(&PixelValue32))[j] = PixelValue[j];
        return (PixelValue32);
    };
} uint24_t;
typedef uint24_t GenDCDataU24;

// GenDC Component typedef and enumerations.
typedef uint16_t GenDCGroupId;
typedef uint16_t GenDCSourceId;
typedef uint16_t GenDCRegionId;
typedef uint32_t GenDCRegionOffset;
typedef int64_t  GenDCTimestamp;
typedef uint64_t GenDCComponentTypeId;
typedef PfncFormat GenDCFormat;
typedef uint16_t GenDCPartCount;
enum    GenDCComponentType : GenDCComponentTypeId
{
    TypeUndefined       = GDC_UNDEFINED_COMPONENT, TypeIntensity         = GDC_INTENSITY,
    TypeInfrared        = GDC_INFRARED,            TypeUltraviolet       = GDC_ULTRAVIOLET,
    TypeRange           = GDC_RANGE,               TypeReflectance       = GDC_REFLECTANCE,
    TypeConfidence      = GDC_CONFIDENCE,          TypeDisparity         = GDC_DISPARITY,
    TypeScatter         = GDC_SCATTER,             TypeMultispectral     = GDC_MULTISPECTRAL,
    TypeExtended        = GDC_EXTENDED_COMPONENT,  TypeMetadata          = GDC_METADATA,
    TypeCustomComponent = GDC_CUSTOM_COMPONENT,    TypeReservedComponent = GDC_RESERVED_COMPONENT
};

// GenDC Part typedef and enumerations.
typedef uint64_t GenDCSize1D;
typedef int64_t  GenDCSize1DSigned;
typedef uint32_t GenDCSize2D;
typedef GenDCSize1D GenDCSize;
typedef uint16_t GenDCPadding;
typedef uint64_t GenDCDataSize;
typedef uint16_t GenDCFlowId;
typedef uint32_t GenDCFlowCount;
typedef GenDCOffset GenDCFlowOffset;
enum    GenDCGenericPartType : GenDCHeaderTypeShared
{
    TypeGenericPart   = GDC_PART_HEADER,         TypeGenericMetadata = GDC_GENERIC_PART_METADATA,
    TypeGenericPart1D = GDC_GENERIC_PART_1D,     TypeGenericPart2D   = GDC_GENERIC_PART_2D,
    TypeGenericCustom = GDC_GENERIC_PART_CUSTOM, TypeGenericPartMask = GDC_GENERIC_PART_TYPE_MASK,
};
enum    GenDCPartType : GenDCHeaderTypeShared
{
    TypeMetadataGenICamChunk = GDC_METADATA_GENICAM_CHUNK, TypeMetadataGenICamXML = GDC_METADATA_GENICAM_XML,
    TypeMetadataCustom       = GDC_METADATA_CUSTOM(0),     Type1D                 = GDC_1D,
    Type1DCustom             = GDC_1D_CUSTOM(0),           Type2D                 = GDC_2D,
    TypeJPEG                 = GDC_2D_JPEG,                TypeJPEG2000           = GDC_2D_JPEG2000,
    TypeH264                 = GDC_2D_H264,
    Type2DCustom             = GDC_2D_CUSTOM(0)
};

// General utility types and enumerations.
typedef uint8_t  GenDCReserved8;
typedef uint16_t GenDCReserved16;
typedef uint32_t GenDCReserved32;
typedef uint64_t GenDCReserved64;
typedef const char* GenDCErrorMessage;
enum GenDCPredefinedValue32 : GenDCComponentCount        { GenDCAllComponents = 0xFFFFFFFF, GenDCAllFlows = 0xFFFFFFFF };
enum GenDCPredefinedValue16 : GenDCPartCount             { GenDCAllParts = 0xFFFF };
enum GenDCPredefinedValue64 : uint64_t                   { GenDCAllData = 0x8FFFFFFFFFFFFFFF, GenDCCenter = 0x8FFFFFFFFFFFFFFE };
enum GenDCPredefinedComponentValue : GenDCComponentCount { GenDCInvalidComponentIndex = 0xFFFFFFFF };
enum GenDCPredefinedPartValue : GenDCPartCount           { GenDCInvalidPartIndex = 0xFFFF };

// Typedef to avoid warning for 32 or 64 bit compilation.
#ifndef WIN32
typedef GenDCDataSize GenDCAllocationDataSize;
#else
typedef unsigned GenDCAllocationDataSize;
#endif


//GenDC headers structures:
//-----------------------------------------
//-----------------------------------------

// Container's Flags bit fields structure.
// ---------------------------------------
union GenDCContainerFlagsGroup    // Container's Flags.
{
    GenDCHeaderFlags Value;
    struct
    {
        GenDCHeaderFlags TimestampPTP     : 1;
        GenDCHeaderFlags ComponentInvalid : 1;
        GenDCHeaderFlags Reserved         : 14;
    } Field;
};

// Container's VariableFields flags bit fields structure.
// ------------------------------------------------------
union GenDCContainerVariableFieldsGroup    // Container's Flags.
{
    GenDCHeaderFlags Value;
    struct
    {
        GenDCHeaderFlags DataSize : 1;
        GenDCHeaderFlags SizeX : 1;
        GenDCHeaderFlags SizeY : 1;
        GenDCHeaderFlags RegionOffset : 1;
        GenDCHeaderFlags Format : 1;
        GenDCHeaderFlags Timestamp : 1;
        GenDCHeaderFlags ComponentCount : 1;
        GenDCHeaderFlags ComponentInvalid: 1;
        GenDCHeaderFlags Reserved : 8;
    } Field;
};


// GenDC Container header base.
//-----------------------------
struct GenDCContainerHeaderBase
{
    GenDCSignature                      Signature;
    GenDCVersionField                   VersionMajor;
    GenDCVersionField                   VersionMinor;
    GenDCVersionField                   VersionSubMinor;
    GenDCReserved8                      Reserved;
    GenDCHeaderType                     HeaderType;
    GenDCContainerFlagsGroup            Flags;
    GenDCHeaderSize                     HeaderSize;
    GenDCContainerId                    Id;
    GenDCContainerVariableFieldsGroup   VariableFields;
    GenDCReserved16                     Reserved16;
    GenDCReserved32                     Reserved32;
    GenDCDataSize                       DataSize;
    GenDCOffset                         DataOffset;
    GenDCDescriptorSize                 DescriptorSize;
    GenDCComponentCount                 ComponentCount;
    // GenDCOffset ComponentOffsets[ComponentCount]; field not included in base class.
};

// GenDC Container header (including a Component PartOffset array member).
//------------------------------------------------------------------------
#define GDC_CONTAINER_COMPONENT_COUNT_MIN 1
struct GenDCContainerHeader : GenDCContainerHeaderBase
{
    // GenDCOffset ComponentOffsets[ComponentCount]; minimal Component Offset(s) included.
    // This allow to use Container.ComponentOffsets[ComponentIndex].
    // Note: sizeof(GenDCContainerHeader) must not be used if ComponentCount > 1.
    // Note: Only GenDCContaineHeader reference (GenDCContainerHeader &) can be used as destination to operator =
    //       since the default copy constructor will not copy all the ComponentOffset members;
    //       Use only GenDCContaineHeader &Container = AnotherGenDCContaineHeader.
    GenDCOffset ComponentOffsets[GDC_CONTAINER_COMPONENT_COUNT_MIN];

    // Default constructor for "ContainerHeader &".
    // GenDCContainerHeader() {;};

    // Deleted default copy constructor since it will not copy all the ComponentOffsets[] members.
    // It would also not point to the real Container header memory Offset.
    // Use a reference instead (Ex: GenDCContainerHeader& MyContainer = ...;) or a pointer.
    // GenDCContainerHeader(GenDCContainerHeader &) = delete;
};


// Component's Flags bit fields structure.
// ---------------------------------------
union GenDCComponentFlagsGroup // Component's Flags.
{
    GenDCHeaderFlags Value;
    struct
    {
        GenDCHeaderFlags Invalid : 1;
        GenDCHeaderFlags Unallocated : 15;
    } Field;
};


// GenDC Component header base.
// ----------------------------
struct GenDCComponentHeaderBase
{
    GenDCHeaderType             HeaderType;
    GenDCComponentFlagsGroup    Flags;
    GenDCHeaderSize             HeaderSize;
    GenDCReserved16             Reserved;
    GenDCGroupId                GroupId;
    GenDCSourceId               SourceId;
    GenDCRegionId               RegionId;
    GenDCRegionOffset           RegionOffsetX;
    GenDCRegionOffset           RegionOffsetY;
    GenDCTimestamp              Timestamp;
    GenDCComponentTypeId        TypeId;
    GenDCFormat                 Format;
    GenDCReserved16             Reserved2;
    GenDCPartCount              PartCount;
    // GenDCOffset              PartOffsets[PartCount]; // This field is not included in base class.
};

// GenDC Component  header (including a PartOffset[] array member).
//-----------------------------------------------------------------
#define GDC_COMPONENT_PART_COUNT_MIN 1
struct GenDCComponentHeader : GenDCComponentHeaderBase
{
    // GenDCOffset PartOffsets[PartCount]; minimal Component Offset(s) included.
    // This allow to use Component.PartOffsets[ComponentIndex].
    // Note: sizeof(GenDCComponent Header) must not be used if ComponentCount > 1.
    // Note: Only GenDCComponent header reference (GenDCPart Header &) can be used as destination to operator =
    //       since the default copy constructor will not copy all the PartOffsets members;
    //       Use only GenDCComponentHeader &Component  = AnotherGenDCComponentHeader.
    GenDCOffset PartOffsets[GDC_COMPONENT_PART_COUNT_MIN];

    // Default constructor for "ComponentHeader &".
    GenDCComponentHeader() { ; };

    // Deleted default copy constructor since it will not copy all the Parts header members.
    // It would also not point to the real Component header memory Offset.
    // Use a reference instead (Ex: GenDCCoponenHeader& MyComponent = ...;) or a pointer.
    GenDCComponentHeader(GenDCComponentHeader &) = delete;
};

// Part's Flags bit fields structure.
// ---------------------------------------
union GenDCPartFlagsGroup    // Part's Flags.
{
    GenDCHeaderFlags Value;
    struct
    {
        GenDCHeaderFlags Unallocated : 16;
    } Field;
};

// GenDC Part header common fields.
// --------------------------------
struct GenDCPartHeaderBase
{
   GenDCPartType        HeaderType;
   GenDCPartFlagsGroup  Flags;
   GenDCHeaderSize      HeaderSize;
   GenDCFormat          Format;
   GenDCReserved16      Reserved;
   GenDCFlowId          FlowId;
   GenDCFlowOffset      FlowOffset;
   GenDCDataSize        DataSize;
   GenDCOffset          DataOffset;
};

// GenDC generic standard Part header.
//------------------------------------
struct GenDCPartHeader : public GenDCPartHeaderBase // Add no field compared to base class.
{
   // Default constructor for "PartHeader &".
   GenDCPartHeader() { ; };

   // Deleted default copy constructor since it will not copy all Part type specific members.
   // It would also not point to the real Part header memory Offset.
   // Use a reference instead (Ex: GenDCPartHeader& MyPart = ...;) or a pointer.
   GenDCPartHeader(GenDCPartHeader &) = delete;
};

// GenDC 2D Part header base
//---------------------------
struct GenDCPartHeader2DBase : public GenDCPartHeader
{
    GenDCSize2D     SizeX;
    GenDCSize2D     SizeY;
    GenDCPadding    PaddingX;
    GenDCPadding    PaddingY;
    GenDCReserved32 InfoReserved;
};

// GenDC 2D uncompressed Part header
//-----------------------------------
#define GDC_1D_2D_IMAGE_INFO_RESERVED_COUNT 1
struct GenDCPartHeader2D : public GenDCPartHeader2DBase
{
};

// GenDC 2D JPEG and JPEG200 standard Type specific info.
//-------------------------------------------------------
struct GenDCInfoTypeSpecificJPEG
{
};

// GenDC 2D JPEG standard Part header.
//------------------------------------
struct GenDCPartHeaderJPEG : public GenDCPartHeader2DBase
{
};

// GenDC 2D JPEG2000 standard Part header.
//----------------------------------------
struct GenDCPartHeaderJPEG2000 : public GenDCPartHeader2DBase
{
};

// Part Info field interpretation structure for H.264.
struct GenDCInfoTypeSpecificH264
{
    uint8_t Reserved;
    uint8_t	ProfileIDC;
    union H264Flags
    {
        uint8_t CS_set0_flag : 1;
        uint8_t CS_set1_flag : 1;
        uint8_t CS_set2_flag : 1;
        uint8_t CS_set3_flag : 1;
        uint8_t	PM : 2;
        uint8_t RF : 2;
    } Flags;
    uint8_t	LevelIDC;
    uint16_t SpropInterleavingDepth;
    uint16_t SpropMaxDonDiff;
    uint32_t SpropDeintBufReq;
    uint32_t SpropInitBufTime;
};

// GenDC 2D H.264 compressed Part header.
// --------------------------------------
struct GenDCPartHeaderH264 : public GenDCPartHeader2DBase
{
   GenDCInfoTypeSpecificH264 InfoTypeSpecific;
};

// GenDC 1D uncompressed Part header.
// ----------------------------------
struct GenDCPartHeader1DBase : GenDCPartHeader
{
    GenDCSize1D     SizeX;
    GenDCPadding    PaddingX;
    GenDCReserved16 PaddingReserved;
    GenDCReserved32 InfoReserved;
    uint64_t        InfoTypeSpecific;
};

// GenDC 1D uncompressed Part header.
// ----------------------------------
struct GenDCPartHeader1D : GenDCPartHeader1DBase
{
};

// GenDC GenICam Chunk Metadata Part header.
// -----------------------------------------
struct GenDCPartHeaderGenICamChunk : GenDCPartHeader1DBase
{
// For GenICam Chunk metadata Part, InfoTypeSpecific[] should contain the GenICam chunk_layout_id.
};

// GenDC GenICam XML Metadata Part header.
// ---------------------------------------
struct GenDCPartHeaderGenICamXML: GenDCPartHeader1DBase
{
    // For GenICam XML metadata Part, InfoTypeSpecific[] should contain the GenICam XML_layout_id.
};

// GenDC Container Descriptor Template declaration.
// Assuming that all the Components and their 2D Parts are all symmetrical.
template<size_t _ComponentCount, size_t _PartCount>
struct ContainerDescriptorTemplate2D : GenDCContainerHeaderBase
{
    // Container header base fields followed by the ComponentOffset.
    GenDCOffset ComponentOffsets[_ComponentCount];

    // Including a Component header base followed by the PartOffset.
    struct : GenDCComponentHeaderBase
    {
        GenDCOffset PartOffsets[_PartCount];

        // Including Part headers.
        struct : GenDCPartHeader2D
        {
        } Parts[_PartCount];
    } Components[_ComponentCount];
};

// GenDC Container Descriptor for a single 2D Component declaration.
// Assuming 1 Components and 1 2D Part.
struct ContainerDescriptorSingleComponent2D : GenDCContainerHeaderBase
{
    // Container header base fields followed by a single ComponentOffset.
    GenDCOffset ComponentOffsets[1];
    // Including a Component header base followed by a single PartOffset.
    struct : GenDCComponentHeaderBase
    {
        GenDCOffset PartOffsets[1];

        // Including a Part header.
        struct : GenDCPartHeader2D
        {
        } Part;
    } Component;
};

// Flow table base header.
// -------------------------
struct GenDCFlowTableHeader
{
    GenDCHeaderType   HeaderType;
    GenDCHeaderFlags  Flags;
    GenDCHeaderSize   HeaderSize;
    GenDCVersionField VersionMajor;
    GenDCVersionField VersionMinor;
    GenDCReserved16   Reserved;
    GenDCFlowCount    FlowCount;
};

// Flow table with one entry (Note: sizeof(GenDCFlowTable) invalid).
// -------------------------
struct GenDCFlowTable : GenDCFlowTableHeader
{
    uint64_t FlowSize[1]; // Stub array field for easy access using FlowTable.FlowSize[n].
};

// Flow table template.
// -------------------------
template<GenDCPartCount _FlowCount>
struct GenDCFlowTableTemplate : GenDCFlowTableHeader
{
    uint64_t FlowSize[_FlowCount];
};

// Restore packing.
#pragma pack(pop)

#endif // #ifndef GenDCH
