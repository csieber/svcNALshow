# svcNALshow

Prints out the position and type of all NAL units in a raw h.264/SVC bitstream.

## Requirements

 - premake4
 - g++
 - libboost-system-dev 
 - libboost-program-options-dev
 
## Compile

Use premake4 to create the makefiles and compile the application:

```bash
git clone git@github.com:csieber/svcNALshow.git
cd svcNALshow/

premake4 gmake
```

Build the application:

```bash
cd build/
make
```

## Usage

```
Options:
  --help                Help
  -F [ --file ] arg     SVC stream
```

Check the vagrant [here](vagrant/README.md) for an example how to use the application.

## Citing

Please cite the following publication if you use this application:

```
@inproceedings{sieber2013implementation,
  title={Implementation and User-centric Comparison of a Novel Adaptation Logic for DASH with SVC},
  author={Sieber, Christian and Ho{\ss}feld, Tobias and Zinner, Thomas and Tran-Gia, Phuoc and Timmerer, Christian},
  booktitle={2013 IFIP/IEEE International Symposium on Integrated Network Management (IM 2013)},
  pages={1318--1323},
  year={2013},
  organization={IEEE}
}
```