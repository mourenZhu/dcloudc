# dcloudc
Device Cloud C,分为客户端、服务端。客户端上传设备信息，服务端获取设备信息并保存。  
这是一个本人用来学习Linux C的项目。


# 所需库
- libevent
```shell
apt install libevent-dev
```
- cJSON
```shell
cd ..
git clone https://github.com/DaveGamble/cJSON.git
cd cJSON/
mkdir build
cd build
cmake ..
sudo make install
```

# 构建项目
```shell
mkdir build
cd build
cmake ..
```

