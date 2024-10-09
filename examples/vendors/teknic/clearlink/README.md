# EDS File (Electronic Data Sheets)

This file comes from the Teknic Downloads page

## CIP Definition

https://www.odva.org/wp-content/uploads/2020/06/PUB00123R1_Common-Industrial_Protocol_and_Family_of_CIP_Networks.pdf


## Understanding Implicit Messaging

There are a number of object assemblies that are reserved for Ethernet/IP (https://infosys.beckhoff.com/english.php?content=../content/1033/tf6280_tc3_ethernetipslave/10390821771.html) 

| Object      | Class   | Description         |
|-------------|---------|---------------------|
| Identity Object         | 0x1   | Returns values for the Identity            |
| Message Router Object   | 0x2   |             |
| Assembly Object         | 0x4   |             |
| ConnectionManager       | 0x6   | Handles initializing the Requested Packet Interval and sets assemblies  |
| TCP/IP Interface Object | 0xF5  |             |
| Ethernet Link Object    | OxF6  |             |
* 