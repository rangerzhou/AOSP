# Android fstab file for ramdisk
#<dev>  <mnt_point> <type>  <mnt_flags options> <fs_mgr_flags>
system   /system     ext4    ro,barrier=1     wait,logical,avb=vbmeta,first_stage_mount
vendor   /vendor     ext4    ro,barrier=1     wait,logical,first_stage_mount
product  /product    ext4    ro,barrier=1     wait,logical,first_stage_mount
system_ext  /system_ext  ext4   ro,barrier=1   wait,logical,first_stage_mount
/dev/block/pci/pci0000:00/0000:00:06.0/by-name/metadata    /metadata    ext4    noatime,nosuid,nodev    wait,formattable,first_stage_mount
