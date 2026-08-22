#pragma once

#include <optional>
#include <string>
#include <cstdint>

enum class FilesystemType {
    EXT2,
    EXT3,
    EXT4,
    BTRFS,
    XFS,
    JFS,
    REISERFS,
    REISER4,
    F2FS,
    NILFS2,

    NTFS,
    FAT12,
    FAT16,
    FAT32,
    EXFAT,

    HFS_PLUS,
    UFS,
    VMFS,

    UNKNOWN
};

enum class PartitionTableType {
    GPT,
    MBR,
    UNKNOWN
};

class Partition {
private:
    unsigned number;

    uint64_t startLba;
    uint64_t sizeLba;

    std::string typeId;

    std::optional<std::string> uuid;
    std::optional<std::string> name;

    uint64_t attributes;

    std::optional<FilesystemType> filesystem;
};