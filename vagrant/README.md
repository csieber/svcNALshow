# Vagrant Example

## Requirements

 - Vagrant
 - VirtualBox
 
## Setup

Clone the repository, spin up the VM and ssh into the machine:

```bash
git clone git@github.com:csieber/svcNALshow.git
cd svcNALshow/vagrant/

vagrant up
vagrant shh
```

Inside the machine, download an example video:

```bash
sudo apt-get install unzip

cd /svcNALshow/bin

wget http://sourceforge.net/projects/opensvcdecoder/files/Video%20Streams/video_5.zip/download -O video_5.zip

unzip video_5.zip
```

Analyse the video bitstream:

```bash
./svcNALshow_dbg -F video_5/video_5.264
```

The output should look like this:

```
h264: file index missing. Creating new one. This might take a while.
h264: No stream database found. Creating a new one. This might take a while.
h264: No stream statistics found. Creating new statistics. This might take a while.
Progress: 14.9626%
Progress: 29.9252%
Progress: 44.8878%
Progress: 59.8504%
Progress: 74.813%
Progress: 89.7756%
h264: Finished creating database/statistics.
```

There should be now a video\_5.264.{db|index|stats} file:

```
vagrant@vagrant-ubuntu-trusty-64:/svcNALshow/bin/video_5$ head video_5.264.index
944091
0, 0
1, 238
2, 252
3, 268
4, 278
5, 288
6, 297
7, 306
8, 2043

vagrant@vagrant-ubuntu-trusty-64:/svcNALshow/bin/video_5$ head video_5.264.stats
NALs: 2005
Size: 936071 bytes
Frames: 500 (highest frame number seen: 499)
Layers: 10
*------------------------------*
| ( D/ T/ Q) | NALs |     Size |
*------------------------------*
| (-1/-1/-1) |  521 |    23487 |
| ( 0/ 0/ 0) |   48 |    12709 |
| ( 1/ 0/ 0) |   32 |   160447 |

vagrant@vagrant-ubuntu-trusty-64:/svcNALshow/bin/video_5$ head video_5.264.db
|    NAL | Type |   Size | Frame | ( D/ T/ Q) |
|---------------------------------------------|
|      0 |    6 |    234 |      0 | (-1/-1/-1) |
|      1 |    7 |     10 |      0 | (-1/-1/-1) |
|      2 |   15 |     12 |      0 | (-1/-1/-1) |
|      3 |    8 |      6 |      0 | (-1/-1/-1) |
|      4 |    8 |      6 |      0 | (-1/-1/-1) |
|      5 |    6 |      5 |      0 | (-1/-1/-1) |
|      6 |   14 |      5 |      0 | ( 0/ 0/ 0) |
|      7 |    5 |   1733 |      0 | (-1/-1/-1) |
```

