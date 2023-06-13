[top]
components : cachel1@CacheL1 
in : AddressIn
in : DataIn
out : AddressOut
out : DataOut
out : ErrorOut

Link : AddressIn AddressIn@cachel1
Link : DataIn DataIn@cachel1
Link : AddressOut@cachel1 AddressOut
Link : DataOut@cachel1 DataOut
Link : ErrorOut@cachel1 ErrorOut

[cachel1]
CacheAccessTime : 00:00:10:000
CacheTimingOutTime : 00:01:10:000