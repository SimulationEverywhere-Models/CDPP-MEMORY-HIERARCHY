[top]
components : cachel1@CacheL1
components : cachel2@CacheL2

in : cpuaddressin  mainmemorydatain
out : cachedataout cacheaddressout

Link : cpuaddressin addressin@cachel1
Link : mainmemorydatain datain@cachel2
Link : dataout@cachel1 cachedataout
Link : addressout@cachel2 cacheaddressout
Link : addressout@cachel1  addressin@cachel2
Link : dataout@cachel2  datain@cachel1


[cachel1]
CacheAccessTime : 00:00:10:000
CacheTimingOutTime : 00:01:10:000

[cachel2]
CacheAccessTime : 00:00:20:000
CacheTimingOutTime : 00:00:50:000
