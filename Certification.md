## Certified components

### Bluetooth Low Energy

**Certification overview:**

|                           | QDID      | Declaration ID    | Specification | Link  |
| ---                       | ---       | ---               | ---           | ---   |
| BLE Controller QPG7015M   | 163591    | D056523           | 5.2           | [https://launchstudio.bluetooth.com/ListingDetails/123871](https://launchstudio.bluetooth.com/ListingDetails/123871) |
| BLE Host Stack            | 146344    | D049426           | 5.2           | [https://launchstudio.bluetooth.com/ListingDetails/103670](https://launchstudio.bluetooth.com/ListingDetails/103670) |
| BLE profiles subsystem    | N/A       | N/A               | N/A           | Not certified but verified with the TCRL.2018-2 compliance tester using Bluetooth Profile Tuning Suites 7.3.0. **Please include testing for the BLE profiles included in your end-product listing.** |

**End-product certification instructions**

SDK users can reference Qorvo QDIDs (see above) in their End Product Listing (EPL)
- 1 BLE controller subsystem: Supplied by Qorvo SDK
- 1 BLE host subsystem: Supplied by Qorvo SDK
- \[optional\] Profile subsystem: **No certified subsystem in this SDK**
    - When modifying the profiles from the SDK or when the subsystem was not certified, one should selectively test the modified/non-certified profiles using the [profile-tuning-suite](https://www.bluetooth.com/develop-with-bluetooth/qualification-listing/qualification-test-tools/profile-tuning-suite/). Results of the Profile Tuning Suite tests should be verified by a [Bluetooth Qualification Test Facility (BQTF)](https://www.bluetooth.com/develop-with-bluetooth/qualification-listing/qualification-test-facilities).
### Thread

**Certification overview:**

|                           |  Certification ID  | Test Harness | Specification | Link  |
| ---                       |  ---               | ---          | ---           | ---   |
| QPG7015M Thread Component | 13A072.1           | v58.0        | 1.3           |[https://www.threadgroup.org](https://www.threadgroup.org/What-is-Thread/Developers#dnn_ctr1464_Thread_CompDataDefault_rptrProductData_tdcn_50)|


**Thread Device Roles**

|                  |   |
|---               |---|
|Border Router       |X|
|FTD-REED            |X|
|FTD-FED             ||
|MED                 ||
|SED                 ||
|SSED                ||
|On-Mesh Commissioner|X|
|Thread Joiner       |X|

**Optional Features**

|                           |   |
|---                        |---|
|DUA Management (BR)          |X|
|DUA Registration (MTD)       |X|
|Link Metrics Initiator (FTD) |X|
|DHCPv6 Agent                 ||
|DHCPv6 Client                |X|
|Joiner Provisioning (Joiner) ||

**End-product certification instructions**

Qorvo provides a PR SDK that has been certified as "Thread Component" (tested by a [Authorized-Test-Lab](https://www.threadgroup.org/Authorized-Test-Lab) and certification requested at the ThreadGroup). The seleced *device roles* and *optional features* are tailored for generic Thread usage, but can be reduced for e.g. Matter-only devices (no need for Thread Joiner role)

Qorvo provides maintenance SDKs that have been verified by running the certification tests in-house using a Thread Test Harness. This offers confidence for customers to use this SDK, but does not allow for inheritance. 

Qorvo does not provide "end product" certified modules or white-label products. A customer is expected to apply for "end product" certification which may require different tests methods than "Thread Component" certification.

**Certification by similarity (inheritance)**

The SDK offers the Thread stack in 2 ways:
- \[No inheritance possible\] Source code to run natively on your platform agter cross-compilation and porting
- \[Inheritance possible\] OpenThread Border Router docker image
 
### Zigbee

**Certification overview:**

|                                              |  Certification ID   | Specification | Link  |
| ---                                          |  ---                | ---           | ---   |
| QPG7015M Zigbee Compliant Platform reference | ZIG22013ZCP27336-24 | R22           |[https://csa-iot.org/csa_product/qpg6105/](https://csa-iot.org/csa_product/qpg6105/)|

Note: Qorvo certified QPG6105 as parent of our Zigbee Pro R22 compliant platform family. We reference this when certifying derivitive compliant platforms by similarity.

**End-product certification instructions**

Qorvo's SDKs for their Zigbee compliant platforms can be used to apply for end-product certification.
The SDKs come with test applications and instructions that enable an [Authorized-Test-Lab](https://www.threadgroup.org/Authorized-Test-Lab) to run end-product certification testing on a Zigbee Unified Test Harness (ZUTH)
