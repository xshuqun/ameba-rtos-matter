# Matter OTA Guide

Follow this guide to carry out Matter standard Over the Air Software Update

## Prerequisites

Build Linux ota-provider-app

    cd connectedhomeip
    source scripts/activate.sh
    ./scripts/examples/gn_build_example.sh examples/ota-provider-app/linux/ ota-provider

## Generating the OTA Image

When building the OTA firmware, ensure that the software version is higher than
that of the current image. The device only accepts an update whose version is
newer than the one it is running. You can check the current image's software
version using `chip-tool` commands below.

    ./chip-tool basicinformation read software-version 1 0
    ./chip-tool basicinformation read software-version-string 1 0

### Device identity and software version

Vendor ID, product ID and software version are configured in the menuconfig and
applied by running `matter_apply_conf`, which writes them into `current_proj.conf`:

| menuconfig option | Default | Meaning |
|---|---|---|
| `MATTER_DEVICE_VENDOR_ID` | `0xFFF1` | Vendor ID (hex) |
| `MATTER_DEVICE_PRODUCT_ID` | `0x8001` | Product ID (hex) |
| `MATTER_DEVICE_SOFTWARE_VERSION` | `2` | Numeric software version |
| `MATTER_DEVICE_SOFTWARE_VERSION_STR` | `"2.0"` | Software version string |

`0xFFF1` and `0x8001` are the Matter test vendor and product IDs; replace them
with your CSA-allocated values for production.

One menuconfig value feeds both the firmware and the OTA image. This matters
because after an update reboots, the new firmware confirms the image by
comparing its own compiled-in `CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION`
against the version the OTA image declared (`ConfirmCurrentImage`). If the two
disagree the update is applied but never reported as successful, so keep them in
step by bumping the menuconfig version, rebuilding, and regenerating the image.

To update a device that is already running version `2`, set
`MATTER_DEVICE_SOFTWARE_VERSION` to `3` (and the string accordingly), then
rebuild and generate the image as below.

> The Ameba bootloader also has its own image version (`img_ver_major` /
> `img_ver_minor` of `image2` in
> `component/soc/amebaxx/project/manifest.json5`, ameba-rtos-v1.2). That is a
> separate mechanism used for rollback protection; see the SDK documentation.

### Generating the Matter OTA image

From the `ameba-rtos-matter` directory, after `matter_apply_conf` and
`matter_build_proj`:

    matter_ota_image [output ota image]

For example:

    $ matter_ota_image
    Matter OTA image
      container:   /path/to/ameba-rtos-matter/build_RTL8721F/ota_all.bin
      vendor ID:   0xFFF1
      product ID:  0x8001
      version:     2 (2.0)
      output:      matter_ota_all.bin
    /path/to/build_RTL8721F/ota_all.bin: OK (FwVer 0xffffffff, 1 image(s), 1713248 B)
    Wrote matter_ota_all.bin

The script reads the device identity back out of the menuconfig, validates the
Ameba OTA container, and invokes `ota_image_tool.py create` as described in the
per-chip sections below. Pass a path to write somewhere other than
`./matter_ota_all.bin`.

If you prefer to run the tools by hand, the rest of this section documents the
underlying steps.

### Use the Ameba OTA container (`ota_all.bin`)

The Matter OTA image must be built from the **Ameba OTA container**, i.e. `ota_all.bin`,
not from the bare application image. The build produces both:

| Artifact | Contents | Use for Matter OTA |
|---|---|---|
| `ota_all.bin` | 32-byte Ameba OTA header + application image | **yes** |
| `app.bin` / `km0_km4_app.bin` / `kr4_km4_app.bin` / `km0_km4_ca32_app.bin` | application image only | no |

The 32-byte Ameba OTA header tells the OTA Requestor how long the application
image is and what its checksum is:

    offset 0   FwVer      u32 LE   container format version
    offset 4   HdrNum     u32 LE   number of image sub-headers
    offset 8   sub-header #0 (24 bytes):
                 +0  Signature  4 B   "OTA1"
                 +4  ImgHdrLen  u32   length of this sub-header (24)
                 +8  Checksum   u32   sum of all image bytes, modulo 2^32
                 +12 ImgLen     u32   length of the application image
                 +16 Offset     u32   offset of the image in the container
                 +20 ImgID      u32   0 = bootloader, 1 = application
    offset 32  application image

On the device, `matter_ota_store_header()` collects these 32 bytes, validates
them, and `matter_ota_flash_burst_write()` writes only the application image to
the OTA slot. The image is checked against the declared length and checksum
before the new slot is committed, so a truncated or corrupted download is
rejected instead of being booted.

### Inspecting the container: `ota_all_tool.py`

`ota_all_tool.py` reads and validates `ota_all.bin` before you wrap it into a
Matter OTA image, so a bad or truncated build is caught on the host rather than
on the device.

#### `show` — print the container header

    python3 ota_all_tool.py show <ota_all.bin>

Example:

    $ python3 ota_all_tool.py show build_RTL8721F/ota_all.bin
    File: build_RTL8721F/ota_all.bin
    Size: 1713248
    Ameba OTA file header:
      FwVer:  4294967295 (0xffffffff)
      HdrNum: 1
    Image sub-headers:
      [0] Signature: OTA1
          ImgHdrLen: 24
          Checksum:  181411802 (0xad01fda)
          ImgLen:    1713216
          Offset:    32
          ImgID:     1 (application)

#### `verify` — validate the container

    python3 ota_all_tool.py verify <ota_all.bin>

Checks that the image signature is "OTA...", that `ImgHdrLen` is 24, that
`ImgID` is 1 (application), that the images are contiguous, and that each
`Checksum` matches the image bytes. Exits non-zero and prints one `error:` line
per problem if the container is not usable.

    $ python3 ota_all_tool.py verify build_RTL8721F/ota_all.bin
    build_RTL8721F/ota_all.bin: OK (FwVer 0xffffffff, 1 image(s), 1713248 B)
      ImgID=1 (application) offset=32 len=1713216 checksum=0x0ad01fda OK

A container whose checksum does not match is rejected:

    $ python3 ota_all_tool.py verify ota_all.bin
    error: image[0] (ImgID=1 application): Checksum is 0x0ad01fda, computed 0x0ad01edb
    error: ota_all.bin: 1 problem(s) found, NOT a usable Ameba OTA container

Passing a bare application image such as `app.bin` by mistake is also caught:

    $ python3 ota_all_tool.py verify app.bin
    error: this looks like a bare application image (certificate pattern present at offset 0), not the Ameba OTA container; pass ota_all.bin instead

#### `extract` — pull one image out of the container

    python3 ota_all_tool.py extract [-id <IMGID>] <ota_all.bin> <output file>

`-id` defaults to `1` (the application image), which is the image that lands in
the OTA slot. Extracting it reproduces the SDK's `app.bin`:

    python3 ota_all_tool.py extract -id 1 build_RTL8721F/ota_all.bin app.bin

The recommended flow is therefore: `verify` the container, then pass the same
`ota_all.bin` to `ota_image_tool.py create` (see the per-chip sections below).

<details>
  <summary>For AmebaDplus OTA Image</summary>

Ensure that the OTA address is set correctly according to the device's flash size in the following files:

    component/soc/usrcfg/amebadplus/ameba_flashcfg.c (ameba-rtos-v1.2 or v1.1)
    component/soc/amebadplus/usrcfg/ameba_flashcfg.c (ameba-rtos-v1.0)

The file can be found in the base SDK.

### Example

In `ameba_flashcfg.c`
```c
const FlashLayoutInfo_TypeDef Flash_Layout[] = {
	/* Region_Type, [StartAddr, EndAddr] */
	{IMG_BOOT,      0x08000000, 0x08013FFF}, //Boot Manifest(4K) + KM4 Bootloader(76K)
	//Users should modify below according to their own memory
	{IMG_APP_OTA1,  0x08014000, 0x081FFFFF}, //Certificate(4K) + Manifest(4K) + KM4 Application OTA1 + RDP IMG OTA1

	{IMG_BOOT_OTA2, 0x08200000, 0x08213FFF}, //Boot Manifest(4K) + KM4 Bootloader(76K) OTA
	{IMG_APP_OTA2,  0x08214000, 0x083DCFFF}, //Certificate(4K) + Manifest(4K) + KM4 Application OTA2 + RDP IMG OTA2

	{FTL,           0x083DD000, 0x083DFFFF}, //FTL for BT(>=12K), The start offset of flash pages which is allocated to FTL physical map.
	{VFS1,          0x083E0000, 0x083FFFFF}, //VFS region 1 (128K)
	{VFS2,          0xFFFFFFFF, 0xFFFFFFFF}, //VFS region 2
	{USER,          0xFFFFFFFF, 0xFFFFFFFF}, //reserve for user

	/* End */
	{0xFF,          0xFFFFFFFF, 0xFFFFFFFF},
};
```

Once you've set the addresses correctly for `IMG_APP_OTA1` and `IMG_APP_OTA2`, ensure that you rebuild both the firmware correctly.

### Generating Matter OTA Image

Use the ota_image_tool.py to generate the Matter OTA image, embedding the Matter OTA header:

    python3 ota_image_tool.py create -v <VENDORID> -p <PRODUCTID> -vn <VERSION> -vs <VERSIONSTRING> -da <DIGESTALGO> <path to ota_all.bin> <output ota image>

Example:

    python3 ota_image_tool.py create -v 0xFFF1 -p 0x8001 -vn 2 -vs 2.0 -da sha256 ../../../../../build_RTL8721Dx/ota_all.bin matter_ota_all.bin

</details>

<details>
  <summary>For AmebaLite OTA Image</summary>

Ensure that the OTA address is set correctly according to the device's flash size in the following files:

    component/soc/usrcfg/amebalite/ameba_flashcfg.c (ameba-rtos-v1.2 or v1.1)
    component/soc/amebalite/usrcfg/ameba_flashcfg.c (ameba-rtos-v1.0)

The file can be found in the base SDK.

### Example

In `ameba_flashcfg.c`
```c
FlashLayoutInfo_TypeDef Flash_Layout[] = {
	/* Region_Type, [StartAddr, EndAddr] */
	{IMG_BOOT,      0x08000000, 0x08013FFF}, //Boot Manifest(4K) + KM4 Bootloader(76K)
	//Users should modify below according to their own memory
	{IMG_APP_OTA1,  0x08014000, 0x081FFFFF}, //Certificate(4K) + Manifest(4K) + KR4 & KM4 Application OTA1 + RDP IMG OTA1

	{IMG_BOOT_OTA2, 0x08200000, 0x08213FFF}, //Boot Manifest(4K) + KM4 Bootloader(76K) OTA
	{IMG_APP_OTA2,  0x08214000, 0x083DCFFF}, //Certificate(4K) + Manifest(4K) + KR4 & KM4 Application OTA2 + RDP IMG OTA2
	{FTL,           0x083DD000, 0x083DFFFF}, //FTL for BT(>=12K), The start offset of flash pages which is allocated to FTL physical map.
	{VFS1,          0x083E0000, 0x083FFFFF}, //VFS region 1 (128K)
	{IMG_DSP,       0x08400000, 0x086FFFFF}, //Manifest(4K) + DSP IMG, only one DSP region in layout
	{VFS2,          0xFFFFFFFF, 0xFFFFFFFF}, //VFS region 2
	{USER,          0xFFFFFFFF, 0xFFFFFFFF}, //reserve for user

	/* End */
	{0xFF,          0xFFFFFFFF, 0xFFFFFFFF},
};
```

Once you've set the addresses correctly for `IMG_APP_OTA1` and `IMG_APP_OTA2`, ensure that you rebuild both the firmware correctly.

### Generating Matter OTA Image

Use the ota_image_tool.py to generate the Matter OTA image, embedding the Matter OTA header:

    python3 ota_image_tool.py create -v <VENDORID> -p <PRODUCTID> -vn <VERSION> -vs <VERSIONSTRING> -da <DIGESTALGO> <path to ota_all.bin> <output ota image>

Example:

    python3 ota_image_tool.py create -v 0xFFF1 -p 0x8001 -vn 2 -vs 2.0 -da sha256 ../../../../../build_RTL8720E/ota_all.bin matter_ota_all.bin

</details>

<details>
  <summary>For AmebaSmart OTA Image</summary>

Ensure that the OTA address is set correctly according to the device's flash size in the following files:

    component/soc/usrcfg/amebasmart/ameba_flashcfg.c (ameba-rtos-v1.2 or v1.1)
    component/soc/amebasmart/usrcfg/ameba_flashcfg.c (ameba-rtos-v1.0)

The file can be found in the base SDK.

### Example

In `ameba_flashcfg.c`
```c
FlashLayoutInfo_TypeDef Flash_Layout[] = {
	/* Region_Type, [StartAddr, EndAddr] */
	{IMG_BOOT,      0x08000000, 0x0803FFFF}, //Boot Manifest(4K) + KM4 Bootloader(252K)
	//Users should modify below according to their own memory
	{IMG_APP_OTA1,  0x08040000, 0x0833FFFF}, //Certificate(4K) + Manifest(4K) + KM0 & KM4 & CA32 Application OTA1 + RDP IMG OTA1
	// + AP IMG OTA1
	{IMG_BOOT_OTA2, 0x08340000, 0x0837FFFF}, //Boot Manifest(4K) + KM4 Bootloader(252K) OTA
	{IMG_APP_OTA2,  0x08380000, 0x0867FFFF}, //Certificate(4K) + Manifest(4K) + KM0 & KM4 & CA32 Application OTA2 + RDP IMG OTA2
	// + AP IMG OTA2
	{FTL,           0x08680000, 0x08682FFF}, //FTL for BT(>=12K), The start offset of flash pages which is allocated to FTL physical map.
	{VFS1,          0x08683000, 0x086A2FFF}, //VFS region 1 (128K)
	{VFS2,          0xFFFFFFFF, 0xFFFFFFFF}, //VFS region 2
	{USER,          0xFFFFFFFF, 0xFFFFFFFF}, //reserve for user
	/* End */
	{0xFF,          0xFFFFFFFF, 0xFFFFFFFF},
};
```

Once you've set the addresses correctly for `IMG_APP_OTA1` and `IMG_APP_OTA2`, ensure that you rebuild both the firmware correctly.

### Generating Matter OTA Image

Use the ota_image_tool.py to generate the Matter OTA image, embedding the Matter OTA header:

    python3 ota_image_tool.py create -v <VENDORID> -p <PRODUCTID> -vn <VERSION> -vs <VERSIONSTRING> -da <DIGESTALGO> <path to ota_all.bin> <output ota image>

Example:

    python3 ota_image_tool.py create -v 0xFFF1 -p 0x8001 -vn 2 -vs 2.0 -da sha256 ../../../../../build_RTL8730E/ota_all.bin matter_ota_all.bin

</details>

<details>
  <summary>For Amebagreen2 OTA Image</summary>

Ensure that the OTA address is set correctly according to the device's flash size in the following file:

    component/soc/usrcfg/amebagreen2/ameba_flashcfg.c (ameba-rtos-v1.2)

The file can be found in the base SDK.

### Example

In `ameba_flashcfg.c`
```c
FlashLayoutInfo_TypeDef Flash_Layout[] = {
	/* Region_Type, [StartAddr, EndAddr] */
	{IMG_BOOT,      0x08000000, 0x0803FFFF}, //Boot Manifest(4K) + AP Bootloader(76K)
	//Users should modify below according to their own memory
	{IMG_APP_OTA1,  0x08040000, 0x081BFFFF}, //Certificate(4K) + Manifest(4K) + AP Application OTA1 + RDP IMG OTA1

	{IMG_BOOT_OTA2, 0x081C0000, 0x081FFFFF}, //Boot Manifest(4K) + AP Bootloader(76K) OTA
	{IMG_APP_OTA2,  0x08200000, 0x0837FFFF}, //Certificate(4K) + Manifest(4K) + AP Application OTA2 + RDP IMG OTA2

	{VFS1,          0x083C0000, 0x0843FFFF}, //VFS region 1 (512K)
	{VFS2,          0xFFFFFFFF, 0xFFFFFFFF}, //VFS region 2
	{USER,          0xFFFFFFFF, 0xFFFFFFFF}, //reserve for user

	/* End */
	{0xFF,          0xFFFFFFFF, 0xFFFFFFFF},
};
```

Once you've set the addresses correctly for `IMG_APP_OTA1` and `IMG_APP_OTA2`, ensure that you rebuild both the firmware correctly.

### Generating Matter OTA Image

The Amebagreen2 build emits its application image as `app.bin` together with the
OTA container `ota_all.bin`. Use `ota_all.bin`:

    python3 ota_image_tool.py create -v <VENDORID> -p <PRODUCTID> -vn <VERSION> -vs <VERSIONSTRING> -da <DIGESTALGO> <path to ota_all.bin> <output ota image>

Example:

    python3 ota_image_tool.py create -v 0xFFF1 -p 0x8001 -vn 2 -vs 2.0 -da sha256 ../../../../../build_RTL8721F/ota_all.bin matter_ota_all.bin

</details>

Ensure that `VERSION` and `VERSIONSTRING` match your
`CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION` and
`CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION_STRING` respectively. The
`matter_ota_image` script above takes care of this automatically.

To check your OTA image

    python3 ota_image_tool.py show <ota image>

Once you have ensured that the OTA image is correct, copy the output OTA image to the directory of the ota-provider built from the previous step.

    cp matter_ota_all.bin <path to the ota-provider directory>

## Executing the OTA

#### Terminal 1 (Linux ota-provider-app)

    cd connectedhomeip/ota-provider
    ./chip-ota-provider-app -f matter_ota_all.bin

#### Terminal 2 (chip-tool): 

Pair the device on NodeID=1, pair the ota-provider-app on NodeID=2.

    ./chip-tool ble-wifi 1 <SSID> <PASSWORD> 20202021 3840
    ./chip-tool pairing onnetwork 2 20202021

Set the ota-provider to be the default-otaprovider of the device.

    ./chip-tool otasoftwareupdaterequestor write default-otaproviders '[{"fabricIndex": 1, "providerNodeID": 2, "endpoint": 0}]' 1 0

Configure the ACL of the ota-provider-app to allow access for device.

    ./chip-tool accesscontrol write acl '[{"fabricIndex": 1, "privilege": 3, "authMode": 2, "subjects": null, "targets": [{"cluster": 41, "endpoint": null, "deviceType": null}]}]' 2 0

Announce the ota-provider-app to the device to start the OTA process.

    ./chip-tool otasoftwareupdaterequestor announce-otaprovider 2 0 0 0 1 0

## Expected Outcome

- The ota-provider-app will transfer the ota image by blocks of 1024 bytes.
- After completion, device will send an `ApplyUpdateRequest` to the ota-provider-app, who will send back an `ApplyUpdateResponse`.
- Upon receiving the `ApplyUpdateResponse`, the device will countdown 10 seconds before rebooting.
- If the OTA is successful, the device will reboot into the new image and will send a `NotifyUpdateApplied` to the ota-provider-app. 

## Common Mistakes

- VendorID and ProductID of the new OTA image does not match the ones in the Basic Information cluster, causing OTA to fail. Check your VendorID and ProductID using below `chip-tool` commands.

```
    ./chip-tool basicinformation read vendor-id 1 0
    ./chip-tool basicinformation read product-id 1 0
```

- Version of the new OTA image is not higher than the current image's version. OTA will only be allowed to execute if new image is newer than the current image.
