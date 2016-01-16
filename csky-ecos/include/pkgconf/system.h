#ifndef CYGONCE_PKGCONF_SYSTEM_H
#define CYGONCE_PKGCONF_SYSTEM_H
/*
 * File <pkgconf/system.h>
 *
 * This file is generated automatically by the configuration
 * system. It should not be edited. Any changes to this file
 * may be overwritten.
 */

#define CYGNUM_VERSION_CURRENT 0x7fffff00
#define CYGPKG_HAL_CKMMU v3_0
#define CYGPKG_HAL_CKMMU_v3_0
#define CYGNUM_HAL_CKMMU_VERSION_MAJOR 3
#define CYGNUM_HAL_CKMMU_VERSION_MINOR 0
#define CYGNUM_HAL_CKMMU_VERSION_RELEASE -1
#define CYGPKG_HAL_CKMMU_CK610M v3_0
#define CYGPKG_HAL_CKMMU_CK610M_v3_0
#define CYGNUM_HAL_CKMMU_CK610M_VERSION_MAJOR 3
#define CYGNUM_HAL_CKMMU_CK610M_VERSION_MINOR 0
#define CYGNUM_HAL_CKMMU_CK610M_VERSION_RELEASE -1
#define CYGPKG_HAL_CKMMU_CK610M_GX3201 v3_0
#define CYGPKG_HAL_CKMMU_CK610M_GX3201_v3_0
#define CYGNUM_HAL_CKMMU_CK610M_GX3201_VERSION_MAJOR 3
#define CYGNUM_HAL_CKMMU_CK610M_GX3201_VERSION_MINOR 0
#define CYGNUM_HAL_CKMMU_CK610M_GX3201_VERSION_RELEASE -1
#define CYGBLD_HAL_TARGET_H <pkgconf/hal_ckmmu_ck610m.h>
#define CYGBLD_HAL_PLATFORM_H <pkgconf/hal_ckmmu_ck610m_gx3201.h>

/* Make sure we get the CORE type definitions for HAL_PLATFORM_CPU */
#include CYGBLD_HAL_TARGET_H
#define HAL_PLATFORM_BOARD    "gx3201"
#define HAL_PLATFORM_EXTRA    ""

#  define HAL_PLATFORM_CPU    "CK610m"

#define CYG_HAL_STARTUP RAM
#define CYG_HAL_STARTUP_RAM
#define CYGHWR_MEMORY_LAYOUT_LDI <pkgconf/mlt_ckmmu_gx3201_ram.ldi>
#define CYGHWR_MEMORY_LAYOUT_H <pkgconf/mlt_ckmmu_gx3201_ram.h>
#define CYGPKG_CRC v3_0
#define CYGPKG_CRC_v3_0
#define CYGNUM_CRC_VERSION_MAJOR 3
#define CYGNUM_CRC_VERSION_MINOR 0
#define CYGNUM_CRC_VERSION_RELEASE -1
#define CYGPKG_BLOCK_LIB v3_0
#define CYGPKG_BLOCK_LIB_v3_0
#define CYGNUM_BLOCK_LIB_VERSION_MAJOR 3
#define CYGNUM_BLOCK_LIB_VERSION_MINOR 0
#define CYGNUM_BLOCK_LIB_VERSION_RELEASE -1
#define CYGPKG_POSIX v3_0
#define CYGPKG_POSIX_v3_0
#define CYGNUM_POSIX_VERSION_MAJOR 3
#define CYGNUM_POSIX_VERSION_MINOR 0
#define CYGNUM_POSIX_VERSION_RELEASE -1
#define CYGPKG_LINUX_COMPAT v3_0
#define CYGPKG_LINUX_COMPAT_v3_0
#define CYGNUM_LINUX_COMPAT_VERSION_MAJOR 3
#define CYGNUM_LINUX_COMPAT_VERSION_MINOR 0
#define CYGNUM_LINUX_COMPAT_VERSION_RELEASE -1
#define CYGPKG_COMPRESS_ZLIB v3_0
#define CYGPKG_COMPRESS_ZLIB_v3_0
#define CYGNUM_COMPRESS_ZLIB_VERSION_MAJOR 3
#define CYGNUM_COMPRESS_ZLIB_VERSION_MINOR 0
#define CYGNUM_COMPRESS_ZLIB_VERSION_RELEASE -1
#define CYGPKG_DEVS_DYNAMIC_MANAGE v3_0
#define CYGPKG_DEVS_DYNAMIC_MANAGE_v3_0
#define CYGNUM_DEVS_DYNAMIC_MANAGE_VERSION_MAJOR 3
#define CYGNUM_DEVS_DYNAMIC_MANAGE_VERSION_MINOR 0
#define CYGNUM_DEVS_DYNAMIC_MANAGE_VERSION_RELEASE -1
#define CYGPKG_FS_FAT v3_0
#define CYGPKG_FS_FAT_v3_0
#define CYGNUM_FS_FAT_VERSION_MAJOR 3
#define CYGNUM_FS_FAT_VERSION_MINOR 0
#define CYGNUM_FS_FAT_VERSION_RELEASE -1
#define CYGPKG_FS_EXFAT v3_0
#define CYGPKG_FS_EXFAT_v3_0
#define CYGNUM_FS_EXFAT_VERSION_MAJOR 3
#define CYGNUM_FS_EXFAT_VERSION_MINOR 0
#define CYGNUM_FS_EXFAT_VERSION_RELEASE -1
#define CYGPKG_FS_JFFS2 v3_0
#define CYGPKG_FS_JFFS2_v3_0
#define CYGNUM_FS_JFFS2_VERSION_MAJOR 3
#define CYGNUM_FS_JFFS2_VERSION_MINOR 0
#define CYGNUM_FS_JFFS2_VERSION_RELEASE -1
#define CYGPKG_FS_YAFFS v3_0
#define CYGPKG_FS_YAFFS_v3_0
#define CYGNUM_FS_YAFFS_VERSION_MAJOR 3
#define CYGNUM_FS_YAFFS_VERSION_MINOR 0
#define CYGNUM_FS_YAFFS_VERSION_RELEASE -1
/***** Synthdisk driver proc output start *****/
#define CYGDAT_DEVS_DISK_YAFFS_CFG <pkgconf/fs_yaffs.h>
/***** Synthdisk driver proc output end  *****/
#define CYGPKG_FS_ROM v3_0
#define CYGPKG_FS_ROM_v3_0
#define CYGNUM_FS_ROM_VERSION_MAJOR 3
#define CYGNUM_FS_ROM_VERSION_MINOR 0
#define CYGNUM_FS_ROM_VERSION_RELEASE -1
#define CYGPKG_FS_CRAMFS v3_0
#define CYGPKG_FS_CRAMFS_v3_0
#define CYGNUM_FS_CRAMFS_VERSION_MAJOR 3
#define CYGNUM_FS_CRAMFS_VERSION_MINOR 0
#define CYGNUM_FS_CRAMFS_VERSION_RELEASE -1
#define CYGPKG_FS_MINIFS v3_0
#define CYGPKG_FS_MINIFS_v3_0
#define CYGNUM_FS_MINIFS_VERSION_MAJOR 3
#define CYGNUM_FS_MINIFS_VERSION_MINOR 0
#define CYGNUM_FS_MINIFS_VERSION_RELEASE -1
#define CYGPKG_FS_RAM v3_0
#define CYGPKG_FS_RAM_v3_0
#define CYGNUM_FS_RAM_VERSION_MAJOR 3
#define CYGNUM_FS_RAM_VERSION_MINOR 0
#define CYGNUM_FS_RAM_VERSION_RELEASE -1
#define CYGPKG_FS_NTFS v3_0
#define CYGPKG_FS_NTFS_v3_0
#define CYGNUM_FS_NTFS_VERSION_MAJOR 3
#define CYGNUM_FS_NTFS_VERSION_MINOR 0
#define CYGNUM_FS_NTFS_VERSION_RELEASE -1
#define CYGPKG_IO_I2C v3_0
#define CYGPKG_IO_I2C_v3_0
#define CYGNUM_IO_I2C_VERSION_MAJOR 3
#define CYGNUM_IO_I2C_VERSION_MINOR 0
#define CYGNUM_IO_I2C_VERSION_RELEASE -1
#define CYGPKG_IO_SPI v3_0
#define CYGPKG_IO_SPI_v3_0
#define CYGNUM_IO_SPI_VERSION_MAJOR 3
#define CYGNUM_IO_SPI_VERSION_MINOR 0
#define CYGNUM_IO_SPI_VERSION_RELEASE -1
#define CYGPKG_IO_DISK v3_0
#define CYGPKG_IO_DISK_v3_0
#define CYGNUM_IO_DISK_VERSION_MAJOR 3
#define CYGNUM_IO_DISK_VERSION_MINOR 0
#define CYGNUM_IO_DISK_VERSION_RELEASE -1
#define CYGPKG_IO_FLASH v3_0
#define CYGPKG_IO_FLASH_v3_0
#define CYGNUM_IO_FLASH_VERSION_MAJOR 3
#define CYGNUM_IO_FLASH_VERSION_MINOR 0
#define CYGNUM_IO_FLASH_VERSION_RELEASE -1
#define CYGPKG_IO_NAND v3_0
#define CYGPKG_IO_NAND_v3_0
#define CYGNUM_IO_NAND_VERSION_MAJOR 3
#define CYGNUM_IO_NAND_VERSION_MINOR 0
#define CYGNUM_IO_NAND_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_SPI v3_0
#define CYGPKG_DEVS_GX3110_SPI_v3_0
#define CYGNUM_DEVS_GX3110_SPI_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_SPI_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_SPI_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_IRR v3_0
#define CYGPKG_DEVS_GX3110_IRR_v3_0
#define CYGNUM_DEVS_GX3110_IRR_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_IRR_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_IRR_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_WDT v3_0
#define CYGPKG_DEVS_GX3110_WDT_v3_0
#define CYGNUM_DEVS_GX3110_WDT_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_WDT_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_WDT_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_I2C v3_0
#define CYGPKG_DEVS_GX3110_I2C_v3_0
#define CYGNUM_DEVS_GX3110_I2C_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_I2C_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_I2C_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX_SERIAL v3_0
#define CYGPKG_DEVS_GX_SERIAL_v3_0
#define CYGNUM_DEVS_GX_SERIAL_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX_SERIAL_VERSION_MINOR 0
#define CYGNUM_DEVS_GX_SERIAL_VERSION_RELEASE -1
/***** serial driver proc output start *****/
#define CYGDAT_IO_SERIAL_DEVICE_HEADER <pkgconf/devs_gx_serial.h>
/*****  serial driver proc output end  *****/
#define CYGPKG_DEVS_GX3110_DISK_SD v3_0
#define CYGPKG_DEVS_GX3110_DISK_SD_v3_0
#define CYGNUM_DEVS_GX3110_DISK_SD_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_DISK_SD_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_DISK_SD_VERSION_RELEASE -1
/***** SD disk driver output start *****/
#ifndef CYGDAT_DEVS_DISK_CFG
#define CYGDAT_DEVS_DISK_CFG <pkgconf/devs_disk_sd.h>
#endif
/***** SD disk driver output end *****/
#define CYGPKG_DEVS_GX3110_DISK_IDE v3_0
#define CYGPKG_DEVS_GX3110_DISK_IDE_v3_0
#define CYGNUM_DEVS_GX3110_DISK_IDE_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_DISK_IDE_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_DISK_IDE_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_SPI_FLASH v3_0
#define CYGPKG_DEVS_GX3110_SPI_FLASH_v3_0
#define CYGNUM_DEVS_GX3110_SPI_FLASH_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_SPI_FLASH_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_SPI_FLASH_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_SMARTCARD v3_0
#define CYGPKG_DEVS_GX3110_SMARTCARD_v3_0
#define CYGNUM_DEVS_GX3110_SMARTCARD_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_SMARTCARD_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_SMARTCARD_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_NAND v3_0
#define CYGPKG_DEVS_GX3110_NAND_v3_0
#define CYGNUM_DEVS_GX3110_NAND_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_NAND_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_NAND_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_WALLCLOCK v3_0
#define CYGPKG_DEVS_GX3110_WALLCLOCK_v3_0
#define CYGNUM_DEVS_GX3110_WALLCLOCK_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_WALLCLOCK_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_WALLCLOCK_VERSION_RELEASE -1
#define CYGPKG_DEVS_GX3110_GPIO v3_0
#define CYGPKG_DEVS_GX3110_GPIO_v3_0
#define CYGNUM_DEVS_GX3110_GPIO_VERSION_MAJOR 3
#define CYGNUM_DEVS_GX3110_GPIO_VERSION_MINOR 0
#define CYGNUM_DEVS_GX3110_GPIO_VERSION_RELEASE -1
#define CYGPKG_DEVS_ETH_CKCORE v3_0
#define CYGPKG_DEVS_ETH_CKCORE_v3_0
#define CYGNUM_DEVS_ETH_CKCORE_VERSION_MAJOR 3
#define CYGNUM_DEVS_ETH_CKCORE_VERSION_MINOR 0
#define CYGNUM_DEVS_ETH_CKCORE_VERSION_RELEASE -1
#define CYGPKG_DEVS_ETH_SYNOP_MAC v3_0
#define CYGPKG_DEVS_ETH_SYNOP_MAC_v3_0
#define CYGNUM_DEVS_ETH_SYNOP_MAC_VERSION_MAJOR 3
#define CYGNUM_DEVS_ETH_SYNOP_MAC_VERSION_MINOR 0
#define CYGNUM_DEVS_ETH_SYNOP_MAC_VERSION_RELEASE -1
#define GX_USB_DRIVER v3_0
#define GX_USB_DRIVER_v3_0
#define EVIXPKG_USB_LIB v3_0
#define EVIXPKG_USB_LIB_v3_0
#define EVIXNUM_USB_LIB_VERSION_MAJOR 3
#define EVIXNUM_USB_LIB_VERSION_MINOR 0
#define EVIXNUM_USB_LIB_VERSION_RELEASE -1
#define EVIXPKG_USB_WIFI v3_0
#define EVIXPKG_USB_WIFI_v3_0
#define EVIXNUM_USB_WIFI_VERSION_MAJOR 3
#define EVIXNUM_USB_WIFI_VERSION_MINOR 0
#define EVIXNUM_USB_WIFI_VERSION_RELEASE -1
#define EVIXPKG_USB_BASE v3_0
#define EVIXPKG_USB_BASE_v3_0
#define EVIXNUM_USB_BASE_VERSION_MAJOR 3
#define EVIXNUM_USB_BASE_VERSION_MINOR 0
#define EVIXNUM_USB_BASE_VERSION_RELEASE -1
#define EVIXPKG_USB_CORE v3_0
#define EVIXPKG_USB_CORE_v3_0
#define EVIXNUM_USB_CORE_VERSION_MAJOR 3
#define EVIXNUM_USB_CORE_VERSION_MINOR 0
#define EVIXNUM_USB_CORE_VERSION_RELEASE -1
#define EVIXPKG_USB_HOST_EHCI v3_0
#define EVIXPKG_USB_HOST_EHCI_v3_0
#define EVIXNUM_USB_HOST_EHCI_VERSION_MAJOR 3
#define EVIXNUM_USB_HOST_EHCI_VERSION_MINOR 0
#define EVIXNUM_USB_HOST_EHCI_VERSION_RELEASE -1
#define EVIXPKG_USB_HOST_OHCI v3_0
#define EVIXPKG_USB_HOST_OHCI_v3_0
#define EVIXNUM_USB_HOST_OHCI_VERSION_MAJOR 3
#define EVIXNUM_USB_HOST_OHCI_VERSION_MINOR 0
#define EVIXNUM_USB_HOST_OHCI_VERSION_RELEASE -1
#define EVIXPKG_USB_STORAGE v3_0
#define EVIXPKG_USB_STORAGE_v3_0
#define EVIXNUM_USB_STORAGE_VERSION_MAJOR 3
#define EVIXNUM_USB_STORAGE_VERSION_MINOR 0
#define EVIXNUM_USB_STORAGE_VERSION_RELEASE -1
#define CYGPKG_HAL v3_0
#define CYGPKG_HAL_v3_0
#define CYGNUM_HAL_VERSION_MAJOR 3
#define CYGNUM_HAL_VERSION_MINOR 0
#define CYGNUM_HAL_VERSION_RELEASE -1
#define CYGPKG_IO v3_0
#define CYGPKG_IO_v3_0
#define CYGNUM_IO_VERSION_MAJOR 3
#define CYGNUM_IO_VERSION_MINOR 0
#define CYGNUM_IO_VERSION_RELEASE -1
#define CYGPKG_IO_SERIAL v3_0
#define CYGPKG_IO_SERIAL_v3_0
#define CYGNUM_IO_SERIAL_VERSION_MAJOR 3
#define CYGNUM_IO_SERIAL_VERSION_MINOR 0
#define CYGNUM_IO_SERIAL_VERSION_RELEASE -1
#define CYGPKG_INFRA v3_0
#define CYGPKG_INFRA_v3_0
#define CYGNUM_INFRA_VERSION_MAJOR 3
#define CYGNUM_INFRA_VERSION_MINOR 0
#define CYGNUM_INFRA_VERSION_RELEASE -1
#define CYGPKG_ISOINFRA v3_0
#define CYGPKG_ISOINFRA_v3_0
#define CYGNUM_ISOINFRA_VERSION_MAJOR 3
#define CYGNUM_ISOINFRA_VERSION_MINOR 0
#define CYGNUM_ISOINFRA_VERSION_RELEASE -1
#define CYGPKG_KERNEL v3_0
#define CYGPKG_KERNEL_v3_0
#define CYGNUM_KERNEL_VERSION_MAJOR 3
#define CYGNUM_KERNEL_VERSION_MINOR 0
#define CYGNUM_KERNEL_VERSION_RELEASE -1
#define CYGPKG_MEMALLOC v3_0
#define CYGPKG_MEMALLOC_v3_0
#define CYGNUM_MEMALLOC_VERSION_MAJOR 3
#define CYGNUM_MEMALLOC_VERSION_MINOR 0
#define CYGNUM_MEMALLOC_VERSION_RELEASE -1
#define CYGPKG_LIBC v3_0
#define CYGPKG_LIBC_v3_0
#define CYGNUM_LIBC_VERSION_MAJOR 3
#define CYGNUM_LIBC_VERSION_MINOR 0
#define CYGNUM_LIBC_VERSION_RELEASE -1
#define CYGPKG_LIBC_TIME v3_0
#define CYGPKG_LIBC_TIME_v3_0
#define CYGNUM_LIBC_TIME_VERSION_MAJOR 3
#define CYGNUM_LIBC_TIME_VERSION_MINOR 0
#define CYGNUM_LIBC_TIME_VERSION_RELEASE -1
#define CYGPKG_LIBC_STDLIB v3_0
#define CYGPKG_LIBC_STDLIB_v3_0
#define CYGNUM_LIBC_STDLIB_VERSION_MAJOR 3
#define CYGNUM_LIBC_STDLIB_VERSION_MINOR 0
#define CYGNUM_LIBC_STDLIB_VERSION_RELEASE -1
#define CYGPKG_LIBC_STRING v3_0
#define CYGPKG_LIBC_STRING_v3_0
#define CYGNUM_LIBC_STRING_VERSION_MAJOR 3
#define CYGNUM_LIBC_STRING_VERSION_MINOR 0
#define CYGNUM_LIBC_STRING_VERSION_RELEASE -1
#define CYGPKG_LIBC_I18N v3_0
#define CYGPKG_LIBC_I18N_v3_0
#define CYGNUM_LIBC_I18N_VERSION_MAJOR 3
#define CYGNUM_LIBC_I18N_VERSION_MINOR 0
#define CYGNUM_LIBC_I18N_VERSION_RELEASE -1
#define CYGPKG_LIBC_SETJMP v3_0
#define CYGPKG_LIBC_SETJMP_v3_0
#define CYGNUM_LIBC_SETJMP_VERSION_MAJOR 3
#define CYGNUM_LIBC_SETJMP_VERSION_MINOR 0
#define CYGNUM_LIBC_SETJMP_VERSION_RELEASE -1
#define CYGPKG_LIBC_STARTUP v3_0
#define CYGPKG_LIBC_STARTUP_v3_0
#define CYGNUM_LIBC_STARTUP_VERSION_MAJOR 3
#define CYGNUM_LIBC_STARTUP_VERSION_MINOR 0
#define CYGNUM_LIBC_STARTUP_VERSION_RELEASE -1
#define CYGPKG_LIBC_STDIO v3_0
#define CYGPKG_LIBC_STDIO_v3_0
#define CYGNUM_LIBC_STDIO_VERSION_MAJOR 3
#define CYGNUM_LIBC_STDIO_VERSION_MINOR 0
#define CYGNUM_LIBC_STDIO_VERSION_RELEASE -1
#define CYGPKG_LIBM v3_0
#define CYGPKG_LIBM_v3_0
#define CYGNUM_LIBM_VERSION_MAJOR 3
#define CYGNUM_LIBM_VERSION_MINOR 0
#define CYGNUM_LIBM_VERSION_RELEASE -1
#define CYGPKG_IO_WATCHDOG v3_0
#define CYGPKG_IO_WATCHDOG_v3_0
#define CYGNUM_IO_WATCHDOG_VERSION_MAJOR 3
#define CYGNUM_IO_WATCHDOG_VERSION_MINOR 0
#define CYGNUM_IO_WATCHDOG_VERSION_RELEASE -1
#define CYGPKG_IO_WALLCLOCK v3_0
#define CYGPKG_IO_WALLCLOCK_v3_0
#define CYGNUM_IO_WALLCLOCK_VERSION_MAJOR 3
#define CYGNUM_IO_WALLCLOCK_VERSION_MINOR 0
#define CYGNUM_IO_WALLCLOCK_VERSION_RELEASE -1
#define CYGPKG_ERROR v3_0
#define CYGPKG_ERROR_v3_0
#define CYGNUM_ERROR_VERSION_MAJOR 3
#define CYGNUM_ERROR_VERSION_MINOR 0
#define CYGNUM_ERROR_VERSION_RELEASE -1
#define CYGPKG_IO_FILEIO v3_0
#define CYGPKG_IO_FILEIO_v3_0
#define CYGNUM_IO_FILEIO_VERSION_MAJOR 3
#define CYGNUM_IO_FILEIO_VERSION_MINOR 0
#define CYGNUM_IO_FILEIO_VERSION_RELEASE -1
#define CYGPKG_NET v3_0
#define CYGPKG_NET_v3_0
#define CYGNUM_NET_VERSION_MAJOR 3
#define CYGNUM_NET_VERSION_MINOR 0
#define CYGNUM_NET_VERSION_RELEASE -1
#define CYGPKG_NET_FREEBSD_STACK v3_0
#define CYGPKG_NET_FREEBSD_STACK_v3_0
#define CYGNUM_NET_FREEBSD_STACK_VERSION_MAJOR 3
#define CYGNUM_NET_FREEBSD_STACK_VERSION_MINOR 0
#define CYGNUM_NET_FREEBSD_STACK_VERSION_RELEASE -1
/***** Networking stack proc output start *****/
#define CYGDAT_NET_STACK_CFG <pkgconf/net_freebsd_stack.h>
/***** Networking stack proc output end *****/
#define CYGPKG_NS_DNS v3_0
#define CYGPKG_NS_DNS_v3_0
#define CYGNUM_NS_DNS_VERSION_MAJOR 3
#define CYGNUM_NS_DNS_VERSION_MINOR 0
#define CYGNUM_NS_DNS_VERSION_RELEASE -1
#define CYGPKG_IO_ETH_DRIVERS v3_0
#define CYGPKG_IO_ETH_DRIVERS_v3_0
#define CYGNUM_IO_ETH_DRIVERS_VERSION_MAJOR 3
#define CYGNUM_IO_ETH_DRIVERS_VERSION_MINOR 0
#define CYGNUM_IO_ETH_DRIVERS_VERSION_RELEASE -1
#define CYGPKG_NET_SNTP v3_0
#define CYGPKG_NET_SNTP_v3_0
#define CYGNUM_NET_SNTP_VERSION_MAJOR 3
#define CYGNUM_NET_SNTP_VERSION_MINOR 0
#define CYGNUM_NET_SNTP_VERSION_RELEASE -1

#endif