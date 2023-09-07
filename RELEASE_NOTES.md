# Release Notes

## Smart Home Gateway SDK  - v1.5.2.0

### New Features

- Feat(HAL): Block radio from sending and receiving when reaching a threshold in the outgoing communication buffer (over SPI, USB) to avoid a state mismatch between host and controller as the controller would continue responding while the host would not be informed of this. When the outgoing communication buffer drops below the threshold, the radio is re-enabled, allowing the controller to recover the communication. Closes: APPSCS-1389

- Feat(driver): new versioning scheme: appVersion is fixed to v0.0.0.0,  GP_CHANGELIST is defined as a GIT_SHA presented by a unique short

- Feat(BleAdapter): A start scanning request can now wait (blocking function) until an ongoing scanning stop request is handled. Closes APPSCS-1150

### Fixed Bugs

- Fix(Thread): Pulled in a security fix from OpenThread which blocks the security gap that allowed injection of arbitrary IPv6 datagrams without possession of the Thread Network Key. Closes: SDP011-1773

- Fix(Thread): Eliminated a corner case where at radio reset an incorrect frame pending bit is sent by the openthread on the first device trying to attach. Closes: SDP011-1317

- Fix(Thread): Fixed an incorrect frame counter in the OpenThread builds for QPG7015M, which could cause radio communications to break down. The DataConfirmCallback was extended to append the FrameCounter (which was received from the OpenThread stack before this callback) to the packet. Closes: SDP011-1318

- Fix(Thread): Fixed CSL timing for RCP (used by OpenThread Border Router) by making otPlatGetNow() function unconditionally available. Closes: SDP011-1204

- Fix(BLE): Fixed an issue where the Qorvo BLE+Zigbee+Thread transceiver QPG7015M failed to maintain an active BLE connection while active scanning in the background. Due to a timing conflict in handling the transmission of the connection event and the scan request, the Bluetooth LE Real-Time Link Layer failed to send the connection event PDU and became unresponsive until reset. Closes: SDP004-3051

- Fix(BLE Host memory): Aligned the WSF memory chunk size with maximum possible size for ATT write request, ATT notification and ATT indication. When a GATT characteristics of maximum value-length was used, it would result in a memory allocation failure, leading to a failing assert that reset the system. Closes: APPSCS-1825

### Known Issues

- N/A
